#pragma once

#include "types.h"
#include "Minecraft.World/ArrayWithLength.h"
#include "Minecraft.Core/io/OutputStream.h"

class ByteArrayOutputStream : public OutputStream {
public:
    ByteArrayOutputStream();
    ByteArrayOutputStream(unsigned int);

    virtual ~ByteArrayOutputStream() override;
    virtual void write(unsigned int) override;
    virtual void write(arrayWithLength<unsigned char>) override;
    virtual void write(arrayWithLength<unsigned char>, unsigned int, unsigned int) override;
    virtual void close() override;
    virtual void flush() override;
    virtual arrayWithLength<uchar> toByteArray();

    unsigned int size();
    void clear();

    arrayWithLength<unsigned char> mBuffer;
    unsigned int mSize;
};
