#pragma once

#include "Minecraft.World/level/block/Block.h"

class HalfTransparentBlock : public Block {
public:
    HalfTransparentBlock();

    ~HalfTransparentBlock() override;
    void shouldRenderFace(const BlockState* blockState, LevelSource* levelSource, const BlockPos& pos,
                          const Direction* direction) override;
    bool isSolidRender(const BlockState* blockState) const override;
    void registerIcons(IconRegister*) override;
};
