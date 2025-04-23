#pragma once

#include "Minecraft.World/level/block/Block.h"

class AirBlock : public Block {
public:
    AirBlock();

    bool isCubeShaped(const BlockState* blockState) override;
    int getRenderShape(const BlockState* blockState) override;
    bool mayReplaceWithPlace(LevelSource* levelSource, const BlockPos& pos) override;
    int getBlockFaceShape(LevelSource* levelSource, const BlockState* blockState, const BlockPos& pos,
                          const Direction* direction) override;
    AABB* getClipAABB(const BlockState* blockState, LevelSource* levelSource, const BlockPos& pos) override;
    bool isSolidRender(const BlockState* blockState) const override;
    bool mayPick(const BlockState* blockState, bool) override;
    void spawnResources(Level* level, const BlockPos& pos, const BlockState* blockState, float, int) override;
};
