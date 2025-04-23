#pragma once
#include <string>

#include "Minecraft.World/ArrayWithLength.h"

class PlayerUID;

class DataOutput {
public:
    DataOutput();

    virtual ~DataOutput();
    virtual void close();
    virtual void writeFully(arrayWithLength<unsigned char>);  // guessed name
    virtual void _20();                                       // unknown function
    virtual void writeBytes(arrayWithLength<unsigned char>) = 0;
    virtual void writeByte(unsigned char) = 0;
    virtual void writeDouble(double) = 0;
    virtual void writeFloat(float) = 0;
    virtual void writeInt(int) = 0;
    virtual void writeLong(long long) = 0;
    virtual void writeShort(short) = 0;
    virtual void writeUnsignedShort(unsigned short) = 0;
    virtual void writeChar(wchar_t) = 0;
    virtual void writeChars(const std::wstring&) = 0;
    virtual void writeBoolean(bool) = 0;
    virtual void writeUTF(std::wstring const&) = 0;
    virtual void writePlayerUID(PlayerUID) = 0;
};
