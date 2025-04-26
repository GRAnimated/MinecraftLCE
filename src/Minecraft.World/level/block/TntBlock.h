#pragma once

#include "Minecraft.World/level/block/Block.h"
#include "Minecraft.World/level/block/state/BooleanProperty.h"

class TntBlock : public Block {
public:
    static BooleanProperty* EXPLODE;

    TntBlock();

    const BlockState* getBlockState(int) override;
    int convertBlockStateToLegacyData(const BlockState* blockState) override;
    void destroy(Level* level, const BlockPos& pos, const BlockState* blockState) override;
    void neighborChanged(const BlockState* blockState, Level* level, const BlockPos& pos, Block*,
                         const BlockPos& pos2) override;
    void onPlace(Level* level, const BlockPos& pos, const BlockState* blockState) override;
    void wasExploded(Level* level, const BlockPos& pos, Explosion*) override;
    void use(Level* level, const BlockPos& pos, const BlockState* blockState, std::shared_ptr<Player> player,
             InteractionHand::EInteractionHand, const Direction* direction, float, float, float,
             bool) override;
    void entityInside(Level* level, const BlockPos& pos, const BlockState* blockState,
                      std::shared_ptr<Entity> const&) override;
    void setPlacedBy(Level* level, const BlockPos& pos, const BlockState* blockState,
                     std::shared_ptr<LivingEntity>, not_null_ptr<ItemInstance>) override;
    void dropFromExplosion(Explosion*) override;
    Texture* getTexture(const Direction* direction, const BlockState* blockState) override;
    BlockStateDefinition* createBlockStateDefinition() override;
    virtual void destroy(Level*, BlockPos const&, BlockState const*, std::shared_ptr<LivingEntity>);
};
