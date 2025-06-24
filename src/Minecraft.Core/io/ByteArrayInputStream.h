#pragma once

#include "Minecraft.Core/io/InputStream.h"

class ByteArrayInputStream : public InputStream {
public:
    ByteArrayInputStream(arrayWithLength<unsigned char> array, unsigned int start, unsigned int length);
    ByteArrayInputStream(arrayWithLength<unsigned char> array);

    virtual ~ByteArrayInputStream() override;
    virtual int read() override;
    virtual int read(arrayWithLength<unsigned char>) override;
    virtual int read(arrayWithLength<unsigned char>, unsigned int, unsigned int) override;
    virtual void close() override;
    virtual long long skip(long long) override;

    arrayWithLength<unsigned char> mBuffer;
    unsigned int mLength;
    unsigned int mCurrentPos;
    unsigned int mNextPos;
};
