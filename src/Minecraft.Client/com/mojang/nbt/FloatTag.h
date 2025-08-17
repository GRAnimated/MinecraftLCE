#pragma once

#include "com/mojang/nbt/NumericTag.h"

class FloatTag : public NumericTag {
public:
    FloatTag();
    FloatTag(float data);

    void write(DataOutput*) override;
    void load(DataInput*, int) override;
    std::wstring toString() override;
    u8 getId() override;
    bool equals(Tag*) override;
    long getAsLong() override;
    int getAsInt() override;
    short getAsShort() override;
    u8 getAsByte() override;
    double getAsDouble() override;
    float getAsFloat() override;
    Tag* copy() override;

    float mData;
};
