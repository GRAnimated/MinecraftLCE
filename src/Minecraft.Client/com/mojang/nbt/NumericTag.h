#pragma once

#include "com/mojang/nbt/Tag.h"

class NumericTag : public Tag {
public:
    NumericTag();

    virtual long getAsLong() = 0;
    virtual int getAsInt() = 0;
    virtual short getAsShort() = 0;
    virtual u8 getAsByte() = 0;
    virtual double getAsDouble() = 0;
    virtual float getAsFloat() = 0;
    virtual Tag* copy() = 0;
};
