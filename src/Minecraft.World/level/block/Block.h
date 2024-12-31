#pragma once

#include <memory>
#include <string>
#include <vector>
#include "types.h"

typedef unsigned char uchar;

class AABB;
class BlockEntity;
class BlockPos;
class BlockState;
class BlockStateDefinition;
class BlockTooltipDataHolder;
class Direction;
class Entity;
class Explosion;
class HtmlString;
class IconRegister;
class InteractionHand {
public:
    enum EInteractionHand {};
};
class ItemInstance;
class Level;
class LevelSource;
class LivingEntity;
class Material;
class GasMaterial;
class MaterialColor;
class Mirror;
class Player;
class Random;
class Rotation;
class SoundType;
class Texture;
class Vec3;

class Block {
public:
    Block(Material* material);
    Block(Material* material, const MaterialColor* materialColor);

    const BlockState* defaultBlockState();
    void registerDefaultState(const BlockState* blockState);
    static const BlockState* getStateByIdAndData(int, unsigned char);

    void init(Material* material, const MaterialColor* materialColor);

    virtual bool isTopSolidBlocking(const BlockState* blockState);
    virtual bool isValidSpawn(const BlockState* blockState, std::shared_ptr<Entity>);
    virtual void ParticlesSurviveWithin();
    virtual void GetInteractTooltip(const BlockTooltipDataHolder& blockTooltipDataHolder);
    virtual void GetHitTooltip(const BlockTooltipDataHolder& blockTooltipDataHolder);
    virtual void getMapColor(const BlockState* blockState, LevelSource*, const BlockPos& pos);
    virtual const BlockState* getBlockState(int);
    virtual void convertBlockStateToLegacyData(const BlockState* blockState);
    virtual void fillVirtualBlockStateProperties(const BlockState* blockState, LevelSource*, const BlockPos& pos);
    virtual void rotate(const BlockState* blockState, Rotation*);
    virtual void mirror(const BlockState* blockState, Mirror*);
    virtual ~Block();
    virtual void DerivedInit();
    virtual void sendBlockData(uchar);
    virtual void setSoundType(SoundType const*);
    virtual void setLightBlock(int);
    virtual void setLightEmission(float);
    virtual void setExplodeable(float);
    virtual bool isSolidBlockingCube(const BlockState* blockState);
    virtual bool isSolidBlockingCubeAndNotSignalSource(const BlockState* blockState);
    virtual bool isViewBlocking(const BlockState* blockState);
    virtual bool isCubeShaped(const BlockState* blockState);
    virtual void hasCustomBreakingProgress(const BlockState* blockState);
    virtual bool isPathfindable(LevelSource*, const BlockPos& pos);
    virtual void getRenderShape(const BlockState* blockState);
    virtual void hasInHandRenderOffset();
    virtual void mayReplaceWithPlace(LevelSource*, const BlockPos& pos);
    virtual void setDestroyTime(float);
    virtual void setIndestructible();
    virtual bool isIndestructible();
    virtual void getDestroySpeed(const BlockState* blockState, Level*, const BlockPos& pos);
    virtual void setTicking(bool);
    virtual void disableMipmap();
    virtual void setSemiTransparent();
    virtual bool isTicking();
    virtual void getShape(const BlockState* blockState, LevelSource*, const BlockPos& pos);
    virtual void getLightColor(const BlockState* blockState, LevelSource*, const BlockPos& pos, int);
    virtual void shouldRenderFace(const BlockState* blockState, LevelSource*, const BlockPos& pos, const Direction* direction);
    virtual void getShapes(const BlockState* blockState, LevelSource*, BlockPos const*);
    virtual bool isSolidFace(LevelSource*, const BlockPos& pos, const Direction* direction);
    virtual void getBlockFaceShape(LevelSource*, const BlockState* blockState, const BlockPos& pos, const Direction* direction);
    virtual void getOutlineAABB(const BlockState* blockState, Level*, const BlockPos& pos);
    virtual void addCollisionAABBs(const BlockState* blockState, Level*, const BlockPos& pos, AABB const*, std::vector<AABB*>*, std::shared_ptr<Entity>, bool);
    virtual void addCollisionAABB(const BlockPos& pos, AABB const*, std::vector<AABB*>*, AABB const*);
    virtual void getClipAABB(const BlockState* blockState, LevelSource*, const BlockPos& pos);
    virtual bool isSolidRender(const BlockState* blockState);
    virtual void mayPick(const BlockState* blockState, bool);
    virtual void mayPick();
    virtual void randomTick(Level*, const BlockPos& pos, const BlockState* blockState, Random*);
    virtual void tick(Level*, const BlockPos& pos, const BlockState* blockState, Random*);
    virtual void animateTick(const BlockState* blockState, Level*, const BlockPos& pos, Random*);
    virtual void destroy(Level*, const BlockPos& pos, const BlockState* blockState);
    virtual void neighborChanged(const BlockState* blockState, Level*, const BlockPos& pos, Block*, const BlockPos& pos2);
    virtual void addLights(Level*, const BlockPos& pos);
    virtual void getTickDelay(Level*);
    virtual void onPlace(Level*, const BlockPos& pos, const BlockState* blockState);
    virtual void onRemove(Level*, const BlockPos& pos, const BlockState* blockState);
    virtual void getResourceCount(Random*);
    virtual void getResource(const BlockState* blockState, Random*, int);
    virtual void getDestroyProgress(const BlockState* blockState, std::shared_ptr<Player>, Level*, const BlockPos& pos);
    virtual void spawnResources(Level*, const BlockPos& pos, const BlockState* blockState, int);
    virtual void spawnResources(Level*, const BlockPos& pos, const BlockState* blockState, float, int);
    virtual void popExperience(Level*, const BlockPos& pos, int);
    virtual void getSpawnResourcesAuxValue(const BlockState* blockState);
    virtual void getExplosionResistance(std::shared_ptr<Entity>);
    virtual void clip(const BlockState* blockState, Level*, const BlockPos& pos, Vec3*, Vec3*);
    virtual void clip(const BlockPos& pos, Vec3*, Vec3*, AABB const*);
    virtual void wasExploded(Level*, const BlockPos& pos, Explosion*);
    virtual void getRenderLayer();
    virtual bool mayPlace(Level*, const BlockPos& pos, const Direction* direction);
    virtual bool mayPlace(Level*, const BlockPos& pos);
    virtual void TestUse();
    virtual void TestUse(Level*, const BlockPos& pos, const BlockState* blockState, std::shared_ptr<Player>);
    virtual void use(Level*, const BlockPos& pos, const BlockState* blockState, std::shared_ptr<Player>, InteractionHand::EInteractionHand, const Direction* direction, float, float, float, bool);
    virtual void stepOn(Level*, const BlockPos& pos, std::shared_ptr<Entity>);
    virtual void getStateForPlacement(Level*, const BlockPos& pos, const Direction* direction, float, float, float, int, std::shared_ptr<LivingEntity>);
    virtual void prepareRender(Level*, const BlockPos& pos);
    virtual void attack(Level*, const BlockPos& pos, std::shared_ptr<Player>);
    virtual void handleEntityInside(Level*, const BlockPos& pos, std::shared_ptr<Entity>, Vec3*);
    virtual void getColor();
    virtual void getColor(const BlockState* blockState);
    virtual void getColor(LevelSource*, const BlockPos& pos, int);
    virtual void getColor(LevelSource*, const BlockPos& pos);
    virtual void getColor(LevelSource*, const BlockPos& pos, const BlockState* blockState);
    virtual void getSignal(const BlockState* blockState, LevelSource*, const BlockPos& pos, const Direction* direction);
    virtual bool isSignalSource(const BlockState* blockState);
    virtual void entityInside(Level*, const BlockPos& pos, const BlockState* blockState, std::shared_ptr<Entity> const&);
    virtual void getDirectSignal(const BlockState* blockState, LevelSource*, const BlockPos& pos, const Direction* direction);
    virtual void playerDestroy(Level*, std::shared_ptr<Player>, const BlockPos& pos, const BlockState* blockState, std::shared_ptr<BlockEntity>, not_null_ptr<ItemInstance>);
    virtual bool isSilkTouchable();
    virtual void getSilkTouchItemInstance(const BlockState* blockState);
    virtual void getResourceCountForLootBonus(int, Random*);
    virtual void setPlacedBy(Level*, const BlockPos& pos, const BlockState* blockState, std::shared_ptr<LivingEntity>, not_null_ptr<ItemInstance>);
    virtual void setNameAndDescriptionId(int, int);
    virtual bool isPossibleToRespawnInThis();
    virtual void getName();
    virtual void getDescriptionId(int);
    virtual void getUseDescriptionId();
    virtual void triggerEvent(const BlockState* blockState, Level*, const BlockPos& pos, int, int);
    virtual bool isCollectStatistics();
    virtual void shouldBlockTick(Level*, const BlockPos& pos, const BlockState* blockState);
    virtual void setNotCollectStatistics();
    virtual void getPistonPushReaction(const BlockState* blockState);
    virtual void getShadeBrightness(const BlockState* blockState);
    virtual void fallOn(Level*, const BlockPos& pos, std::shared_ptr<Entity>, float);
    virtual void updateEntityAfterFallOn(Level*, std::shared_ptr<Entity>);
    virtual void getCloneItemInstance(Level*, const BlockPos& pos, const BlockState* blockState);
    virtual void playerWillDestroy(Level*, const BlockPos& pos, const BlockState* blockState, std::shared_ptr<Player>);
    virtual void handleRain(Level*, const BlockPos& pos);
    virtual void canInstantlyTick();
    virtual void dropFromExplosion(Explosion*);
    virtual bool isMatching(Block*);
    virtual void hasAnalogOutputSignal(const BlockState* blockState);
    virtual void getAnalogOutputSignal(const BlockState* blockState, Level*, const BlockPos& pos);
    virtual void setIconName(const std::wstring&);
    virtual void getIconName();
    virtual void registerIcons(IconRegister*);
    virtual void getTileItemIconName();
    virtual void getIconTexture(const Direction* direction, const BlockState* blockState);
    virtual void getTexture(LevelSource*, const BlockPos& pos, const Direction* direction, const BlockState* blockState);
    virtual void getTexture(const Direction* direction, const BlockState* blockState);
    virtual void getTexture(const Direction* direction);
    virtual void getInventoryRenderState(const BlockState* blockState);
    virtual BlockStateDefinition* createBlockStateDefinition();
    virtual void getBlockStateDefinition();
    virtual void getOffsetType();
    virtual void getOffset(const BlockState* blockState, LevelSource*, const BlockPos& pos);
    virtual void getSoundType();
    virtual void toString();
    virtual void appendHoverText(not_null_ptr<ItemInstance>, std::shared_ptr<Player>, std::vector<HtmlString>*, bool);
    virtual bool isLiquidBlock();

    Material* getMaterial();

    int field_8;
    bool field_C;
    std::wstring mItemName;
    int field_24;
    bool field_28;
    int lightEmission;
    bool isBlocksLight;
    int mLightEmission;
    bool field_3C;
    bool isDisableMipmap;
    bool field_3E;
    bool isSemiTransparent;
    float mDestroyTime;
    float mExplosionResistance;
    bool mIsCollectStatistics;
    bool mIsTicking;
    bool mIsSilkTouchable;
    bool field_4B;
    int mMaterialType;
    int mBaseItemType;
    char isInited;
    const SoundType* mSoundType;
    float field_60;
    Material* mMaterial;
    const MaterialColor* mMapColor;
    float mFriction;
    BlockStateDefinition* mBlockStateDefinition;
    const BlockState* mBlockState;
    int mDescriptionId;
    int mUseDescriptionId;
    Texture* mTexture;
    int field_A0;
};

ASSERT_SIZEOF(Block, 0xA8)