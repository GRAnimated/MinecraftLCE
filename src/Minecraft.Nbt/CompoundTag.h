#pragma once

#include "nn/types.h"
#include "types.h"
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
    CompoundTag* copy() override;
    void stripEmptyChildren() override;
    bool isEmpty() const override;

    /** Gets a child `Compound Tag`
     *
     * @param name The name of the `Tag` that you want to get
     */
    CompoundTag* getCompound(std::wstring const& name);

    /** Gets a child `bool`
     *
     * @param name The name of the `Tag` that you want to get
     */
    bool getBoolean(std::wstring const& name);

    /** Gets a child `Byte`
     *
     * @param name The name of the `Tag` that you want to get
     */
    byte getByte(std::wstring const& name);

    /** Gets a child `std::wstring`
     *
     * @param name The name of the `Tag` that you want to get
     */
    std::wstring getString(std::wstring const& name);

    /** Gets a child `Int`
     *
     * @param name The name of the `Tag` that you want to get
     */
    int getInt(std::wstring const& name);

    /** Gets a child `Short`
     *
     * @param name The name of the `Tag` that you want to get
     */
    short getShort(std::wstring const& name);

    /** Gets a child `Float`
     *
     * @param name The name of the `Tag` that you want to get
     */
    float getFloat(std::wstring const& name);

    /** Gets a child `List Tag` (but returns void???)
     *
     *  @param name The name of the child tag
     *  @param length The length of the list (unconfirmed)
     */
    void getList(std::wstring const& name, int length);

    /** Gets a child `Tag` with the provided name
     *
     * @param name The name of the tag that you want to get.
     */
    CompoundTag* get(std::wstring const& name);

    /** Gets a child `List Tag` (Safe)
     *
     *  Why does this return void
     *
     *  @param name The name of the child tag
     *  @param length The length of the list (unconfirmed)
     */
    void fjSafeGetListTag(std::wstring const& name, int length);

    /** Checks if a child with the provided name exists
     *
     *  Dunno what the int is for
     *  @param name The name of the child tag
     */
    bool contains(std::wstring const& name, int);

    /** Adds a `Tag`
     *
     *  @param name The name of the value
     *  @param tag The tag
     */
    void put(const std::wstring& name, Tag* tag);

    /** Adds a `Boolean`
     *
     *  @param name The name of the value
     *  @param value The value
     */
    void putBoolean(const std::wstring& name, bool value);

    /** Adds a `Byte`
     *
     *  @param name The name of the value
     *  @param value The value
     */
    void putByte(const std::wstring& name, byte value);

    /** Adds a `Short`
     *
     *  @param name The name of the value
     *  @param value The value
     */
    void putShort(const std::wstring& name, short value);

    /** Adds an `Int`
     *
     *  @param name The name of the value
     *  @param value The value
     */
    void putInt(const std::wstring& name, int value);

    /** Adds a `Long`
     *
     *  @param name The name of the value
     *  @param value The value
     */
    void putLong(const std::wstring& name, long long value);

    /** Adds a `Float`
     *
     *  @param name The name of the value
     *  @param value The value
     */
    void putFloat(const std::wstring& name, float value);

    /** Adds an `std::wstring`
     *
     *  @param name The name of the string
     *  @param str The string
     */
    void putString(const std::wstring& name, const std::wstring& str);

    std::unordered_map<std::wstring, Tag*> *childTags;
    void* field_8;
    void* field_10;
    void* field_18;
    float field_28 = 1.0f;
};