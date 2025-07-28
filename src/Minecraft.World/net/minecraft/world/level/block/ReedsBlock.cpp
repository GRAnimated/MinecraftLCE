#include "net/minecraft/world/level/block/ReedsBlock.h"

#include "net/minecraft/core/BlockPos.h"
#include "net/minecraft/world/item/ItemInstance.h"
#include "net/minecraft/world/item/Items.h"
#include "net/minecraft/world/level/Level.h"
#include "net/minecraft/world/level/block/BlockShapes.h"
#include "net/minecraft/world/level/block/Blocks.h"
#include "net/minecraft/world/level/block/BonemealableBlock.h"
#include "net/minecraft/world/level/block/state/BlockStateDefinition.h"
#include "net/minecraft/world/level/block/state/IntegerProperty.h"
#include "net/minecraft/world/level/material/Material.h"
#include "net/minecraft/world/phys/AABB.h"

static std::atomic_bool hasCreatedDefinition;
std::vector<const Property*> sAgeProperties;
IntegerProperty* ReedsBlock::sAgeProperty = IntegerProperty::create(L"age", 0, 15);

const f32 size = 6.0f / 16.0f;  // 0.375f

AABB* ReedsBlock::sAABB = AABB::newPermanent(0.5f - size, 0.0f, 0.5f - size, size + 0.5f, 1.0f, size + 0.5f);

ReedsBlock::ReedsBlock() : Block(Material::PLANTS) {
    Block::DerivedInit();
    const BlockState* propertyState = mBlockStateDefinition->any()->setValue(sAgeProperty, 0);
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
        int age = blockState->getValue<int>(sAgeProperty);
        if (age == 15) {
            level->setBlockAndUpdate(pos.above(), defaultBlockState());
            level->setBlock(pos, blockState->setValue(sAgeProperty, 0), 4, false);
        } else {
            level->setBlock(pos, blockState->setValue(sAgeProperty, age + 1), 4, false);
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

bool ReedsBlock::canSurvive(Level* level, const BlockPos& pos) {
    return mayPlace(level, pos);
}

AABB* ReedsBlock::getClipAABB(const BlockState* blockState, LevelSource* levelSource, const BlockPos& pos) {
    return sAABB;
}

Item* ReedsBlock::getResource(const BlockState* blockState, Random*, int) {
    return Items::REEDS;
}

bool ReedsBlock::isSolidRender(const BlockState* blockState) const {
    return false;
}

bool ReedsBlock::isCubeShaped(const BlockState* blockState) {
    return false;
}

not_null_ptr<ItemInstance> ReedsBlock::getCloneItemInstance(Level* level, const BlockPos& pos,
                                                            const BlockState* blockState) {
    return new ItemInstance(Items::REEDS);
}

int ReedsBlock::getColor(LevelSource* levelSource, const BlockPos& pos, int) {
    return 0xFFFFFF;
}

int ReedsBlock::getRenderLayer() {
    return 0;
}

const BlockState* ReedsBlock::getBlockState(int age) {
    return defaultBlockState()->setValue(sAgeProperty, age);
}

int ReedsBlock::convertBlockStateToLegacyData(const BlockState* blockState) {
    return blockState->getValue<int>(sAgeProperty);
}

// NON_MATCHING: Original does some weird atomic stuff, i think hasCreatedDefinition is fake
BlockStateDefinition* ReedsBlock::createBlockStateDefinition() {
    if (hasCreatedDefinition == false) {
        hasCreatedDefinition = true;
        sAgeProperties[0] = sAgeProperty;
    }
    // removed as this needs to be reworked :skull:
    // return new BlockStateDefinition(this, sAgeProperties.data());
}

int ReedsBlock::getBlockFaceShape(LevelSource* levelSource, const BlockState* blockState, const BlockPos& pos,
                                  const Direction* direction) {
    return 8;
}

bool ReedsBlock::shouldBlockTick(Level* level, const BlockPos& pos, const BlockState* blockState) {
    return level->isEmptyBlock(pos.above());
}

RenderShape ReedsBlock::getRenderShape(const BlockState* blockState) {
    return RenderShape_CROSS;
}

// ReedsBlock::GetInteractTooltip
