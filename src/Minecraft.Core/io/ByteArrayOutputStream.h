#pragma once

#include "Minecraft.Core/io/OutputStream.h"
#include "Minecraft.World/ArrayWithLength.h"

class ByteArrayOutputStream : public OutputStream {
public:
    ByteArrayOutputStream(unsigned int);
    virtual ~ByteArrayOutputStream() override;
    virtual void write(unsigned int) override;
    virtual void write(arrayWithLength<unsigned char>) override;
    virtual void write(arrayWithLength<unsigned char>, unsigned int, unsigned int) override;
    virtual void close() override;
    virtual void flush() override;
    virtual void toByteArray();

    unsigned int size();
    void clear();

    arrayWithLength<unsigned char> mBuffer;
    unsigned int mSize;
};
