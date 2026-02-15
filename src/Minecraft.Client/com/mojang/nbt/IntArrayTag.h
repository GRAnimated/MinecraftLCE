#pragma once

#include "com/mojang/nbt/Tag.h"
#include "net/minecraft/world/ArrayWithLength.h"

class IntArrayTag : public Tag {
public:
    IntArrayTag();
    IntArrayTag(arrayWithLength<int> data);

    void write(DataOutput*) override;
    void load(DataInput*, int) override;
    std::wstring toString() override;
    u8 getId() override;
    ~IntArrayTag() override;
    bool equals(Tag*) override;
    Tag* copy() override;

    arrayWithLength<int> m_data;
};
