#include "Minecraft.World/level/Level.h"
#include "Minecraft.World/level/block/Blocks.h"
#include "Minecraft.World/level/chunk/LevelChunk.h"

const BlockState* Level::getBlockState(const BlockPos& pos) {
    if (isOutsideBuildHeight(pos))
        return Blocks::AIR->defaultBlockState();
    return getChunkAt(pos)->getBlockState(pos);
}
