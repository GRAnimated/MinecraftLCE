#include "net/minecraft/world/level/block/WaterlilyBlock.h"

#include "net/minecraft/client/Minecraft.h"
#include "net/minecraft/client/color/ColourTable.h"
#include "net/minecraft/world/entity/Entity.h"
#include "net/minecraft/world/level/Level.h"
#include "net/minecraft/world/level/block/Blocks.h"
#include "net/minecraft/world/level/block/state/properties/BlockStateProperties.h"
#include "net/minecraft/world/level/material/Material.h"
#include "net/minecraft/world/level/material/MaterialColor.h"
#include "net/minecraft/world/phys/AABB.h"

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
                                  const std::shared_ptr<Entity>& entity) {
    Block::entityInside(level, pos, blockState, entity);
    if (entity->isType(eBoat)) {
        level->destroyBlock(pos, true);
    }
}

bool WaterlilyBlock::mayPlaceOn(const BlockState* blockState) {
    return blockState->getBlock() == Blocks::WATER || blockState->getMaterial() == Material::ICE;
}

bool WaterlilyBlock::canSurvive(Level* level, const BlockPos& pos, const BlockState* blockState) {
    if (pos.getY() < 0 || pos.getY() > 255)
        return false;

    const BlockState* belowState = level->getBlockState(pos.below());
    Material* material = belowState->getMaterial();

    return (material == Material::WATER && !belowState->getValue<int>(BlockStateProperties::WATER_LEVEL))
           || material == Material::ICE;
}
