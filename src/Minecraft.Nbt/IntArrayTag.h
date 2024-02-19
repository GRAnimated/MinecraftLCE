#pragma once

#include "Minecraft.Nbt/Tag.h"

class IntArrayTag : public Tag {
public:
    IntArrayTag();

    void write(DataOutput*) override;
    void load(DataInput*, int) override;
    void toString() override;
    u8 getId() override;
    ~IntArrayTag() override;
    void equals(Tag*) override;
    void copy() override;

    int mData[];
};