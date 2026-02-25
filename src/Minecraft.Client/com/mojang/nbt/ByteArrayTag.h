#pragma once

#include "com/mojang/nbt/Tag.h"
#include "net/minecraft/world/ArrayWithLength.h"

class ByteArrayTag : public Tag {
public:
    ByteArrayTag();
    ByteArrayTag(arrayWithLength<u8>, bool);

    void write(DataOutput*) override;
    void load(DataInput*, int) override;
    std::wstring toString() override;
    u8 getId() override;
    ~ByteArrayTag() override;
    bool equals(Tag*) override;
    Tag* copy() override;

    arrayWithLength<u8> m_data;
    bool m_unknown;
};
