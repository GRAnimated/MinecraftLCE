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

    int read() override;
    int read(arrayWithLength<unsigned char>) override;
    int read(arrayWithLength<unsigned char>, unsigned int, unsigned int) override;
    void close() override;
    long long skip(long long) override;

    bool readBoolean() override;
    unsigned char readByte() override;
    unsigned char readUnsignedByte() override;
    int readUnsignedShort() override;
    wchar_t readChar() override;
    void readFully(arrayWithLength<unsigned char>) override;
    void readFully(arrayWithLength<char>) override;
    void readBytes(arrayWithLength<unsigned char>) override;
    double readDouble() override;
    float readFloat() override;
    int readInt() override;
    long readLong() override;
    short readShort() override;
    std::wstring readUTF() override;
    int readUTFChar() override;
    PlayerUID readPlayerUID() override;
    void skipBytes(long long) override;

    int readVarInt();
    long readVarLong();
    BlockPos readBlockPos();
    BlockPos* readBlockPosPointer();
    not_null_ptr<ItemInstance> readItem();
    CompoundTag* readNbt();

    InputStream* mInputStream;
};