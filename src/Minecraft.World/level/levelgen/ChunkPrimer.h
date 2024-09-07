#pragma once

#include "Minecraft.World/ArrayWithLength.h"
#include "types.h"

class BlockState;

class ChunkPrimer {
public:
    ChunkPrimer(bool, arrayWithLength<uchar>, arrayWithLength<uchar>);
    ~ChunkPrimer();
    const BlockState* getState(int, int, int);
    void setState(int, BlockState const*);
    void setState(int, int, int, BlockState const*);
    void setBlockAndData(int, int, int);
    int getBlockId(int);
    arrayWithLength<uchar> getBlockIds();
    arrayWithLength<uchar> getBlockData();
    int getHighestNonAirPos(int, int);

private:
    arrayWithLength<uchar> mBlockIds;
    arrayWithLength<uchar> mBlockData;
    const BlockState* mAirBlock;
    bool byte_28;
};
