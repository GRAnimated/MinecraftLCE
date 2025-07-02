#pragma once

#include "net/minecraft/world/level/block/HalfTransparentBlock.h"

class GlassBlock : public HalfTransparentBlock {
public:
    GlassBlock(Material* material, bool unk);

    bool isCubeShaped(const BlockState* blockState) override;
    int getResourceCount(Random*) override;
    int getRenderLayer() override;
    bool isSilkTouchable() override;
};
