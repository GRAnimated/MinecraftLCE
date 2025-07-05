#pragma once

#include "com/mojang/nbt/Tag.h"

class StringTag : public Tag {
public:
    StringTag();

    void write(DataOutput*) override;
    void load(DataInput*, int) override;
    std::wstring toString() override;
    u8 getId() override;
    ~StringTag() override;
    bool equals(Tag*) override;
    Tag* copy() override;
    bool isEmpty() const override;
    std::wstring getAsString() override;

    std::wstring mData;
};
