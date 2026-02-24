#pragma once

#include "java/io/OutputStream.h"
#include "net/minecraft/world/ArrayWithLength.h"
#include "types.h"

class ByteArrayOutputStream : public OutputStream {
public:
    ByteArrayOutputStream();
    ByteArrayOutputStream(unsigned int);

    ~ByteArrayOutputStream() override;
    void write(unsigned int) override;
    void write(arrayWithLength<unsigned char>) override;
    void write(arrayWithLength<unsigned char>, unsigned int, unsigned int) override;
    void close() override;
    void flush() override;
    virtual arrayWithLength<uchar> toByteArray();

    unsigned int size();
    void clear();

    arrayWithLength<unsigned char> m_buffer;
    unsigned int m_size;
};
