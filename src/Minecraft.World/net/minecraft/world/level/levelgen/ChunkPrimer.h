#pragma once

#include "net/minecraft/world/ArrayWithLength.h"
#include "types.h"

class BlockState;

class ChunkPrimer {
public:
    ChunkPrimer(bool, arrayWithLength<uchar>, arrayWithLength<uchar>);
    ~ChunkPrimer();
    const BlockState* getState(int);
    const BlockState* getState(int, int, int);
    void setState(int, const BlockState*);
    void setState(int, int, int, const BlockState*);
    void setBlockAndData(int, int, int);
    int getBlockId(int);
    arrayWithLength<uchar> getBlockIds();
    arrayWithLength<uchar> getBlockData();
    int getHighestNonAirPos(int, int);

private:
    arrayWithLength<uchar> m_blockIds;
    arrayWithLength<uchar> m_blockData;
    const BlockState* m_airBlock;
    bool m_byte28;
};
