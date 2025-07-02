#pragma once

#include "nn/types.h"
#include <string>
#include <vector>

class DataOutput;
class DataInput;

class Tag {
public:
    Tag();

    virtual void write(DataOutput*) = 0;
    virtual void load(DataInput*, int) = 0;
    virtual std::wstring toString() = 0;
    virtual u8 getId() = 0;
    virtual void print(const std::wstring&, char*, std::wostream&);
    virtual ~Tag() {}
    virtual bool equals(Tag* other);
    virtual Tag* copy() = 0;
    virtual void stripEmptyChildren();
    virtual bool isEmpty() const;
    virtual std::wstring getAsString();

    static Tag* newTag(u8 id);
    static const wchar_t* getTagTypeName(u8 id);

    template <class T>
    static void deleteElements(const std::vector<T>&);

protected:
    static const u8 TAG_End = 0;
    static const u8 TAG_Byte = 1;
    static const u8 TAG_Short = 2;
    static const u8 TAG_Int = 3;
    static const u8 TAG_Long = 4;
    static const u8 TAG_Float = 5;
    static const u8 TAG_Double = 6;
    static const u8 TAG_Byte_Array = 7;
    static const u8 TAG_String = 8;
    static const u8 TAG_List = 9;
    static const u8 TAG_Compound = 10;
    static const u8 TAG_Int_Array = 11;
};
