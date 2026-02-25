#pragma once

#include "net/minecraft/client/renderer/texture/TextureAtlasSprite.h"
#include "net/minecraft/core/Direction.h"
#include "net/minecraft/world/level/block/Block.h"
#include "net/minecraft/world/level/block/BlockShapes.h"
#include "net/minecraft/world/level/block/state/EnumProperty.h"
#include "types.h"

class RotatedPillarBlock : public Block {
public:
    static void blockStaticCtor();

    RotatedPillarBlock(Material*);
    RotatedPillarBlock(Material*, const MaterialColor*);

    const BlockState* getBlockState(int) override;
    int convertBlockStateToLegacyData(const BlockState*) override;
    const BlockState* rotate(const BlockState*, Rotation*) override;
    RenderShape getRenderShape(const BlockState*) override;
    const BlockState* getStateForPlacement(Level*, const BlockPos&, const Direction*, float, float, float,
                                           int, std::shared_ptr<LivingEntity>) override;
    not_null_ptr<ItemInstance> getSilkTouchItemInstance(const BlockState*) override;
    TextureAtlasSprite* getTexture(const Direction*, const BlockState*) override;
    BlockStateDefinition* createBlockStateDefinition() override;
    virtual TextureAtlasSprite* getTypeTexture(const BlockState*);
    virtual TextureAtlasSprite* getTopTexture(const BlockState*);
    virtual Direction::Axis* getAxis(const BlockState*) = 0;

    static inline EnumProperty<Direction::Axis*>* AXIS;

    TextureAtlasSprite* m_topTexture;
};
