#include "net/minecraft/world/level/levelgen/feature/SpringFeature.h"

#include "net/minecraft/client/CMinecraftApp.h"
#include "net/minecraft/core/BlockPos.h"
#include "net/minecraft/world/level/Level.h"
#include "net/minecraft/world/level/block/Block.h"

SpringFeature::SpringFeature(Block* block) : Feature(false), mBlock(block) {}

bool SpringFeature::place(Level* level, Random& random, const BlockPos& pos) {
    if (CConsoleMinecraftApp::sInstance.getLevelGenerationOptions()) {
        LevelGenerationOptions* options = CConsoleMinecraftApp::sInstance.getLevelGenerationOptions();
        if (options->intersects(pos, pos))
            return false;
    }

    int x = pos.getX();
    int y = pos.getY();
    int z = pos.getZ();
    if (level->getBlockId(x, y + 1, z) != 1 || level->getBlockId(x, y - 1, z) != 1)
        return false;
    if (level->getBlockId(x, y, z) != 0 && level->getBlockId(x, y, z) != 1)
        return false;

    int stoneCount = 0;
    int west = level->getBlockId(x - 1, y, z);
    if (west == 1)
        stoneCount = 1;
    else if (west != 0)
        return false;
    int east = level->getBlockId(x + 1, y, z);
    if (east != 0) {
        if (east != 1)
            return false;
        stoneCount++;
    }
    int north = level->getBlockId(x, y, z - 1);
    if (north != 0) {
        if (north != 1)
            return false;
        stoneCount++;
    }
    int south = level->getBlockId(x, y, z + 1);
    if (south != 0) {
        if (south != 1)
            return false;
        stoneCount++;
    }
    if (stoneCount == 3) {
        const BlockState* state = mBlock->defaultBlockState();
        level->setBlock(pos, state, 2, false);
        level->instaTick(pos, state, random);
    }
    return true;
}
