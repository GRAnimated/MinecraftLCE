#pragma once

#include "Minecraft.Nbt/NumericTag.h"

class ByteTag : public NumericTag {
public:
    ByteTag();

    void getAsLong() override;
    void getAsInt() override;
    void getAsShort() override;
    void getAsByte() override;
    void getAsDouble() override;
    void getAsFloat() override;
    void copy() override;

    u8 mData;
};