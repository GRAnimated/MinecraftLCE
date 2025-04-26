#pragma once

#include "Minecraft.World/level/block/HalfTransparentBlock.h"

class PortalBlock : public HalfTransparentBlock {
public:
    PortalBlock();

    const BlockState* getBlockState(int) override;
    int convertBlockStateToLegacyData(const BlockState* blockState) override;
    void rotate(const BlockState* blockState, Rotation*) override;
    ~PortalBlock() override;
    bool isCubeShaped(const BlockState* blockState) override;
    AABB* getShape(const BlockState* blockState, LevelSource* levelSource, const BlockPos& pos) override;
    bool shouldRenderFace(const BlockState* blockState, LevelSource* levelSource, const BlockPos& pos,
                          const Direction* direction) override;
    int getBlockFaceShape(LevelSource* levelSource, const BlockState* blockState, const BlockPos& pos,
                          const Direction* direction) override;
    AABB* getClipAABB(const BlockState* blockState, LevelSource* levelSource, const BlockPos& pos) override;
    bool mayPick() override;
    void tick(Level* level, const BlockPos& pos, const BlockState* blockState, Random*) override;
    void animateTick(const BlockState* blockState, Level* level, const BlockPos& pos, Random*) override;
    void neighborChanged(const BlockState* blockState, Level* level, const BlockPos& pos, Block*,
                         const BlockPos& pos2) override;
    int getResourceCount(Random*) override;
    int getRenderLayer() override;
    void entityInside(Level* level, const BlockPos& pos, const BlockState* blockState,
                      std::shared_ptr<Entity> const&) override;
    std::shared_ptr<ItemInstance> getCloneItemInstance(Level* level, const BlockPos& pos,
                                                       const BlockState* blockState) override;
    BlockStateDefinition* createBlockStateDefinition() override;
    virtual bool trySpawnPortal(Level*, BlockPos const&, bool);
};
