#pragma once

#include "Minecraft.Nbt/Tag.h"
#include <vector>

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

private:
    std::vector<Tag*> mData;
    u8 mTagId;
};
