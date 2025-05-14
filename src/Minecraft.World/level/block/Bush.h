#pragma once

#include "Minecraft.World/level/block/Block.h"

class Bush : public Block {
public:
    Bush();
    Bush(Material*);
    void _init();

    bool isCubeShaped(const BlockState* blockState) override;
    RenderShape getRenderShape(const BlockState* blockState) override;
    AABB* getShape(const BlockState* blockState, LevelSource* levelSource, const BlockPos& pos) override;
    int getBlockFaceShape(LevelSource* levelSource, const BlockState* blockState, const BlockPos& pos,
                          const Direction* direction) override;
    AABB* getClipAABB(const BlockState* blockState, LevelSource* levelSource, const BlockPos& pos) override;
    bool isSolidRender(const BlockState* blockState) const override;
    void tick(Level* level, const BlockPos& pos, const BlockState* blockState, Random*) override;
    void neighborChanged(const BlockState* blockState, Level* level, const BlockPos& pos, Block*,
                         const BlockPos& pos2) override;
    int getRenderLayer() override;
    bool mayPlace(Level* level, const BlockPos& pos) override;

    virtual bool mayPlaceOn(BlockState const* blockState);
    virtual void checkAlive(Level* level, const BlockPos& pos, BlockState const* blockState);
    virtual bool canSurvive(Level* level, const BlockPos& pos, BlockState const* blockState);
};
