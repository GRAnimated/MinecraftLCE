#include "net/minecraft/world/level/block/BarrierBlock.h"
#include "net/minecraft/world/level/block/Block.h"
#include "net/minecraft/world/level/block/BlockShapes.h"
#include "net/minecraft/world/level/material/Material.h"

BarrierBlock::BarrierBlock() : Block(Material::BARRIER) {
    DerivedInit();
    setIndestructible();
    setExplodeable(6000000.0f);
    setNotCollectStatistics();
    m_isBlocksLight = true;
}

RenderShape BarrierBlock::getRenderShape(const BlockState* blockState) {
    return RenderShape_INVISIBLE;
}

bool BarrierBlock::isSolidRender(const BlockState* blockState) const {
    return false;
}

void BarrierBlock::spawnResources(Level* level, const BlockPos& pos, const BlockState* blockState, float,
                                  int) {}

float BarrierBlock::getShadeBrightness(const BlockState* blockState) {
    return 1.0f;
}
