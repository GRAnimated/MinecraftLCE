#pragma once

#include "com/mojang/nbt/Tag.h"
#include "net/minecraft/world/ArrayWithLength.h"
#include "nn/types.h"
#include "types.h"
#include <unordered_map>

class CompoundTag : public Tag {
public:
    CompoundTag();

    void write(DataOutput*) override;
    void load(DataInput*, int) override;
    std::wstring toString() override;
    u8 getId() override;
    void print(const std::wstring&, char*, std::wostream&) override;
    ~CompoundTag();
    bool equals(Tag*) override;
    CompoundTag* copy() override;
    void stripEmptyChildren() override;
    bool isEmpty() const override;
    void remove(const std::wstring&);

    /** Gets a child `Compound Tag`
     *
     * @param name The name of the `Tag` that you want to get
     */
    CompoundTag* getCompound(const std::wstring& name);

    /** Gets a child `bool`
     *
     * @param name The name of the `Tag` that you want to get
     */
    bool getBoolean(const std::wstring& name);

    /** Gets a child `Byte`
     *
     * @param name The name of the `Tag` that you want to get
     */
    byte getByte(const std::wstring& name);

    /** Gets a child `std::wstring`
     *
     * @param name The name of the `Tag` that you want to get
     */
    std::wstring getString(const std::wstring& name);

    /** Gets a child `Int`
     *
     * @param name The name of the `Tag` that you want to get
     */
    int getInt(const std::wstring& name);

    /** Gets a child `Short`
     *
     * @param name The name of the `Tag` that you want to get
     */
    short getShort(const std::wstring& name);

    /** Gets a child `Float`
     *
     * @param name The name of the `Tag` that you want to get
     */
    float getFloat(const std::wstring& name);

    /** Gets a child `List Tag` (but returns void???)
     *
     *  @param name The name of the child tag
     *  @param length The length of the list (unconfirmed)
     */
    void getList(const std::wstring& name, int length);

    /** Gets a child `Tag` with the provided name
     *
     * @param name The name of the tag that you want to get.
     */
    CompoundTag* get(const std::wstring& name);

    /** Gets a child `List Tag` (Safe)
     *
     *  Why does this return void
     *
     *  @param name The name of the child tag
     *  @param length The length of the list (unconfirmed)
     */
    void fjSafeGetListTag(const std::wstring& name, int length);

    /** Checks if a child with the provided name exists
     *
     *  @param name The name of the child tag
     */
    bool contains(const std::wstring& name);

    /** Checks if a child with the provided name and type exists
     *
     *  @param name The name of the child tag
     *  @param type Type of the child tag
     */
    bool contains(const std::wstring& name, int type);

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

    void putByteArray(const std::wstring&, arrayWithLength<u8>);
    arrayWithLength<u8> getByteArray(const std::wstring&);

    std::unordered_map<std::wstring, Tag*> childTags;
};
