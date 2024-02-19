#pragma once

#include "Minecraft.Nbt/NumericTag.h"

class IntTag : public NumericTag {
public:
    IntTag();
    IntTag(int);

    void write(DataOutput*) override;
    void load(DataInput*, int) override;
    void toString() override;
    u8 getId() override;
    void equals(Tag*) override;
    void copy() override;

    void getAsLong() override;
    void getAsInt() override;
    void getAsShort() override;
    void getAsByte() override;
    void getAsDouble() override;
    void getAsFloat() override;

    int mData;
};