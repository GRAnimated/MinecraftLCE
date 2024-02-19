#pragma once

#include "Minecraft.Nbt/Tag.h"

class ListTag : public Tag {
public:
    ListTag();

    void write(DataOutput*) override;
    void load(DataInput*, int) override;
    void toString() override;
    u8 getId() override;
    void print(const std::wstring&, char*, std::wostream&) override;
    ~ListTag() override;
    void equals(Tag*) override;
    void copy() override;
    void stripEmptyChildren() override;
    bool isEmpty() const override;
};