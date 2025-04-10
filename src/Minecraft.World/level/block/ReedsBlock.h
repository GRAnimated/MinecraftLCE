#pragma once

#include "Minecraft.World/level/block/Block.h"
#include "Minecraft.World/level/block/BonemealableBlock.h"
#include "Minecraft.World/level/block/state/IntegerProperty.h"

class ReedsBlock : public Block, public BonemealableBlock {
public:
    static IntegerProperty* sAgeProperty;
    static AABB* sAABB;

    ReedsBlock();

    void GetInteractTooltip(const BlockTooltipDataHolder& blockTooltipDataHolder) override;
    const BlockState* getBlockState(int) override;
    int convertBlockStateToLegacyData(const BlockState* blockState) override;
    ~ReedsBlock() override;
    bool isCubeShaped(const BlockState* blockState) override;
    void getRenderShape(const BlockState* blockState) override;
    AABB* getShape(const BlockState* blockState, LevelSource* levelSource, const BlockPos& pos) override;
    void getBlockFaceShape(LevelSource* levelSource, const BlockState* blockState, const BlockPos& pos, const Direction* direction) override;
    AABB* getClipAABB(const BlockState* blockState, LevelSource* levelSource, const BlockPos& pos) override;
    bool isSolidRender(const BlockState* blockState) override;
    void tick(Level* level, const BlockPos& pos, const BlockState* blockState, Random*) override;
    void neighborChanged(const BlockState* blockState, Level* level, const BlockPos& pos, Block*, const BlockPos& pos2) override;
    void getResource(const BlockState* blockState, Random*, int) override;
    void getRenderLayer() override;
    bool mayPlace(Level* level, const BlockPos& pos) override;
    void getColor(LevelSource* levelSource, const BlockPos& pos, int) override;
    void shouldBlockTick(Level* level, const BlockPos& pos, const BlockState* blockState) override;
    void getCloneItemInstance(Level* level, const BlockPos& pos, const BlockState* blockState) override;
    BlockStateDefinition* createBlockStateDefinition() override;
    bool isValidBonemealTarget(Level*, BlockPos const&, BlockState const*, bool) override;
    bool isBonemealSuccess(Level*, Random*, BlockPos const&, BlockState const*) override;
    void performBonemeal(Level*, Random*, BlockPos const&, BlockState const*) override;

    bool canSurvive(Level*, BlockPos const&);
    bool checkAlive(Level*, BlockPos const&, BlockState const*);
};
