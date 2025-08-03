#include "net/minecraft/world/level/levelgen/ChunkPrimer.h"

#include "net/minecraft/client/resources/IdMapper.h"
#include "net/minecraft/world/level/block/Blocks.h"

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

const BlockState* ChunkPrimer::getState(int packedPos) {
    int index = packedPos / 2;

    int bitShift = 4 * (packedPos & 1);

    return Block::getStateByIdAndData(mBlockIds[packedPos], (mBlockData[index] >> bitShift) & 0xF);
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

void ChunkPrimer::setState(int packedPos, const BlockState* state) {
    unsigned int id = 0;
    unsigned char lowerNibble = 0;
    unsigned char upperNibble = 0;

    if (state) {
        id = sBlockStateMapper->getId(state);
        upperNibble = id / 16;
        lowerNibble = id & 0xF;
    }

    mBlockIds[packedPos] = upperNibble;

    int dataIndex = packedPos / 2;

    unsigned char currentValue = mBlockData[dataIndex];

    if (packedPos & 1) {
        currentValue = (currentValue & 0x0F) | (lowerNibble << 4);
    } else {
        currentValue = (currentValue & 0xF0) | lowerNibble;
    }

    mBlockData[dataIndex] = currentValue;
}

void ChunkPrimer::setState(int x, int y, int z, const BlockState* state) {
    int v5 = 0;
    if (mBlockIds.length > 0x8000u && y >= 128) {
        y -= 128;
        v5 = 0x8000;
    }
    int packedPos = v5 + ((x << 11) | (z << 7) | y);
    setState(packedPos, state);
}

void ChunkPrimer::setBlockAndData(int packedPos, int id, int data) {
    mBlockIds[packedPos] = id;

    int index = packedPos / 2;

    if (packedPos & 1)
        mBlockData[index] = (mBlockData[index] & 0xF) | (data << 4);
    else
        mBlockData[index] = (mBlockData[index] & 0xF0) | data;
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

int ChunkPrimer::getHighestNonAirPos(int x, int z) {
    int packedXZ = (x << 11) | (z << 7) | 1;

    for (int y = 127; y >= 0; y--) {
        if (Block::byId(mBlockIds[packedXZ + y + 126]) != Blocks::AIR) {
            return y;
        }
    }
    return 0;
}
