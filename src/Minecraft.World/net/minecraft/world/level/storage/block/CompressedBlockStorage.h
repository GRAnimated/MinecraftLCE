#pragma once

#include "NX/Platform.h"
#include "XLockFreeStack.h"
#include "net/minecraft/world/ArrayWithLength.h"
#include "nn/os/os_MutexTypes.h"

class DataInputStream;
class DataOutputStream;

class CompressedBlockStorage {
public:
    static unsigned int sStackLength;
    static XLockFreeStack<unsigned char> sStack[3];
    static unsigned int sLength;  // ?

    static void staticCtor();

    CompressedBlockStorage(arrayWithLength<unsigned char>, unsigned int);
    CompressedBlockStorage(bool);
    CompressedBlockStorage(CompressedBlockStorage*);
    CompressedBlockStorage();

    void write(DataOutputStream*);
    void read(DataInputStream* s);
    void compress(int);

    static void free(unsigned char* data, int len) {
        XPhysicalFree(data);
        sLength -= len;
    }

    static unsigned char* create(unsigned int a1, unsigned int a2) {
        unsigned int len = a1;

        if (a2)
            len = a2;

        unsigned char* data = static_cast<unsigned char*>(XPhysicalAlloc(a1, ULONG_MAX, 0x1000, 4));
        sLength += len;

        return data;
    }

    int get(int x, int y, int z);
    void set(int x, int y, int z, int id);
    void tick();

    void getDataRegion(arrayWithLength<unsigned char>, int, int, int, int, int, int, int);  // unk return type
    void getData(arrayWithLength<unsigned char>, unsigned int, int, int);  // unk return type 2

    void setDataRegion(arrayWithLength<unsigned char>, int, int, int, int, int, int, int,
                       void (*)(int, int, int, void*, int), void*, int);
    void setData(arrayWithLength<unsigned char>, unsigned int);

    void queueForDelete(unsigned char*, int);
    void reverseIndices(unsigned char*);

    int getHighestNonEmptyY();

    bool isCompressed();
    bool isRenderChunkEmpty(int);
    bool isSameAs(CompressedBlockStorage* rhs);  // never heard of operator==

    void testSetDataRegion(arrayWithLength<unsigned char>, int, int, int, int, int, int, int, bool*);

    // made up name
    static void getIndexes(int* gridIdx, int* blockIdx, int x, int y, int z) {
        const int gX = (32 * x) & 0x180;
        const int gY = y >> 2;
        const int gZ = (8 * z) & 0x60;
        *gridIdx = gX | gY | gZ;

        // yxz?
        const int bY = y & 3;
        const int bX = 16 * (x & 3);
        const int bZ = 4 * (z & 3);
        *blockIdx = bY | bX | bZ;
    }

    unsigned char* mData;
    int mLength;

    static nn::os::MutexType sMutex;
};
