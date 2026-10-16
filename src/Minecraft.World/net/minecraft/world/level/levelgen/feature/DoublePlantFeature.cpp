#include "net/minecraft/world/level/levelgen/feature/DoublePlantFeature.h"

#include "net/minecraft/core/BlockPos.h"
#include "net/minecraft/world/Random.h"
#include "net/minecraft/world/level/Level.h"
#include "net/minecraft/world/level/block/Blocks.h"
#include "net/minecraft/world/level/dimension/Dimension.h"

DoublePlantFeature::DoublePlantFeature() : Feature(false) {}

DoublePlantFeature::~DoublePlantFeature() = default;

void DoublePlantFeature::setNextPlantType(DoublePlantBlock::Variant* type) {
    m_type = type;
}

bool DoublePlantFeature::place(Level* level, Random& random, const BlockPos& origin) {
    bool placed = false;
    for (int attempt = 0; attempt < 64; ++attempt) {
        BlockPos candidate
            = origin.offset(random.nextInt(8) - random.nextInt(8), random.nextInt(4) - random.nextInt(4),
                            random.nextInt(8) - random.nextInt(8));
        if (level->isEmptyBlock(candidate) && (!level->m_dimension->isHasCeiling() || candidate.getY() < 126)
            && Blocks::DOUBLE_PLANT->mayPlace(level, candidate)) {
            static_cast<DoublePlantBlock*>(Blocks::DOUBLE_PLANT)->placeAt(level, candidate, m_type, 2);
            placed = true;
        }
    }
    return placed;
}
