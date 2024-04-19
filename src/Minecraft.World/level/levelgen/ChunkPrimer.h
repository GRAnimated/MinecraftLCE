#pragma once

#include "Minecraft.World/ArrayWithLength.h"

class BlockState;

class ChunkPrimer {
public:
    ChunkPrimer(bool, arrayWithLength<unsigned char>, arrayWithLength<unsigned char>);
    ~ChunkPrimer();
    void getState(int, int, int);
    void setState(int, BlockState const*);
    void setState(int, int, int, BlockState const*);
    void setBlockAndData(int, int, int);
    void getBlockId(int);
    void getBlockIds();
    void getBlockData();
    void getHighestNonAirPos(int, int);
};