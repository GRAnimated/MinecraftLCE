#pragma once

#include "java/io/DataInput.h"
#include "java/io/InputStream.h"
#include "net/minecraft/world/ArrayWithLength.h"

class BlockPos;
class CompoundTag;
class ItemInstance;

class DataInputStream : public InputStream, public DataInput {
public:
    DataInputStream(InputStream*);
    virtual ~DataInputStream();
    virtual int read();
    virtual int read(arrayWithLength<unsigned char>);
    virtual int read(arrayWithLength<unsigned char>, unsigned int, unsigned int);
    virtual void close();
    virtual long long skip(long long);
    virtual bool readBoolean();
    virtual unsigned char readByte();
    virtual unsigned char readUnsignedByte();
    virtual int readUnsignedShort();
    virtual wchar_t readChar();
    virtual void readFully(arrayWithLength<char>);
    virtual void readFully(arrayWithLength<unsigned char>);
    virtual void readBytes(arrayWithLength<unsigned char>);
    virtual double readDouble();
    virtual float readFloat();
    virtual int readInt();
    virtual long readLong();
    virtual short readShort();
    virtual std::wstring readUTF();
    virtual void readUTFChar();
    virtual PlayerUID readPlayerUID();
    virtual void skipBytes(long long);

    int readVarInt();
    long readVarLong();
    BlockPos readBlockPos();
    BlockPos* readBlockPosPointer();
    not_null_ptr<ItemInstance> readItem();
    CompoundTag* readNbt();

    InputStream* mInputStream;
};
