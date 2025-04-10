#include "Minecraft.World/level/block/ReedsBlock.h"

#include "Minecraft.World/level/Level.h"
#include "Minecraft.World/level/block/Blocks.h"
#include "Minecraft.World/level/block/BonemealableBlock.h"
#include "Minecraft.World/level/block/state/BlockStateDefinition.h"
#include "Minecraft.World/level/block/state/IntegerProperty.h"
#include "Minecraft.World/level/material/DecorationMaterial.h"
#include "Minecraft.World/phys/AABB.h"
#include "Minecraft.Core/BlockPos.h"

IntegerProperty* ReedsBlock::sAgeProperty = IntegerProperty::create(L"age", 0, 15);

const f32 size = 6.0f / 16.0f;  // 0.375f

AABB* ReedsBlock::sAABB = AABB::newPermanent(0.5f - size, 0.0f, 0.5f - size, size + 0.5f, 1.0f, size + 0.5f);

ReedsBlock::ReedsBlock() : Block(Material::PLANTS) {
    Block::DerivedInit();
    const BlockState* propertyState = mBlockStateDefinition->any()->setPropertyState(sAgeProperty, 0);
    registerDefaultState(propertyState);
    setTicking(true);
}

AABB* ReedsBlock::getShape(const BlockState* blockState, LevelSource* levelSource, const BlockPos& pos) {
    return sAABB;
}

void ReedsBlock::tick(Level* level, const BlockPos& pos, const BlockState* blockState, Random*) {
    if (level->getBlockState(pos.below())->getBlock() != Blocks::REEDS) {
        if (!checkAlive(level, pos, blockState))
            return;
    }

    if (!level->isEmptyBlock(pos.above()))
        return;

    int height = 1;
    while (level->getBlockState(pos.below(height))->getBlock() == this) {
        height++;
    }

    if (height < 3) {
        int age = blockState->getPropertyValue(sAgeProperty);
        if (age == 15) {
            level->setBlockAndUpdate(pos.above(), defaultBlockState());
            level->setBlock(pos, blockState->setPropertyState(sAgeProperty, 0), 4, false);
        } else {
            level->setBlock(pos, blockState->setPropertyState(sAgeProperty, age + 1), 4, false);
        }
    }
}

bool ReedsBlock::checkAlive(Level* level, const BlockPos& pos, const BlockState* blockState) {
    if (!canSurvive(level, pos)) {
        spawnResources(level, pos, blockState, 0);
        level->removeBlock(pos);
        return false;
    }

    return true;
}

// ReedsBlock::mayPlace

void ReedsBlock::neighborChanged(const BlockState* blockState, Level* level, const BlockPos& pos, Block*,
                                 const BlockPos& pos2) {
    checkAlive(level, pos, blockState);
}

bool ReedsBlock::canSurvive(Level* level, BlockPos const& pos) {
    return mayPlace(level, pos);
}

AABB* ReedsBlock::getClipAABB(const BlockState* blockState, LevelSource* levelSource, const BlockPos& pos) {
    return sAABB;
}
