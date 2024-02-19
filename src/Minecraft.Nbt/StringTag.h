#pragma once

#include "Minecraft.Nbt/Tag.h"

class StringTag : public Tag {
public:
    StringTag();

    void write(DataOutput*) override;
    void load(DataInput*, int) override;
    void toString() override;
    u8 getId() override;
    ~StringTag() override;
    void equals(Tag*) override;
    void copy() override;
    bool isEmpty() const override;
    void getAsString() override;

    std::wstring mData;
};