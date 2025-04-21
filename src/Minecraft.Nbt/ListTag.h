#pragma once

#include "Minecraft.Nbt/Tag.h"

class ListTag : public Tag {
public:
    ListTag();
    ListTag(int);

    void write(DataOutput*) override;
    void load(DataInput*, int) override;
    void toString() override;
    u8 getId() override;
    void print(const std::wstring&, char*, std::wostream&) override;
    ~ListTag() override;
    void equals(Tag*) override;
    Tag* copy() override; // originally void but was throwing error
    void stripEmptyChildren() override;
    bool isEmpty() const override;
    void add(Tag *tag);
};