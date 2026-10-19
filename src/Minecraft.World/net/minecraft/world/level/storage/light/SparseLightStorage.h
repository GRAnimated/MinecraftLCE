#pragma once

#include "java/io/DataOutputStream.h"
#include <vector>

class DataInputStream;
template <typename T>
class XLockFreeStack;

class SparseLightStorage {
public:
    SparseLightStorage(bool bright);
    SparseLightStorage(bool bright, bool compact);
    SparseLightStorage(const SparseLightStorage&);
    ~SparseLightStorage();

    void fromNibbles(arrayWithLength<unsigned char>, int offset);
    void toNibbles(arrayWithLength<unsigned char>, unsigned int offset);
    unsigned char getLight(int x, int y, int z);
    void setLight(int x, int y, int z, int value);
    void setFullBright();
    int setDataRegion(arrayWithLength<unsigned char>, int x0, int y0, int z0, int x1, int y1, int z1,
                      int offset);
    int getDataRegion(arrayWithLength<unsigned char>, int x0, int y0, int z0, int x1, int y1, int z1,
                      int offset);
    unsigned int compress();
    bool isCompressed();
    void write(DataOutputStream* out);
    void read(DataInputStream* in);

    static void staticCtor();
    static void tick();

private:
    static unsigned char* allocate(unsigned int);
    static void freeBuffer(unsigned char*, int);
    int bufferSize(unsigned long long);
    void getBuffers(unsigned char** indices, unsigned char** data);
    void replace(unsigned long long);
    void expandLayers(std::vector<int>&);
    void retire(unsigned char*);
    static int sRetirementSlot;
    static XLockFreeStack<unsigned char> sRetired[3];

    /** Low 48 bits: buffer pointer; high 16 bits: number of explicit 128-byte slabs.
     */
    unsigned long long m_packed;
};

static_assert(sizeof(SparseLightStorage) == 8, "SparseLightStorage Switch layout");
