#pragma once

#include "net/minecraft/nbt/NumericTag.h"

class IntTag : public NumericTag {
public:
    IntTag();
    IntTag(int);

    void write(DataOutput*) override;
    void load(DataInput*, int) override;
    std::wstring toString() override;
    u8 getId() override;
    bool equals(Tag*) override;
    Tag* copy() override;

    long getAsLong() override;
    int getAsInt() override;
    short getAsShort() override;
    u8 getAsByte() override;
    double getAsDouble() override;
    float getAsFloat() override;

    int mData;
};
