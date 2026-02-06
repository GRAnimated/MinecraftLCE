#pragma once

#include "XLockFreeStack.h"
#include "java/io/DataOutputStream.h"

class SparseLightStorage {
public:
    static unsigned int sStackLength;
    static XLockFreeStack<unsigned char> sStack[3];
    static unsigned int sLength;  // ?

    void write(DataOutputStream* out);

    static void staticCtor();
    void tick();
    bool isCompressed();

    // again????
    static void free(unsigned char* data, int len) {
        XPhysicalFree(data);
        sLength -= len;
    }

    // 0x710035BC18
    // do they just keep copying these 2 methods everywhere???
    static void* alloc(int len) {
        sLength += len;
        return malloc(len);
    }

    std::atomic<unsigned long*> m_light;
};
