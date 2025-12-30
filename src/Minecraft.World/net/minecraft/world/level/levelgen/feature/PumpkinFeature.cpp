#include "net/minecraft/world/level/levelgen/feature/PumpkinFeature.h"

#include "net/minecraft/core/BlockPos.h"
#include "net/minecraft/core/Direction.h"
#include "net/minecraft/world/Random.h"
#include "net/minecraft/world/level/Level.h"
#include "net/minecraft/world/level/block/Blocks.h"
#include "net/minecraft/world/level/block/PumpkinBlock.h"
#include "net/minecraft/world/level/block/state/BlockState.h"
#include "net/minecraft/world/level/levelgen/feature/Feature.h"

PumpkinFeature::PumpkinFeature() : Feature(false) {}

bool PumpkinFeature::place(Level* level, Random& rand, const BlockPos& pos) {
    for (int i = 0; i < 64; ++i) {
        BlockPos temp = pos.offset(rand.nextInt(8) - rand.nextInt(8), rand.nextInt(4) - rand.nextInt(4),
                                   rand.nextInt(8) - rand.nextInt(8));
        if (level->isEmptyBlock(temp) && level->getBlockState(temp.below())->getBlock() == Blocks::GRASS
            && Blocks::PUMPKIN->mayPlace(level, temp)) {
            level->setBlock(temp,
                            Blocks::PUMPKIN->defaultBlockState()->setValue(
                                PumpkinBlock::AXIS, Direction::Plane::HORIZONTAL->getRandomDirection(rand)),
                            2, false);
        }
    }

    return true;
}
