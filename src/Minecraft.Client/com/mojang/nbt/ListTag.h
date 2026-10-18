#pragma once

#include "com/mojang/nbt/Tag.h"
#include <vector>

class CompoundTag;

class ListTag : public Tag {
public:
    ListTag();
    ListTag(int);

    void write(DataOutput*) override;
    void load(DataInput*, int) override;
    std::wstring toString() override;
    u8 getId() override;
    void print(const std::wstring&, char*, std::wostream&) override;
    ~ListTag() override;
    bool equals(Tag*) override;
    Tag* copy() override;
    void stripEmptyChildren() override;
    bool isEmpty() const override;

    void add(Tag* tag);
    // Replaces an accepted element and deletes its previous owner. Rejected
    // replacements remain caller-owned; assigning the same pointer is a no-op.
    void set(int index, Tag* tag);
    size_t size() const;
    int getElementType() const { return m_tagId; }
    CompoundTag* getCompound(int) const;
    int getInt(int) const;
    double getDouble(int) const;

private:
    std::vector<Tag*> m_data;
    u8 m_tagId;
};
