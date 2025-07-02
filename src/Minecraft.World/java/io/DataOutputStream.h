#pragma once
#include <string>

#include "java/io/DataOutput.h"
#include "java/io/OutputStream.h"
#include "java/io/types/Double.h"
#include "java/io/types/Float.h"
#include "net/minecraft/world/ArrayWithLength.h"

class BlockPos;

class DataOutputStream : public OutputStream, public DataOutput {
public:
    DataOutputStream(OutputStream*);

    virtual ~DataOutputStream();
    void write(unsigned int) override;
    void write(arrayWithLength<unsigned char>) override;
    void write(arrayWithLength<unsigned char>, unsigned int, unsigned int) override;
    void close() override;
    void flush() override;
    void writeBytes(arrayWithLength<unsigned char>) override;
    void writeByte(unsigned char) override;
    void writeDouble(double) override;
    void writeFloat(float) override;
    void writeInt(int) override;
    void writeLong(long long) override;
    void writeShort(short) override;
    void writeUnsignedShort(unsigned short) override;
    void writeChar(wchar_t) override;
    void writeChars(const std::wstring& str) override;
    void writeBoolean(bool) override;
    void writeUTF(const std::wstring&) override;
    void writePlayerUID(PlayerUID) override;

    void writeVarInt(int);
    void writeVarLong(long);
    void writeBlockPos(const BlockPos&) const;

    void deleteChildStream();

    int getSize() const { return mSize; }

    OutputStream* mOutputStream;
    int mSize;
};