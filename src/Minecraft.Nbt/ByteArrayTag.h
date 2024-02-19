#pragma once

#include "Minecraft.Core/arrayWithLength.h"
#include "Minecraft.Nbt/Tag.h"

class ByteArrayTag : public Tag {
public:
    ByteArrayTag();
    ByteArrayTag(arrayWithLength<u8>, bool);

    void write(DataOutput*) override;
    void load(DataInput*, int) override;
    void toString() override;
    u8 getId() override;
    ~ByteArrayTag() override;
    void equals(Tag*) override;
    void copy() override;

    u8 data[];
};