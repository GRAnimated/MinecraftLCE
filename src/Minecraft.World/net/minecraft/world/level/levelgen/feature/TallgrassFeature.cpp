#include "net/minecraft/world/level/levelgen/feature/TallgrassFeature.h"

#include "net/minecraft/core/BlockPos.h"
#include "net/minecraft/world/Random.h"
#include "net/minecraft/world/level/Level.h"
#include "net/minecraft/world/level/block/Blocks.h"
#include "net/minecraft/world/level/block/state/BlockState.h"
#include "net/minecraft/world/level/material/Material.h"

TallgrassFeature::TallgrassFeature(TallGrassBlock::Variant* variant)
    : Feature(false),
      m_state(Blocks::TALLGRASS->defaultBlockState()->setValue(TallGrassBlock::TYPE, variant)) {}

// Descend through air and leaf materials before scattering exactly 128 attempts.
bool TallgrassFeature::place(Level* level, Random& random, const BlockPos& origin) {
    BlockPos pos = origin;
    const BlockState* state = level->getBlockState(pos);
    while ((state->getMaterial() == Material::AIR || state->getMaterial() == Material::LEAVES)
           && pos.getY() > 0) {
        pos = pos.below();
        state = level->getBlockState(pos);
    }

    for (int attempt = 0; attempt < 128; ++attempt) {
        BlockPos candidate
            = pos.offset(random.nextInt(8) - random.nextInt(8), random.nextInt(4) - random.nextInt(4),
                         random.nextInt(8) - random.nextInt(8));
        if (level->isEmptyBlock(candidate)
            && static_cast<TallGrassBlock*>(Blocks::TALLGRASS)->canSurvive(level, candidate, m_state)) {
            level->setBlock(candidate, m_state, 2, false);
        }
    }
    return true;
}
