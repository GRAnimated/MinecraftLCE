#pragma once

#include "Minecraft.Nbt/Tag.h"
#include "nn/types.h"
#include "types.h"

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
    CompoundTag* copy() override;
    void stripEmptyChildren() override;
    bool isEmpty() const override;

    CompoundTag* getCompound(std::wstring const&);
    bool getBoolean(std::wstring const&);
    byte getByte(std::wstring const&);
    std::wstring getString(std::wstring const&);
    int getInt(std::wstring const&);
    short getShort(std::wstring const&);
    float getFloat(std::wstring const&);
    void getList(std::wstring const&, int);
    void fjSafeGetListTag(std::wstring const&, int);
    bool contains(std::wstring const&, int);

    void put(const std::wstring&, Tag*);
    void putBoolean(const std::wstring&, bool);
    void putInt(const std::wstring&, int);
    void putFloat(const std::wstring&, float);

    void* field_8;
    void* field_10;
    void* field_18;
    void* field_20;
    float field_28 = 1.0f;
};