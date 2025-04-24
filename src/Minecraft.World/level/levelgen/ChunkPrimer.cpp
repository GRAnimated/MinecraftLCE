#include "Minecraft.World/level/levelgen/ChunkPrimer.h"

#include "Minecraft.Client/resources/IdMapper.h"
#include "Minecraft.World/level/block/Blocks.h"

ChunkPrimer::ChunkPrimer(bool unk, arrayWithLength<uchar> blockIds, arrayWithLength<uchar> blockData) {
    mBlockIds = blockIds;
    mBlockData = blockData;
    mAirBlock = Blocks::AIR->defaultBlockState();
    byte_28 = unk;
}

ChunkPrimer::~ChunkPrimer() {
    if (byte_28) {
        if (mBlockIds.data)
            delete mBlockIds.data;
        if (mBlockData.data)
            delete mBlockData.data;
    }
}

// NON_MATCHING: CMP 0x1 vs CMP 0x0
const BlockState* ChunkPrimer::getState(int a2) {
    int packedPos = a2 <= 0 ? a2 + 1 : a2;

    int blockDataIndex = packedPos >> 1;

    int bitShift = 4 * (a2 & 1);

    return Block::getStateByIdAndData(mBlockIds[a2], (mBlockData[blockDataIndex] >> bitShift) & 0xF);
}

const BlockState* ChunkPrimer::getState(int x, int y, int z) {
    int v5 = 0;
    if (mBlockIds.length > 0x8000u && y >= 128) {
        y -= 128;
        v5 = 0x8000;
    }
    int packedPos = v5 + ((x << 11) | (z << 7) | y);
    return getState(packedPos);
}

// NON_MATCHING
void ChunkPrimer::setState(int packedPos, const BlockState* state) {
    int id = 0;
    int data = 0;

    if (state) {
        int stateId = sBlockStateMapper->getId(state);
        id = stateId >> 0x4;
        data = stateId & 0xF;
    }

    mBlockIds[packedPos] = id;

    int test = packedPos / 2;

    if (packedPos & 1)
        mBlockData[test] = (mBlockData[test] & 0xF) | (16 * data);
    else
        mBlockData[test] = (mBlockData[test] & 0xF0) | data;
}

void ChunkPrimer::setState(int x, int y, int z, BlockState const* state) {
    int v5 = 0;
    if (mBlockIds.length > 0x8000u && y >= 128) {
        y -= 128;
        v5 = 0x8000;
    }
    int packedPos = v5 + ((x << 11) | (z << 7) | y);
    setState(packedPos, state);
}

// NON_MATCHING: CMP 0x1 vs CMP 0x0
void ChunkPrimer::setBlockAndData(int packedPos, int id, int data) {
    mBlockIds[packedPos] = id;

    int v9 = (packedPos <= 0) ? (packedPos + 1) : packedPos;

    int test = v9 >> 1;

    if (packedPos & 1)
        mBlockData[test] = (mBlockData[test] & 0xF) | (16 * data);
    else
        mBlockData[test] = (mBlockData[test] & 0xF0) | data;
}

int ChunkPrimer::getBlockId(int a) {
    return mBlockIds[a];
}

arrayWithLength<uchar> ChunkPrimer::getBlockIds() {
    return mBlockIds;
}

arrayWithLength<uchar> ChunkPrimer::getBlockData() {
    return mBlockData;
}

// TODO: Find out what this function is
Block* sub_7100029D84(unsigned char);

int ChunkPrimer::getHighestNonAirPos(int x, int z) {
    int packedXZ = (x << 11) | (z << 7) | 1;

    for (int y = 127; y >= 0; y--) {
        if (sub_7100029D84(mBlockIds[packedXZ + y + 126]) != Blocks::AIR) {
            return y;
        }
    }
    return 0;
}
