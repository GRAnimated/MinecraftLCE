#pragma once

#include "types.h"
#include "Minecraft.World/InteractionHand.h"
#include "Minecraft.World/level/block/state/BlockState.h"
#include <memory>
#include <string>
#include <vector>

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
class Item;

class Block {
public:
    Block(Material* material);
    Block(Material* material, const MaterialColor* materialColor);

    const BlockState* defaultBlockState();
    void registerDefaultState(const BlockState* blockState);
    static const BlockState* getStateByIdAndData(int, unsigned char);

    static void registerBlock(int id, std::wstring const& name, Block* block);

    void init(Material* material, const MaterialColor* materialColor);

    virtual bool isTopSolidBlocking(const BlockState* blockState);
    virtual bool isValidSpawn(const BlockState* blockState, std::shared_ptr<Entity>);
    virtual void ParticlesSurviveWithin();
    virtual void GetInteractTooltip(const BlockTooltipDataHolder& blockTooltipDataHolder);
    virtual void GetHitTooltip(const BlockTooltipDataHolder& blockTooltipDataHolder);
    virtual MaterialColor* getMapColor(const BlockState* blockState, LevelSource* levelSource,
                                       const BlockPos& pos);
    virtual const BlockState* getBlockState(int);
    virtual int convertBlockStateToLegacyData(const BlockState* blockState);
    virtual const BlockState* fillVirtualBlockStateProperties(const BlockState* blockState,
                                                              LevelSource* levelSource, const BlockPos& pos);
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
    virtual bool isPathfindable(LevelSource* levelSource, const BlockPos& pos);
    virtual RenderShape getRenderShape(const BlockState* blockState);
    virtual void hasInHandRenderOffset();
    virtual bool mayReplaceWithPlace(LevelSource* levelSource, const BlockPos& pos);
    virtual void setDestroyTime(float);
    virtual void setIndestructible();
    virtual bool isIndestructible();
    virtual void getDestroySpeed(const BlockState* blockState, Level* level, const BlockPos& pos);
    virtual void setTicking(bool);
    virtual void disableMipmap();
    virtual void setSemiTransparent();
    virtual bool isTicking();
    virtual AABB* getShape(const BlockState* blockState, LevelSource* levelSource, const BlockPos& pos);
    virtual void getLightColor(const BlockState* blockState, LevelSource* levelSource, const BlockPos& pos,
                               int);
    virtual bool shouldRenderFace(const BlockState* blockState, LevelSource* levelSource, const BlockPos& pos,
                                  const Direction* direction);
    virtual AABB* getShapes(const BlockState* blockState, LevelSource* levelSource, BlockPos const*);
    virtual bool isSolidFace(LevelSource* levelSource, const BlockPos& pos, const Direction* direction);
    virtual int getBlockFaceShape(LevelSource* levelSource, const BlockState* blockState, const BlockPos& pos,
                                  const Direction* direction);
    virtual void getOutlineAABB(const BlockState* blockState, Level* level, const BlockPos& pos);
    virtual void addCollisionAABBs(const BlockState* blockState, Level* level, const BlockPos& pos,
                                   AABB const*, std::vector<AABB*>*, std::shared_ptr<Entity>, bool);
    virtual void addCollisionAABB(const BlockPos& pos, AABB const*, std::vector<AABB*>*, AABB const*);
    virtual AABB* getClipAABB(const BlockState* blockState, LevelSource* levelSource, const BlockPos& pos);
    virtual bool isSolidRender(const BlockState* blockState) const;
    virtual bool mayPick(const BlockState* blockState, bool);
    virtual bool mayPick();
    virtual void randomTick(Level* level, const BlockPos& pos, const BlockState* blockState, Random*);
    virtual void tick(Level* level, const BlockPos& pos, const BlockState* blockState, Random*);
    virtual void animateTick(const BlockState* blockState, Level* level, const BlockPos& pos, Random*);
    virtual void destroy(Level* level, const BlockPos& pos, const BlockState* blockState);
    virtual void neighborChanged(const BlockState* blockState, Level* level, const BlockPos& pos, Block*,
                                 const BlockPos& pos2);
    virtual void addLights(Level* level, const BlockPos& pos);
    virtual int getTickDelay(Level* level);
    virtual void onPlace(Level* level, const BlockPos& pos, const BlockState* blockState);
    virtual void onRemove(Level* level, const BlockPos& pos, const BlockState* blockState);
    virtual int getResourceCount(Random*);
    virtual Item* getResource(const BlockState* blockState, Random*, int);
    virtual void getDestroyProgress(const BlockState* blockState, std::shared_ptr<Player> player,
                                    Level* level, const BlockPos& pos);
    virtual void spawnResources(Level* level, const BlockPos& pos, const BlockState* blockState, int);
    virtual void spawnResources(Level* level, const BlockPos& pos, const BlockState* blockState, float, int);
    virtual void popExperience(Level* level, const BlockPos& pos, int);
    virtual void getSpawnResourcesAuxValue(const BlockState* blockState);
    virtual void getExplosionResistance(std::shared_ptr<Entity>);
    virtual void clip(const BlockState* blockState, Level* level, const BlockPos& pos, Vec3*, Vec3*);
    virtual void clip(const BlockPos& pos, Vec3*, Vec3*, AABB const*);
    virtual void wasExploded(Level* level, const BlockPos& pos, Explosion*);
    virtual int getRenderLayer();
    virtual bool mayPlace(Level* level, const BlockPos& pos, const Direction* direction);
    virtual bool mayPlace(Level* level, const BlockPos& pos);
    virtual void TestUse();
    virtual void TestUse(Level* level, const BlockPos& pos, const BlockState* blockState,
                         std::shared_ptr<Player> player);
    virtual void use(Level* level, const BlockPos& pos, const BlockState* blockState,
                     std::shared_ptr<Player> player, InteractionHand::EInteractionHand,
                     const Direction* direction, float, float, float, bool);
    virtual void stepOn(Level* level, const BlockPos& pos, std::shared_ptr<Entity>);
    virtual void getStateForPlacement(Level* level, const BlockPos& pos, const Direction* direction, float,
                                      float, float, int, std::shared_ptr<LivingEntity>);
    virtual void prepareRender(Level* level, const BlockPos& pos);
    virtual void attack(Level* level, const BlockPos& pos, std::shared_ptr<Player> player);
    virtual void handleEntityInside(Level* level, const BlockPos& pos, std::shared_ptr<Entity>, Vec3*);
    virtual int getColor() const;
    virtual int getColor(const BlockState* blockState);
    virtual int getColor(LevelSource* levelSource, const BlockPos& pos, int);
    virtual int getColor(LevelSource* levelSource, const BlockPos& pos);
    virtual int getColor(LevelSource* levelSource, const BlockPos& pos, const BlockState* blockState);
    virtual void getSignal(const BlockState* blockState, LevelSource* levelSource, const BlockPos& pos,
                           const Direction* direction);
    virtual bool isSignalSource(const BlockState* blockState);
    virtual void entityInside(Level* level, const BlockPos& pos, const BlockState* blockState,
                              std::shared_ptr<Entity> const&);
    virtual void getDirectSignal(const BlockState* blockState, LevelSource* levelSource, const BlockPos& pos,
                                 const Direction* direction);
    virtual void playerDestroy(Level* level, std::shared_ptr<Player> player, const BlockPos& pos,
                               const BlockState* blockState, std::shared_ptr<BlockEntity>,
                               not_null_ptr<ItemInstance>);
    virtual bool isSilkTouchable();
    virtual void getSilkTouchItemInstance(const BlockState* blockState);
    virtual int getResourceCountForLootBonus(int, Random*);
    virtual void setPlacedBy(Level* level, const BlockPos& pos, const BlockState* blockState,
                             std::shared_ptr<LivingEntity>, not_null_ptr<ItemInstance>);
    virtual void setNameAndDescriptionId(int, int);
    virtual bool isPossibleToRespawnInThis();
    virtual void getName();
    virtual void getDescriptionId(int);
    virtual void getUseDescriptionId();
    virtual void triggerEvent(const BlockState* blockState, Level* level, const BlockPos& pos, int, int);
    virtual bool isCollectStatistics();
    virtual bool shouldBlockTick(Level* level, const BlockPos& pos, const BlockState* blockState);
    virtual void setNotCollectStatistics();
    virtual void getPistonPushReaction(const BlockState* blockState);
    virtual float getShadeBrightness(const BlockState* blockState);
    virtual void fallOn(Level* level, const BlockPos& pos, std::shared_ptr<Entity>, float);
    virtual void updateEntityAfterFallOn(Level* level, std::shared_ptr<Entity>);
    virtual std::shared_ptr<ItemInstance> getCloneItemInstance(Level* level, const BlockPos& pos,
                                                               const BlockState* blockState);
    virtual void playerWillDestroy(Level* level, const BlockPos& pos, const BlockState* blockState,
                                   std::shared_ptr<Player> player);
    virtual void handleRain(Level* level, const BlockPos& pos);
    virtual bool canInstantlyTick();
    virtual void dropFromExplosion(Explosion*);
    virtual bool isMatching(Block*);
    virtual void hasAnalogOutputSignal(const BlockState* blockState);
    virtual void getAnalogOutputSignal(const BlockState* blockState, Level* level, const BlockPos& pos);
    virtual void setIconName(const std::wstring&);
    virtual void getIconName();
    virtual void registerIcons(IconRegister*);
    virtual void getTileItemIconName();
    virtual void getIconTexture(const Direction* direction, const BlockState* blockState);
    virtual Texture* getTexture(LevelSource* levelSource, const BlockPos& pos, const Direction* direction,
                                const BlockState* blockState);
    virtual Texture* getTexture(const Direction* direction, const BlockState* blockState);
    virtual Texture* getTexture(const Direction* direction);
    virtual void getInventoryRenderState(const BlockState* blockState);
    virtual BlockStateDefinition* createBlockStateDefinition();
    virtual void getBlockStateDefinition();
    virtual void getOffsetType();
    virtual void getOffset(const BlockState* blockState, LevelSource* levelSource, const BlockPos& pos);
    virtual void getSoundType();
    virtual void toString();
    virtual void appendHoverText(not_null_ptr<ItemInstance>, std::shared_ptr<Player> player,
                                 std::vector<HtmlString>*, bool);
    virtual bool isLiquidBlock();

    Material* getMaterial();
    static int getId(Block* block);

    static Block* byId(int id);
    static void popResource(Level*, BlockPos const&, not_null_ptr<ItemInstance>);

    static void CreateNewThreadStorage();

    class ThreadStorage {};

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
