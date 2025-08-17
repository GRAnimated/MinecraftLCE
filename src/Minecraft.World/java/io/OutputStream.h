#pragma once

#include "net/minecraft/world/ArrayWithLength.h"

class OutputStream {
public:
    OutputStream() {}

    virtual ~OutputStream() {}
    virtual void write(unsigned int) = 0;
    virtual void write(arrayWithLength<unsigned char>) = 0;
    virtual void write(arrayWithLength<unsigned char>, unsigned int, unsigned int) = 0;
    virtual void close() = 0;
    virtual void flush() = 0;
};
