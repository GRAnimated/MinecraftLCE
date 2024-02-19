#pragma once

#include "Minecraft.Nbt/Tag.h"

class CompoundTag : public Tag {
public:
    CompoundTag();

    void write(DataOutput*) override;
    void load(DataInput*, int) override;
    void toString() override;
    u8 getId() override;
    void print(const std::wstring&, char*, std::wostream&) override;
    ~CompoundTag();
    void equals(Tag*) override;
    void copy() override;
    void stripEmptyChildren() override;
    bool isEmpty() const override;

    bool getBoolean(std::wstring const&);
    void contains(std::wstring const&);
    std::wstring getString(std::wstring const&);
    int getInt(std::wstring const&);
    short getShort(std::wstring const&);
    float getFloat(std::wstring const&);
    void getList(std::wstring const&, int);
    void fjSafeGetListTag(std::wstring const&, int);
    void contains(std::wstring const&, int);
};