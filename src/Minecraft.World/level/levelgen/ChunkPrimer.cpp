#include "Minecraft.World/level/levelgen/ChunkPrimer.h"
#include "Minecraft.World/level/block/Blocks.h"

ChunkPrimer::ChunkPrimer(bool unk, arrayWithLength<uchar> blockIds, arrayWithLength<uchar> blockData) {
    mBlockIds = blockIds;
    mBlockData = blockData;
    mAirBlock = Blocks::AIR->defaultBlockState();
    byte_28 = unk;
}

// NON_MATCHING: CMP 0x1 vs CMP 0x0
const BlockState* ChunkPrimer::getState(int x, int y, int z) {
    int packedPos = x <= 0 ? x + 1 : x;

    int blockDataIndex = packedPos >> 1;

    int bitShift = 4 * (x & 1);

    return Block::getStateByIdAndData(mBlockIds.get(x), (mBlockData.get(blockDataIndex) >> bitShift) & 0xF);
}

// void ChunkPrimer::setState(int a, BlockState const* state);

void ChunkPrimer::setState(int x, int y, int z, BlockState const* state) {
    int v5 = 0;
    if (mBlockIds.length > 0x8000u && y >= 128) {
        y -= 128;
        v5 = 0x8000;
    }
    int packedPos = v5 + ((x << 11) | (z << 7) | y);
    setState(packedPos, state);
}

// void setBlockAndData(int, int, int);

int ChunkPrimer::getBlockId(int a) {
    return mBlockIds.get(a);
}

arrayWithLength<uchar> ChunkPrimer::getBlockData() {
    return mBlockData;
}

arrayWithLength<uchar> ChunkPrimer::getBlockIds() {
    return mBlockIds;
}

// TODO: Find out what this function is
Block* sub_7100029D84(unsigned char);

// NON_MATCHING: packedXZ regswap
int ChunkPrimer::getHighestNonAirPos(int x, int z) {
    int packedXZ = (x << 11) | (z << 7);

    for (int y = 127; y >= 0; y--) {
        if (sub_7100029D84(mBlockIds.get(packedXZ + y + 127)) != Blocks::AIR) {
            return y;
        }
    }
    return 0;
}
