#include "net/minecraft/world/level/levelgen/feature/ReedsFeature.h"

#include "net/minecraft/client/CMinecraftApp.h"
#include "net/minecraft/core/BlockPos.h"
#include "net/minecraft/world/Random.h"
#include "net/minecraft/world/level/Level.h"
#include "net/minecraft/world/level/block/Blocks.h"
#include "net/minecraft/world/level/block/ReedsBlock.h"
#include "net/minecraft/world/level/block/state/BlockState.h"
#include "net/minecraft/world/level/material/Material.h"

bool ReedsFeature::place(Level* level, Random& random, const BlockPos& pos) {
    for (int attempt = 0; attempt < 20; ++attempt) {
        BlockPos candidate
            = pos.offset(random.nextInt(4) - random.nextInt(4), 0, random.nextInt(4) - random.nextInt(4));
        if (CConsoleMinecraftApp::sInstance.getLevelGenerationOptions()
            && CConsoleMinecraftApp::sInstance.getLevelGenerationOptions()->intersects(candidate, candidate))
            continue;

        if (level->isEmptyBlock(candidate)) {
            BlockPos below = candidate.below();
            if (level->getBlockState(below.west())->getMaterial() == Material::WATER
                || level->getBlockState(below.east())->getMaterial() == Material::WATER
                || level->getBlockState(below.north())->getMaterial() == Material::WATER
                || level->getBlockState(below.south())->getMaterial() == Material::WATER) {
                int height = 2 + random.nextInt(random.nextInt(3) + 1);
                for (int y = 0; y < height; ++y) {
                    if (static_cast<ReedsBlock*>(Blocks::REEDS)->canSurvive(level, candidate))
                        level->setBlock(candidate.above(y), Blocks::REEDS->defaultBlockState(), 2, false);
                }
            }
        }
    }
    return true;
}
