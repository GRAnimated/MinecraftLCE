#include "net/minecraft/world/level/levelgen/feature/MelonFeature.h"

#include "net/minecraft/core/BlockPos.h"
#include "net/minecraft/world/Random.h"
#include "net/minecraft/world/level/Level.h"
#include "net/minecraft/world/level/block/Blocks.h"

MelonFeature::MelonFeature() : Feature(false) {}
MelonFeature::~MelonFeature() = default;

bool MelonFeature::place(Level* level, Random& random, const BlockPos& origin) {
    for (int i = 0; i < 64; ++i) {
        int x = random.nextInt(8) - random.nextInt(8);
        int y = random.nextInt(4) - random.nextInt(4);
        int z = random.nextInt(8) - random.nextInt(8);
        BlockPos candidate = origin.offset(x, y, z);
        if (Blocks::MELON_BLOCK->mayPlace(level, candidate)
            && level->getBlockState(candidate.below())->getBlock() == Blocks::GRASS)
            level->setBlock(candidate, Blocks::MELON_BLOCK->defaultBlockState(), 2, false);
    }
    return true;
}
