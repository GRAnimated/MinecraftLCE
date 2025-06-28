#pragma once

#include "Minecraft.World/level/block/Block.h"
#include "Minecraft.World/level/block/BonemealableBlock.h"
#include "Minecraft.World/level/block/state/IntegerProperty.h"
#include <memory>

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
    RenderShape getRenderShape(const BlockState* blockState) override;
    AABB* getShape(const BlockState* blockState, LevelSource* levelSource, const BlockPos& pos) override;
    int getBlockFaceShape(LevelSource* levelSource, const BlockState* blockState, const BlockPos& pos,
                          const Direction* direction) override;
    AABB* getClipAABB(const BlockState* blockState, LevelSource* levelSource, const BlockPos& pos) override;
    bool isSolidRender(const BlockState* blockState) const override;
    void tick(Level* level, const BlockPos& pos, const BlockState* blockState, Random*) override;
    void neighborChanged(const BlockState* blockState, Level* level, const BlockPos& pos, Block*,
                         const BlockPos& pos2) override;
    Item* getResource(const BlockState* blockState, Random*, int) override;
    int getRenderLayer() override;
    bool mayPlace(Level* level, const BlockPos& pos) override;
    int getColor(LevelSource* levelSource, const BlockPos& pos, int) override;
    bool shouldBlockTick(Level* level, const BlockPos& pos, const BlockState* blockState) override;
    not_null_ptr<ItemInstance> getCloneItemInstance(Level* level, const BlockPos& pos,
                                                    const BlockState* blockState) override;
    BlockStateDefinition* createBlockStateDefinition() override;
    bool isValidBonemealTarget(Level*, const BlockPos&, const BlockState*, bool) override;
    bool isBonemealSuccess(Level*, Random*, const BlockPos&, const BlockState*) override;
    void performBonemeal(Level*, Random*, const BlockPos&, const BlockState*) override;

    bool canSurvive(Level*, const BlockPos&);
    bool checkAlive(Level*, const BlockPos&, const BlockState*);
};
