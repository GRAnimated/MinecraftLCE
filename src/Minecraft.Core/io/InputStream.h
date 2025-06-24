#pragma once

#include "Minecraft.World/ArrayWithLength.h"

class InputStream {
public:
    InputStream() {}

    virtual ~InputStream() {}
    virtual int read() = 0;
    virtual int read(arrayWithLength<unsigned char>) = 0;
    virtual int read(arrayWithLength<unsigned char>, unsigned int, unsigned int) = 0;
    virtual void close() = 0;
    virtual long long skip(long long) = 0;
};
