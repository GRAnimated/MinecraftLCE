#pragma once

#include "Minecraft.Nbt/NumericTag.h"

class LongTag : public NumericTag {
public:
    LongTag();

    void write(DataOutput*) override;
    void load(DataInput*, int) override;
    void toString() override;
    u8 getId() override;
    void equals(Tag*) override;
    void getAsLong() override;
    void getAsInt() override;
    void getAsShort() override;
    void getAsByte() override;
    void getAsDouble() override;
    void getAsFloat() override;
    void copy() override;

    long mData;
};