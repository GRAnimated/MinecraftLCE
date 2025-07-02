#pragma once

#include "java/io/OutputStream.h"

class BufferedOutputStream : public OutputStream {
public:
    BufferedOutputStream(OutputStream* outputStream, int bufferSize);

    virtual ~BufferedOutputStream() override;
    virtual void write(unsigned int) override;
    virtual void write(arrayWithLength<unsigned char>) override;
    virtual void write(arrayWithLength<unsigned char>, unsigned int, unsigned int) override;
    virtual void close() override;
    virtual void flush() override;

    OutputStream* mOutputStream;
    arrayWithLength<unsigned char> mBuffer;
    unsigned int mSize;
};
