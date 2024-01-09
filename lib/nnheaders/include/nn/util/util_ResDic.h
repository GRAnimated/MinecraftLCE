#pragma once

#include <nn/util.h>
#include <nn/util/AccessorBase.h>
#include <nn/util/util_BinTypes.h>

namespace nn::util {

struct ResDicData {
    struct Entry {
        int32_t refBit;
        uint16_t children[2];
        BinPtrToString pKey;
    };

    BinBlockSignature signature;
    int32_t count;
    Entry entries[1];
};

class ResDic : public AccessorBase<ResDicData> {
    NN_NO_COPY(ResDic);

public:
    static const int Npos = -1;

    int GetCount() const { return ToData().count; }

    string_view GetKey(int index) const { return ToData().entries[1 + index].pKey.Get()->Get(); }

    int FindIndex(const string_view& key) const {
        const Entry* pEntry = FindImpl(key);
        return *pEntry->pKey.Get() == key ?
                   static_cast<int>(std::distance(&ToData().entries[1], pEntry)) :
                   Npos;
    }

    bool Build();

    static size_t CalculateSize(int numEntries) {
        size_t size = 0;
        size += sizeof(ResDicData);
        size += sizeof(ResDicData::Entry) * numEntries;
        return size;
    }

private:
    static int ExtractRefBit(const string_view& key, int refBit) {
        int charIndex = refBit >> 3;
        if (static_cast<size_t>(charIndex) < key.length()) {
            int bitIndex = refBit & 7;
            return (key[key.length() - charIndex - 1] >> bitIndex) & 1;
        }
        return 0;
    }

    static int FindRefBit(const string_view& lhs, const string_view& rhs);

    static bool Older(const ResDicData::Entry* pParent, const ResDicData::Entry* pChild) {
        return pParent->refBit < pChild->refBit;
    }

    ResDicData::Entry* GetChild(const ResDicData::Entry* pParent, const string_view& key) {
        int childIndex = ExtractRefBit(key, pParent->refBit);
        int entryIndex = pParent->children[childIndex];
        return &ToData().entries[entryIndex];
    }

    const ResDicData::Entry* GetChild(const ResDicData::Entry* parent,
                                      const string_view& key) const {
        int bit = ExtractRefBit(key, parent->refBit);
        int index = parent->children[bit];
        return &ToData().entries[index];
    }

    void SetChild(ResDicData::Entry* parent, ResDicData::Entry* child) {
        int bit = ExtractRefBit(*child->pKey.Get(), parent->refBit);
        auto index = std::distance(ToData().entries, child);
        parent->children[bit] = static_cast<uint16_t>(index);
    }

    const ResDicData::Entry* FindImpl(const string_view& key) const {
        const Entry* pParent = &ToData().entries[0];
        const Entry* pChild = &ToData().entries[pParent->children[0]];

        while (Older(pParent, pChild)) {
            pParent = pChild;
            pChild = GetChild(pChild, key);
        }
        return pChild;
    }
};
}  // namespace nn::util