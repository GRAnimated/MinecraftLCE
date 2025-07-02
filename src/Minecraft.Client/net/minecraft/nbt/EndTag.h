#pragma once

#include "Minecraft.Nbt/Tag.h"

class EndTag : public Tag {
public:
    EndTag();

    void write(DataOutput*) override;
    void load(DataInput*, int) override;
    std::wstring toString() override;
    u8 getId() override;
    bool equals(Tag*) override;
    Tag* copy() override;
};
