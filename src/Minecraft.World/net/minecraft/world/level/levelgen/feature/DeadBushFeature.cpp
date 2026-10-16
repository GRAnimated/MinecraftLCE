#include "net/minecraft/world/level/levelgen/feature/DeadBushFeature.h"

#include "net/minecraft/core/BlockPos.h"
#include "net/minecraft/world/Random.h"
#include "net/minecraft/world/level/Level.h"
#include "net/minecraft/world/level/block/Blocks.h"
#include "net/minecraft/world/level/block/Bush.h"
#include "net/minecraft/world/level/block/state/BlockState.h"
#include "net/minecraft/world/level/material/Material.h"

DeadBushFeature::DeadBushFeature(Block*) : Feature(false) {}

bool DeadBushFeature::place(Level* level, Random& random, const BlockPos& origin) {
    BlockPos pos = origin;
    const BlockState* state = level->getBlockState(pos);
    while ((state->getMaterial() == Material::AIR || state->getMaterial() == Material::LEAVES)
           && pos.getY() > 0) {
        pos = pos.below();
        state = level->getBlockState(pos);
    }

    for (int attempt = 0; attempt < 4; ++attempt) {
        BlockPos candidate
            = pos.offset(random.nextInt(8) - random.nextInt(8), random.nextInt(4) - random.nextInt(4),
                         random.nextInt(8) - random.nextInt(8));
        if (level->isEmptyBlock(candidate)
            && static_cast<Bush*>(Blocks::DEADBUSH)
                   ->canSurvive(level, candidate, Blocks::DEADBUSH->defaultBlockState())) {
            level->setBlock(candidate, Blocks::DEADBUSH->defaultBlockState(), 2, false);
        }
    }
    return true;
}
