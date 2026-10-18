#include "net/minecraft/world/level/levelgen/feature/DesertWellFeature.h"

#include "net/minecraft/core/BlockPos.h"
#include "net/minecraft/core/Direction.h"
#include "net/minecraft/world/level/Level.h"
#include "net/minecraft/world/level/block/Blocks.h"
#include "net/minecraft/world/level/block/HalfSlabBlock.h"
#include "net/minecraft/world/level/block/SandBlock.h"
#include "net/minecraft/world/level/block/StoneSlabBlock.h"
#include "net/minecraft/world/level/block/state/BlockState.h"
#include "net/minecraft/world/level/block/state/BlockStatePredicate.h"

Predicate<const BlockState*>* DesertWellFeature::SAND_PREDICATE;

void DesertWellFeature::staticCtor() {
    BlockStatePredicate* predicate = BlockStatePredicate::forBlock(Blocks::SAND);
    SAND_PREDICATE = predicate->where(SandBlock::VARIANT,
                                      Predicates<SandBlock::Variant*>::equalTo(SandBlock::Variant::DEFAULT));
}

DesertWellFeature::DesertWellFeature() : Feature(false) {
    m_slab = Blocks::STONE_SLAB->defaultBlockState()
                 ->setValue(StoneSlabBlock::VARIANT, StoneSlabBlock::Variant::SANDSTONE)
                 ->setValue(HalfSlabBlock::VARIANT, HalfSlabBlock::Half::BOTTOM);
    m_sandstone = Blocks::SANDSTONE->defaultBlockState();
    m_water = Blocks::FLOWING_WATER->defaultBlockState();
}

// Keep the original query/write order, including writes later overwritten by slabs.
bool DesertWellFeature::place(Level* level, Random&, const BlockPos& origin) {
    BlockPos pos = origin;
    while (level->isEmptyBlock(pos) && pos.getY() > 2)
        pos = pos.below();

    if (!SAND_PREDICATE->apply(level->getBlockState(pos)))
        return false;

    for (int x = -2; x <= 2; x++) {
        for (int z = -2; z <= 2; z++) {
            if (level->isEmptyBlock(pos.offset(x, -1, z)) && level->isEmptyBlock(pos.offset(x, -2, z)))
                return false;
        }
    }

    for (int y = -1; y <= 0; y++) {
        for (int x = -2; x <= 2; x++) {
            for (int z = -2; z <= 2; z++)
                level->setBlock(pos.offset(x, y, z), m_sandstone, 2, false);
        }
    }
    level->setBlock(pos, m_water, 2, false);
    auto directions = Direction::Plane::HORIZONTAL->iterator();
    for (unsigned int i = 0; i < directions.m_length; i++) {
        const Direction* direction = directions[i];
        level->setBlock(pos.relative(direction), m_water, 2, false);
    }

    for (int x = -2; x <= 2; x++) {
        for (int z = -2; z <= 2; z++) {
            if (x == -2 || x == 2 || z == -2 || z == 2)
                level->setBlock(pos.offset(x, 1, z), m_sandstone, 2, false);
        }
    }
    level->setBlock(pos.offset(2, 1, 0), m_slab, 2, false);
    level->setBlock(pos.offset(-2, 1, 0), m_slab, 2, false);
    level->setBlock(pos.offset(0, 1, 2), m_slab, 2, false);
    level->setBlock(pos.offset(0, 1, -2), m_slab, 2, false);

    for (int x = -1; x <= 1; x++) {
        for (int z = -1; z <= 1; z++) {
            if (x == 0 && z == 0)
                level->setBlock(pos.offset(x, 4, z), m_sandstone, 2, false);
            else
                level->setBlock(pos.offset(x, 4, z), m_slab, 2, false);
        }
    }
    for (int y = 1; y <= 3; y++) {
        level->setBlock(pos.offset(-1, y, -1), m_sandstone, 2, false);
        level->setBlock(pos.offset(-1, y, 1), m_sandstone, 2, false);
        level->setBlock(pos.offset(1, y, -1), m_sandstone, 2, false);
        level->setBlock(pos.offset(1, y, 1), m_sandstone, 2, false);
    }
    return true;
}
