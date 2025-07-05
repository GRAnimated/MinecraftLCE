#include "net/minecraft/world/level/block/AirBlock.h"

#include "net/minecraft/world/level/block/Block.h"
#include "net/minecraft/world/level/block/RenderShape.h"
#include "net/minecraft/world/level/material/Material.h"

AirBlock::AirBlock() : Block(Material::AIR) {
    DerivedInit();
}

bool AirBlock::isCubeShaped(const BlockState* blockState) {
    return false;
}

RenderShape AirBlock::getRenderShape(const BlockState* blockState) {
    return RenderShape_INVISIBLE;
}

bool AirBlock::mayReplaceWithPlace(LevelSource* levelSource, const BlockPos& pos) {
    return true;
}

int AirBlock::getBlockFaceShape(LevelSource* levelSource, const BlockState* blockState, const BlockPos& pos,
                                const Direction* direction) {
    return 8;
}

AABB* AirBlock::getClipAABB(const BlockState* blockState, LevelSource* levelSource, const BlockPos& pos) {
    return nullptr;
}

bool AirBlock::isSolidRender(const BlockState* blockState) const {
    return false;
}

bool AirBlock::mayPick(const BlockState* blockState, bool) {
    return false;
}

void AirBlock::spawnResources(Level* level, const BlockPos& pos, const BlockState* blockState, float, int) {}
