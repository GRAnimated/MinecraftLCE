#pragma once

#include "Minecraft.World/ArrayWithLength.h"

class InputStream {
public:
    virtual ~InputStream();
    virtual unsigned int read() = 0;
    virtual void read(arrayWithLength<unsigned char>) = 0;
    virtual void read(arrayWithLength<unsigned char>, unsigned int, unsigned int) = 0;
    virtual void close() = 0;
    virtual void skip(long long) = 0;
};
