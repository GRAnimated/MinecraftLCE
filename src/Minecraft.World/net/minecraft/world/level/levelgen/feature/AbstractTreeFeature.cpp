#include "net/minecraft/world/level/levelgen/feature/AbstractTreeFeature.h"

#include "net/minecraft/core/Direction.h"
#include "net/minecraft/core/MutableBlockPos.h"
#include "net/minecraft/world/Random.h"
#include "net/minecraft/world/level/Level.h"
#include "net/minecraft/world/level/block/Blocks.h"
#include "net/minecraft/world/level/block/LogBlock.h"
#include "net/minecraft/world/level/block/OldLogBlock.h"
#include "net/minecraft/world/level/block/VineBlock.h"
#include "net/minecraft/world/level/block/state/BooleanProperty.h"
#include "net/minecraft/world/level/material/Material.h"

AbstractTreeFeature::AbstractTreeFeature(bool update, int minHeight, const BlockState* trunk,
                                         const BlockState* leaves, bool vines)
    : Feature(update), m_minHeight(minHeight), m_vines(vines), m_trunk(trunk), m_leaves(leaves) {}

void AbstractTreeFeature::postPlaceTree(Level*, Random&, const BlockPos&) {}

bool AbstractTreeFeature::isFree(Block* block) {
    Material* material = block->defaultBlockState()->getMaterial();
    return material == Material::AIR || material == Material::LEAVES || block == Blocks::GRASS
           || block == Blocks::DIRT || block == Blocks::LOG || block == Blocks::LOG2
           || block == Blocks::SAPLING || block == Blocks::VINE;
}

void AbstractTreeFeature::setDirtAt(Level* level, const BlockPos& pos) {
    if (level->getBlockState(pos)->getBlock() != Blocks::DIRT)
        Feature::setBlock(level, pos, Blocks::DIRT->defaultBlockState());
}

void AbstractTreeFeature::addVine(Level* level, const BlockPos& pos, const BooleanProperty* property) {
    setBlock(level, pos,
             Blocks::VINE->defaultBlockState()->setValue<bool>(const_cast<BooleanProperty*>(property), true));
}

// A fallen-tree attempt still leaves the one-block stump when its horizontal trunk is rejected.
bool AbstractTreeFeature::placeTrunk(Level* level, const BlockPos& pos, Random& random, int height) {
    int fallen = random.nextInt(80);
    auto variant = m_trunk->getValue<PlanksBlock::Variant*>(OldLogBlock::VARIANT);
    float vineChance = variant == PlanksBlock::Variant::BIRCH ? 0.0f : 0.75f;
    if (fallen != 0 && variant != PlanksBlock::Variant::BIRCH) {
        if (!m_vines)
            vineChance = random.nextInt(12) == 0 ? 1.0f : 0.0f;
        else
            vineChance = 1.0f / 3.0f;
    }
    if (fallen == 0) {
        placeFallenTrunk(level, pos, random, height);
        height = 1;
    }
    for (int y = 0; y < height; ++y) {
        Material* material = level->getBlockState(pos.above(y))->getMaterial();
        if (material != Material::AIR && material != Material::LEAVES && material != Material::MOSS
            && material != Material::DIRT && material != Material::GRASS)
            continue;
        setBlock(level, pos.above(y), m_trunk);
        if (vineChance != 0.0f) {
            if (random.nextFloat() < vineChance && level->isEmptyBlock(pos.offset(-1, y, 0)))
                addVine(level, pos.offset(-1, y, 0), VineBlock::EAST);
            if (random.nextFloat() < vineChance && level->isEmptyBlock(pos.offset(1, y, 0)))
                addVine(level, pos.offset(1, y, 0), VineBlock::WEST);
            if (random.nextFloat() < vineChance && level->isEmptyBlock(pos.offset(0, y, -1)))
                addVine(level, pos.offset(0, y, -1), VineBlock::SOUTH);
            if (random.nextFloat() < vineChance && level->isEmptyBlock(pos.offset(0, y, 1)))
                addVine(level, pos.offset(0, y, 1), VineBlock::NORTH);
        }
    }
    return fallen != 0;
}

void AbstractTreeFeature::placeFallenTrunk(Level* level, const BlockPos& pos, Random& random, int height) {
    MutableBlockPos start(pos.getX(), pos.getY(), pos.getZ());
    const Direction* direction = Direction::Plane::HORIZONTAL->getRandomDirection(random);
    start.move(direction, random.nextInt(2) + 2);
    MutableBlockPos base = start;
    base.set(base.getX(), level->getHeightmap(base.getX(), base.getZ()), base.getZ());
    if (base.getY() > pos.getY() + 1)
        return;
    MutableBlockPos current = base;
    int unsupported = 0;
    for (int i = 0; i < height - 2; ++i) {
        current.move(direction, 1);
        if (level->getBlockState(current)->getMaterial() != Material::AIR)
            return;
        if (level->isSolidBlockingBlockInLoadedChunk(current.below(), false))
            unsupported = 0;
        else if (++unsupported > 2)
            return;
    }
    current = base;
    for (int i = 0; i < height - 2; ++i) {
        current.move(direction, 1);
        auto axis = direction->getAxis()->getId() == 0 ? LogBlock::LogAxis::X : LogBlock::LogAxis::Z;
        setBlock(level, current, m_trunk->setValue<LogBlock::LogAxis*>(LogBlock::LOG_AXIS, axis));
        if (random.nextInt(10) == 0
            && level->getBlockState(current.above())->getMaterial() == Material::AIR) {
            setBlock(level, current.above(),
                     (random.nextFloat() < 0.5f ? Blocks::BROWN_MUSHROOM : Blocks::RED_MUSHROOM)
                         ->defaultBlockState());
        }
    }
}
