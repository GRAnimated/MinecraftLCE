#include "net/minecraft/world/level/levelgen/structure/StructurePiece.h"

#include "net/minecraft/core/BlockPos.h"
#include "net/minecraft/world/level/Level.h"
#include "net/minecraft/world/level/block/Block.h"
#include "net/minecraft/world/level/block/Blocks.h"
#include "net/minecraft/world/level/block/Mirror.h"
#include "net/minecraft/world/level/block/Rotation.h"
#include "net/minecraft/world/level/block/state/BlockState.h"
#include "net/minecraft/world/level/levelgen/structure/BoundingBox.h"

void StructurePiece::placeBlock(Level* level, const BlockState* state, int x, int y, int z,
                                BoundingBox* bounds) {
    BlockPos pos(getWorldX(x, z), getWorldY(y), getWorldZ(x, z));
    if (bounds->isInside(pos) && pos.getY() != 0) {
        if (m_mirror != Mirror::NONE)
            state = state->getBlock()->mirror(state, m_mirror);
        if (m_rotation != Rotation::NONE)
            state = state->getBlock()->rotate(state, m_rotation);
        level->setBlock(pos, state, 18, false);
    }
}

const BlockState* StructurePiece::getBlock(Level* level, int x, int y, int z, BoundingBox* bounds) {
    BlockPos pos(getWorldX(x, z), getWorldY(y), getWorldZ(x, z));
    return bounds->isInside(pos) ? level->getBlockState(pos) : Blocks::AIR->defaultBlockState();
}

int StructurePiece::getSkyBrightness(Level* level, int x, int y, int z, BoundingBox* bounds) {
    BlockPos pos(getWorldX(x, z), getWorldY(y + 1), getWorldZ(x, z));
    return bounds->isInside(pos) ? level->getBrightness(LightLayer::SKY, pos) : 15;
}
