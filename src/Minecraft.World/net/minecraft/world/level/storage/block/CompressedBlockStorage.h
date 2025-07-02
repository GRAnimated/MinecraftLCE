#pragma once

#include "net/minecraft/world/ArrayWithLength.h"

class DataInputStream;
class DataOutputStream;

class CompressedBlockStorage {
public:
    static void staticCtor();

    CompressedBlockStorage(arrayWithLength<unsigned char>, unsigned int);
    CompressedBlockStorage(bool);

    void write(DataOutputStream*);
    void read(DataInputStream*);
    void compress();

    int get(int x, int y, int z);
    void set(int x, int y, int z, int id);
    void tick();

    arrayWithLength<unsigned char> storage;
};
