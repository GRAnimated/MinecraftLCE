#include "net/minecraft/world/level/levelgen/feature/HellFireFeature.h"

#include "net/minecraft/core/BlockPos.h"
#include "net/minecraft/world/Random.h"
#include "net/minecraft/world/level/Level.h"
#include "net/minecraft/world/level/block/Blocks.h"
#include "net/minecraft/world/level/block/state/BlockState.h"

HellFireFeature::HellFireFeature() : Feature(false) {}

bool HellFireFeature::place(Level* level, Random& random, const BlockPos& pos) {
    for (int i = 0; i < 64; i++) {
        BlockPos pos2
            = pos.offset(random.nextInt(8) - random.nextInt(8), random.nextInt(4) - random.nextInt(4),
                         random.nextInt(8) - random.nextInt(8));
        if (!level->isEmptyBlock(pos2)
            || level->getBlockState(pos2.below())->getBlock() != Blocks::NETHERRACK)
            continue;
        level->setBlock(pos2, Blocks::FIRE->defaultBlockState(), 2, false);
    }
    return true;
}
