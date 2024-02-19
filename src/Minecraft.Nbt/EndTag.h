#pragma once

#include "Minecraft.Nbt/Tag.h"

class EndTag : public Tag {
public:
    EndTag();

    void write(DataOutput*) override;
    void load(DataInput*, int) override;
    void toString() override;
    u8 getId() override;
    void equals(Tag*) override;
    void copy() override;
};