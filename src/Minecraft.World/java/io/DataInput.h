#pragma once

#include "net/minecraft/world/ArrayWithLength.h"
#include "net/minecraft/world/PlayerUID.h"

class DataInput {
public:
    virtual ~DataInput();
    virtual bool readBoolean() = 0;
    virtual unsigned char readByte() = 0;
    virtual unsigned char readUnsignedByte() = 0;
    virtual int readUnsignedShort() = 0;
    virtual wchar_t readChar() = 0;
    // is this correct? i swapped the two readFully methods for a match in ByteArrayTag::load
    virtual void readFully(arrayWithLength<char>) = 0;
    virtual void readFully(arrayWithLength<unsigned char>) = 0;
    virtual void readBytes(arrayWithLength<unsigned char>) = 0;
    virtual double readDouble() = 0;
    virtual float readFloat() = 0;
    virtual int readInt() = 0;
    virtual long readLong() = 0;
    virtual short readShort() = 0;
    virtual std::wstring readUTF() = 0;
    virtual void readUTFChar() = 0;
    virtual PlayerUID readPlayerUID() = 0;
    virtual void skipBytes(long long) = 0;
};
