#pragma once

#include "Minecraft.Core/io/DataInput.h"
#include "Minecraft.Core/io/InputStream.h"
#include "Minecraft.World/ArrayWithLength.h"

class BlockPos;

class DataInputStream : public InputStream, public DataInput {
public:
    DataInputStream(InputStream*);
    virtual ~DataInputStream();
    virtual unsigned int read();
    virtual void read(arrayWithLength<unsigned char>);
    virtual void read(arrayWithLength<unsigned char>, unsigned int, unsigned int);
    virtual void close();
    virtual void skip(long long);
    virtual void readBoolean();
    virtual unsigned char readByte();
    virtual void readUnsignedByte();
    virtual void readUnsignedShort();
    virtual char readChar();
    virtual void readFully(arrayWithLength<unsigned char>);
    virtual void readFully(arrayWithLength<char>);
    virtual void readBytes(arrayWithLength<unsigned char>);
    virtual double readDouble();
    virtual float readFloat();
    virtual int readInt();
    virtual long readLong();
    virtual short readShort();
    virtual void readUTF();
    virtual void readUTFChar();
    virtual void readPlayerUID();
    virtual void skipBytes(long long);

    int readVarInt();
    BlockPos readBlockPos();

    InputStream* mInputStream;
};
