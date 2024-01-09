#pragma once

#include <nn/types.h>
#include <type_traits>

namespace nn::util {

namespace detail {

template <typename Integer>
void AndEqual(Integer* dest, const Integer* source, int count) {
    for (int i = 0; i < count; ++i) {
        dest[i] &= source[i];
    }
}

template <typename Integer>
void XorEqual(Integer* dest, const Integer* source, int count) {
    for (int i = 0; i < count; ++i) {
        dest[i] ^= source[i];
    }
}

template <typename Integer>
void OrEqual(Integer* dest, const Integer* source, int count) {
    for (int i = 0; i < count; ++i) {
        dest[i] |= source[i];
    }
}

template <typename Integer>
bool Equals(const Integer* dest, const Integer* source, int count) {
    for (int i = 0; i < count; ++i) {
        if (dest[i] != source[i]) {
            return false;
        }
    }

    return true;
}

template <typename Integer>
bool IsAnyOn(const Integer* _storage, int count) {
    for (int i = 0; i < count; ++i) {
        if (_storage[i] != 0) {
            return true;
        }
    }

    return false;
}

}  // namespace detail

template <int N, typename Tag>
struct BitFlagSet {
    typedef typename std::conditional<N <= 32, uint32_t, uint64_t>::type StorageT;

    static const int StorageBitCount = 8 * sizeof(StorageT);
    static const int StorageCount = (N + StorageBitCount - 1) / StorageBitCount;
    StorageT _storage[StorageCount]{};

    class Reference {
    public:
        Reference& operator=(bool isOn) {
            m_Set->Set(m_Index, isOn);
            return *this;
        }

        Reference& operator=(const Reference& ref) {
            m_Set->Set(m_Index, ref);
            return *this;
        }

        Reference& Flip() {
            m_Set->Flip(m_Index);
            return *this;
        }

        bool operator~() const { return !m_Set->Test(m_Index); }

        operator bool() const { return m_Set->Test(m_Index); }

    private:
        BitFlagSet* m_Set;
        int m_Index;

        Reference() : m_Set(nullptr), m_Index(0) {}
        Reference(BitFlagSet& set, int index) : m_Set(&set), m_Index(index) {}
    };

    BitFlagSet operator~() const {
        BitFlagSet tmp = *this;
        tmp.Flip();
        return tmp;
    }

    BitFlagSet operator&(const BitFlagSet& other) const {
        BitFlagSet value = *this;
        value &= other;
        return value;
    }

    BitFlagSet operator^(const BitFlagSet& other) const {
        BitFlagSet value = *this;
        value ^= other;
        return value;
    }

    BitFlagSet operator|(const BitFlagSet& other) const {
        BitFlagSet value = *this;
        value |= other;
        return value;
    }

    BitFlagSet& operator&=(const BitFlagSet& other) {
        detail::AndEqual(_storage, other._storage, StorageCount);
        return *this;
    }

    BitFlagSet& operator^=(const BitFlagSet& other) {
        detail::XorEqual(_storage, other._storage, StorageCount);
        return *this;
    }

    BitFlagSet& operator|=(const BitFlagSet& other) {
        detail::OrEqual(_storage, other._storage, StorageCount);
        return *this;
    }

    bool operator==(const BitFlagSet& other) const {
        return detail::Equals(_storage, other._storage, StorageCount);
    }

    bool operator!=(const BitFlagSet& other) const {
        return !detail::Equals(_storage, other._storage, StorageCount);
    }

    bool operator[](int index) const { return Test(index); }
    Reference operator[](int index) { return Reference(*this, index); }

    bool IsAnyOn() const { return detail::IsAnyOn(_storage, StorageCount); }

    // https://en.wikichip.org/wiki/population_count
    int CountPopulation() const {
        int c = 0;
        for (int i = 0; i < StorageCount; ++i) {
            StorageT x = _storage[i];
            for (; x != 0; x &= x - 1)
                c++;
        }
        return c;
    }

    BitFlagSet& Flip(int index) { return Set(index, !Test(index)); }

    BitFlagSet& Flip() {
        for (int i = 0; i < StorageCount; ++i) {
            _storage[i] = ~_storage[i];
        }
        Truncate();

        return *this;
    }

    bool IsAllOn() const { return CountPopulation() == N; }
    bool IsAllOff() const { return CountPopulation() == 0; }

    BitFlagSet& Reset() {
        for (int i = 0; i < StorageCount; ++i) {
            _storage[i] = 0;
        }
        return *this;
    }

    BitFlagSet& Reset(int index) { return Set(index, false); }

    BitFlagSet& Set() {
        for (int i = 0; i < StorageCount; ++i) {
            _storage[i] = ~0;
        }
        Truncate();

        return *this;
    }

    BitFlagSet& Set(int index, bool isOn = true) {
        // todo: add assert to verify index is valid
        return SetImpl(GetStorageIndex(index), MakeStorageMask(index), isOn);
    }

    template <typename FlagT>
    BitFlagSet& Set(bool isOn = true) const {
        return SetImpl(FlagT::StorageIndex, FlagT::StorageMask, isOn);
    }

    int GetCount() const { return N; }

    bool Test(int index) const {
        // todo: add assert to verify index is valid
        return TestImpl(GetStorageIndex(index), MakeStorageMask(index));
    }

    template <typename FlagT>
    bool Test() const {
        return TestImpl(FlagT::StorageIndex, FlagT::StorageMask);
    }

    template <int BitIndex>
    struct Flag {
        static_assert(BitIndex < N, "BitIndex < N");

        static constexpr BitFlagSet buildMask() {
            BitFlagSet tmp;
            tmp.data[StorageIndex] = StorageMask;
            return tmp;
        }

        static constexpr int Index = BitIndex;
        static constexpr BitFlagSet Mask = buildMask();

    private:
        static constexpr int StorageIndex = BitIndex / StorageBitCount;
        static constexpr StorageT StorageMask = StorageT(1) << (BitIndex % StorageBitCount);
    };

private:
    BitFlagSet& SetImpl(int storageIndex, StorageT storageMask, bool isOn) {
        if (isOn) {
            _storage[storageIndex] |= storageMask;
        } else {
            _storage[storageIndex] &= ~storageMask;
        }
        return *this;
    }

    bool TestImpl(int storageIndex, StorageT storageMask) const {
        return _storage[storageIndex] & storageMask;
    }

    void Truncate() { TruncateIf(std::integral_constant<bool, (N % StorageBitCount) != 0>{}); }

    void TruncateIf(std::true_type) { _storage[StorageCount - 1] &= MakeStorageMask(N) - 1; }
    void TruncateIf(std::false_type) {}

    static int GetStorageIndex(int index) { return index / StorageBitCount; }
    static StorageT MakeStorageMask(int index) { return StorageT(1) << (index % StorageBitCount); }
};

}  // namespace nn::util
