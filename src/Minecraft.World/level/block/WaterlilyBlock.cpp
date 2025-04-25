#include "Minecraft.World/level/block/WaterlilyBlock.h"

#include "Minecraft.Client/Minecraft.h"
#include "Minecraft.Client/color/ColourTable.h"
#include "Minecraft.World/entity/Entity.h"
#include "Minecraft.World/level/Level.h"
#include "Minecraft.World/level/block/Blocks.h"
#include "Minecraft.World/level/block/state/properties/BlockStateProperties.h"
#include "Minecraft.World/level/material/Material.h"
#include "Minecraft.World/level/material/MaterialColor.h"
#include "Minecraft.World/phys/AABB.h"

AABB* waterlilyAABB = AABB::newPermanent(0.0625, 0.0f, 0.0625, 0.9375, 0.09375, 0.9375);

WaterlilyBlock::WaterlilyBlock() : Bush() {
    DerivedInit();
}

int WaterlilyBlock::convertBlockStateToLegacyData(const BlockState* blockState) {
    return 0;
}

RenderShape WaterlilyBlock::getRenderShape(const BlockState* blockState) {
    return RenderShape_WATERLILY;
}

AABB* WaterlilyBlock::getShape(const BlockState* blockState, LevelSource* levelSource, const BlockPos& pos) {
    return waterlilyAABB;
}

void WaterlilyBlock::addCollisionAABBs(const BlockState* blockState, Level* level, const BlockPos& pos,
                                       AABB const* aabb, std::vector<AABB*>* aabbs,
                                       std::shared_ptr<Entity> entity, bool) {
    if (entity && !entity->isType(eBoat))
        Block::addCollisionAABB(pos, aabb, aabbs, waterlilyAABB);
}

int WaterlilyBlock::getColor() const {
    return Minecraft::GetInstance()->getColourTable()->getColour(Tile_WaterLily);
}

int WaterlilyBlock::getColor(const BlockState* blockState) {
    return Minecraft::GetInstance()->getColourTable()->getColour(Tile_WaterLily);
}

int WaterlilyBlock::getColor(LevelSource* levelSource, const BlockPos& pos) {
    return Minecraft::GetInstance()->getColourTable()->getColour(Tile_WaterLily);
}

int WaterlilyBlock::getColor(LevelSource* levelSource, const BlockPos& pos, const BlockState* blockState) {
    return getColor(levelSource, pos);
}

void WaterlilyBlock::entityInside(Level* level, const BlockPos& pos, const BlockState* blockState,
                                  std::shared_ptr<Entity> const& entity) {
    Block::entityInside(level, pos, blockState, entity);
    if (entity->isType(eBoat)) {
        level->destroyBlock(pos, true);
    }
}

bool WaterlilyBlock::mayPlaceOn(BlockState const* blockState) {
    return blockState->getBlock() == Blocks::WATER || blockState->getMaterial() == Material::ICE;
}

bool WaterlilyBlock::canSurvive(Level* level, BlockPos const& pos, BlockState const* blockState) {
    if (pos.getY() < 0 || pos.getY() > 255)
        return false;

    const BlockState* belowState = level->getBlockState(pos.below());
    Material* material = belowState->getMaterial();

    return (material == Material::WATER && !belowState->getValue<int>(BlockStateProperties::WATER_LEVEL))
           || material == Material::ICE;
}
