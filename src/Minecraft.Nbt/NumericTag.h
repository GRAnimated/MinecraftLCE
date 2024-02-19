#pragma once

#include "Minecraft.Nbt/Tag.h"

class NumericTag : public Tag {
public:
    NumericTag();

    virtual void getAsLong() = 0;
    virtual void getAsInt() = 0;
    virtual void getAsShort() = 0;
    virtual void getAsByte() = 0;
    virtual void getAsDouble() = 0;
    virtual void getAsFloat() = 0;
    virtual void copy() = 0;
};