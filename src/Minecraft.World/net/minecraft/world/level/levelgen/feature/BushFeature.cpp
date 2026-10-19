#include "net/minecraft/world/level/levelgen/feature/BushFeature.h"

#include "net/minecraft/core/BlockPos.h"
#include "net/minecraft/world/Random.h"
#include "net/minecraft/world/level/Level.h"
#include "net/minecraft/world/level/block/Bush.h"
#include "net/minecraft/world/level/dimension/Dimension.h"

BushFeature::BushFeature(Bush* bush) : Feature(false), m_bush(bush) {}

BushFeature::~BushFeature() {}

// name guessed
bool BushFeature::place(Level* level, Random& random, const BlockPos& pos) {
    for (int attempt = 0; attempt < 64; ++attempt) {
        BlockPos candidate
            = pos.offset(random.nextInt(8) - random.nextInt(8), random.nextInt(4) - random.nextInt(4),
                         random.nextInt(8) - random.nextInt(8));
        if (level->isEmptyBlock(candidate) && (!level->m_dimension->isHasCeiling() || candidate.getY() < 127)
            && m_bush->canSurvive(level, candidate, m_bush->defaultBlockState())) {
            level->setBlock(candidate, m_bush->defaultBlockState(), 2, false);
        }
    }
    return true;
}
