#pragma once

#include "Minecraft.World/level/block/Block.h"

class WebBlock : public Block {
public:
    WebBlock();

    bool isCubeShaped(const BlockState* blockState) override;
    RenderShape getRenderShape(const BlockState* blockState) override;
    int getBlockFaceShape(LevelSource* levelSource, const BlockState* blockState, const BlockPos& pos,
                          const Direction* direction) override;
    AABB* getClipAABB(const BlockState* blockState, LevelSource* levelSource, const BlockPos& pos) override;
    bool isSolidRender(const BlockState* blockState) const override;
    Item* getResource(const BlockState* blockState, Random*, int) override;
    int getRenderLayer() override;
    void entityInside(Level* level, const BlockPos& pos, const BlockState* blockState,
                      std::shared_ptr<Entity> const&) override;
    void playerDestroy(Level* level, std::shared_ptr<Player> player, const BlockPos& pos,
                       const BlockState* blockState, std::shared_ptr<BlockEntity>,
                       not_null_ptr<ItemInstance>) override;
    bool isSilkTouchable() override;
};
