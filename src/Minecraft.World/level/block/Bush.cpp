#include "Minecraft.World/level/block/Bush.h"

#include "Minecraft.World/level/Level.h"
#include "Minecraft.World/level/block/Blocks.h"
#include "Minecraft.World/level/block/RenderShape.h"
#include "Minecraft.World/level/block/state/BlockState.h"
#include "Minecraft.World/level/material/Material.h"
#include "Minecraft.World/phys/AABB.h"
#include "Minecraft.Core/BlockPos.h"

static float boundingSize = 0.2f;

AABB* bushAABB = AABB::newPermanent(0.5 - boundingSize, 0.0f, 0.5 - boundingSize, boundingSize + 0.5,
                                    boundingSize * 3.0, boundingSize + 0.5);

Bush::Bush() : Block(Material::PLANTS) {
    _init();
}

Bush::Bush(Material* material) : Block(material) {
    _init();
}

void Bush::_init() {
    setTicking(true);
}

bool Bush::isCubeShaped(const BlockState* blockState) {
    return false;
}

RenderShape Bush::getRenderShape(const BlockState* blockState) {
    return RenderShape_CROSS;
}

AABB* Bush::getShape(const BlockState* blockState, LevelSource* levelSource, const BlockPos& pos) {
    return bushAABB;
}

int Bush::getBlockFaceShape(LevelSource* levelSource, const BlockState* blockState, const BlockPos& pos,
                            const Direction* direction) {
    return 8;
}

AABB* Bush::getClipAABB(const BlockState* blockState, LevelSource* levelSource, const BlockPos& pos) {
    return nullptr;
}

bool Bush::isSolidRender(const BlockState* blockState) const {
    return false;
}

void Bush::tick(Level* level, const BlockPos& pos, const BlockState* blockState, Random*) {
    checkAlive(level, pos, blockState);
}

void Bush::neighborChanged(const BlockState* blockState, Level* level, const BlockPos& pos, Block*,
                           const BlockPos& pos2) {
    checkAlive(level, pos, blockState);
}

int Bush::getRenderLayer() {
    return 0;
}

bool Bush::mayPlace(Level* level, const BlockPos& pos) {
    if (Block::mayPlace(level, pos)) {
        return mayPlaceOn(level->getBlockState(pos.below()));
    }
    return false;
}

bool Bush::mayPlaceOn(BlockState const* blockState) {
    return blockState->getBlock() == Blocks::GRASS || blockState->getBlock() == Blocks::DIRT
           || blockState->getBlock() == Blocks::FARMLAND;
}

void Bush::checkAlive(Level* level, BlockPos const& pos, BlockState const* blockState) {
    bool canBlockSurvive = canSurvive(level, pos, blockState);
    if (canBlockSurvive)
        return;

    spawnResources(level, pos, blockState, 0);

    level->setBlock(pos, Blocks::AIR->defaultBlockState(), 3, false);
}

bool Bush::canSurvive(Level* level, BlockPos const& pos, BlockState const* blockState) {
    return mayPlaceOn(level->getBlockState(pos.below()));
}
