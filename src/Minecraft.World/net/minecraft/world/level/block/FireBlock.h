#pragma once

#include "net/minecraft/client/renderer/texture/TextureAtlasSprite.h"
#include "net/minecraft/world/level/block/Block.h"
#include <unordered_map>

class IntegerProperty;
class BooleanProperty;

class FireBlock : public Block {
public:
    FireBlock();

    static IntegerProperty* AGE;
    static BooleanProperty* NORTH;
    static BooleanProperty* EAST;
    static BooleanProperty* SOUTH;
    static BooleanProperty* WEST;
    static BooleanProperty* UP;

    static void staticCtor();

    MaterialColor* getMapColor(const BlockState* blockState, LevelSource* levelSource,
                               const BlockPos& pos) override;
    const BlockState* getBlockState(int) override;
    int convertBlockStateToLegacyData(const BlockState* blockState) override;
    const BlockState* fillVirtualBlockStateProperties(const BlockState* blockState, LevelSource* levelSource,
                                                      const BlockPos& pos) override;
    ~FireBlock();
    bool isCubeShaped(const BlockState* blockState) override;
    RenderShape getRenderShape(const BlockState* blockState) override;
    int getBlockFaceShape(LevelSource* levelSource, const BlockState* blockState, const BlockPos& pos,
                          const Direction* direction) override;
    AABB* getClipAABB(const BlockState* blockState, LevelSource* levelSource, const BlockPos& pos) override;
    bool isSolidRender(const BlockState* blockState) const override;
    bool mayPick() override;
    void tick(Level* level, const BlockPos& pos, const BlockState* blockState, Random*) override;
    void animateTick(const BlockState* blockState, Level* level, const BlockPos& pos, Random*) override;
    void neighborChanged(const BlockState* blockState, Level* level, const BlockPos& pos, Block*,
                         const BlockPos& pos2) override;
    int getTickDelay(Level* level) override;
    void onPlace(Level* level, const BlockPos& pos, const BlockState* blockState) override;
    int getResourceCount(Random*) override;
    int getRenderLayer() override;
    bool mayPlace(Level* level, const BlockPos& pos) override;
    bool canInstantlyTick() override;
    void registerIcons(IconRegister*) override;
    TextureAtlasSprite* getTexture(const Direction* direction, const BlockState* blockState) override;
    BlockStateDefinition* createBlockStateDefinition() override;

    void setFlammable(Block*, int, int);
    bool canBurn(LevelSource*, const BlockPos&);
    bool isNearRain(Level*, const BlockPos&);
    void checkBurnOut(Level*, const BlockPos&, int, Random*, int);
    bool isValidFireLocation(Level*, const BlockPos&);
    int getFireOdds(Level*, const BlockPos&);
    int getFlameOdds(Block*);
    int getBurnOdd(Block*);
    TextureAtlasSprite* getTextureLayer(int);

private:
    std::unordered_map<Block*, int> mFlameOdds;
    std::unordered_map<Block*, int> mBurnOdds;
    TextureAtlasSprite* mTexture[2];
};
