#pragma once

#include "Minecraft.World/level/block/Block.h"

class BarrierBlock : public Block {
public:
    BarrierBlock();

    RenderShape getRenderShape(const BlockState* blockState) override;
    bool isSolidRender(const BlockState* blockState) const override;
    void spawnResources(Level* level, const BlockPos& pos, const BlockState* blockState, float, int) override;
    float getShadeBrightness(const BlockState* blockState) override;
};
