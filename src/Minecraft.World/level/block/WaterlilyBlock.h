#pragma once

#include "Minecraft.World/level/block/Bush.h"

class WaterlilyBlock : public Bush {
public:
    WaterlilyBlock();

    int convertBlockStateToLegacyData(const BlockState* blockState) override;
    RenderShape getRenderShape(const BlockState* blockState) override;
    AABB* getShape(const BlockState* blockState, LevelSource* levelSource, const BlockPos& pos) override;
    void addCollisionAABBs(const BlockState* blockState, Level* level, const BlockPos& pos, AABB const*,
                           std::vector<AABB*>*, std::shared_ptr<Entity>, bool) override;
    int getColor() const override;
    int getColor(const BlockState* blockState) override;
    int getColor(LevelSource* levelSource, const BlockPos& pos) override;
    int getColor(LevelSource* levelSource, const BlockPos& pos, const BlockState* blockState) override;
    void entityInside(Level* level, const BlockPos& pos, const BlockState* blockState,
                      const std::shared_ptr<Entity>&) override;
    bool mayPlaceOn(const BlockState* blockState) override;
    bool canSurvive(Level* level, const BlockPos& pos, const BlockState* blockState) override;
};
