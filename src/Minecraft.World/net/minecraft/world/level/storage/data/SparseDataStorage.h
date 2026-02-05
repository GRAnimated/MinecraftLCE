#pragma once

#include "NX/Platform.h"
#include "XLockFreeStack.h"
#include "java/io/DataOutputStream.h"

class SparseDataStorage {
public:
    static unsigned int sStackLength;
    static XLockFreeStack<unsigned char> sStack[3];
    static unsigned int sLength;  // ?

    void write(DataOutputStream* out);
    void tick();
    static void staticCtor();

    // again????
    static void free(unsigned char* data, int len) {
        XPhysicalFree(data);
        sLength -= len;
    }

    // 0x7100359E44
    // do they just keep copying these 2 methods everywhere???
    void *alloc(int len) {
        sLength += len;
        return malloc(len);
    }
};
