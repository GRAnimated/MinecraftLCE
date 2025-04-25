#include "Minecraft.World/level/block/ReedsBlock.h"

#include "Minecraft.World/item/ItemInstance.h"
#include "Minecraft.World/item/Items.h"
#include "Minecraft.World/level/Level.h"
#include "Minecraft.World/level/block/Blocks.h"
#include "Minecraft.World/level/block/BonemealableBlock.h"
#include "Minecraft.World/level/block/RenderShape.h"
#include "Minecraft.World/level/block/state/BlockStateDefinition.h"
#include "Minecraft.World/level/block/state/IntegerProperty.h"
#include "Minecraft.World/level/material/Material.h"
#include "Minecraft.World/phys/AABB.h"
#include "Minecraft.Core/BlockPos.h"

static std::atomic_bool hasCreatedDefinition;
std::vector<Property const*> sAgeProperties;
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

bool ReedsBlock::canSurvive(Level* level, BlockPos const& pos) {
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

// NON_MATCHING: Different shared_ptr constructor?
std::shared_ptr<ItemInstance> ReedsBlock::getCloneItemInstance(Level* level, const BlockPos& pos,
                                                               const BlockState* blockState) {
    return std::shared_ptr<ItemInstance>(new ItemInstance(Items::REEDS));
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

    return new BlockStateDefinition(this, sAgeProperties.data());
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
