#pragma once

#include "net/minecraft/util/ThreadStorage.h"
#include "net/minecraft/world/ArrayWithLength.h"
#include "net/minecraft/world/InteractionHand.h"
#include "net/minecraft/world/level/block/BlockShapes.h"
#include "net/minecraft/world/level/block/state/BlockState.h"
#include "types.h"
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
class TextureAtlasSprite;
class Vec3;
class Item;
class ResourceLocation;
class HitResult;

class Block {
public:
    Block(Material* material);
    Block(Material* material, const MaterialColor* materialColor);

    const BlockState* defaultBlockState();
    void registerDefaultState(const BlockState* state);
    static const BlockState* getStateByIdAndData(int id, uchar data);
    static const BlockState* stateByIdWithData(int idWithData);

    static void registerBlock(int id, const std::wstring& name, Block* block);
    static void registerBlock(int id, const ResourceLocation& rLoc, Block* block);

    void init(Material* material, const MaterialColor* materialColor);

    virtual bool isTopSolidBlocking(const BlockState* state);
    virtual bool isValidSpawn(const BlockState* state, std::shared_ptr<Entity>);
    virtual bool ParticlesSurviveWithin();
    virtual int GetInteractTooltip(const BlockTooltipDataHolder& blockTooltipDataHolder);
    virtual int GetHitTooltip(const BlockTooltipDataHolder& blockTooltipDataHolder);
    virtual const MaterialColor* getMapColor(const BlockState* state, LevelSource* levelSource,
                                             const BlockPos& pos);
    virtual const BlockState* getBlockState(int data);
    virtual int convertBlockStateToLegacyData(const BlockState* state);
    virtual const BlockState* fillVirtualBlockStateProperties(const BlockState* state,
                                                              LevelSource* levelSource, const BlockPos& pos);
    virtual const BlockState* rotate(const BlockState* state, Rotation* rotation);
    virtual const BlockState* mirror(const BlockState* state, Mirror* mirror);
    virtual ~Block();
    virtual void DerivedInit();
    virtual Block* sendBlockData(uchar data);
    virtual Block* setSoundType(const SoundType* soundType);
    virtual Block* setLightBlock(int lightBlock);
    virtual Block* setLightEmission(float lightEmission);
    virtual Block* setExplodeable(float explode);
    virtual bool isSolidBlockingCube(const BlockState* state);
    virtual bool isSolidBlockingCubeAndNotSignalSource(const BlockState* state);
    virtual bool isViewBlocking(const BlockState* state);
    virtual bool isCubeShaped(const BlockState* state);
    virtual bool hasCustomBreakingProgress(const BlockState* state);
    virtual bool isPathfindable(LevelSource* levelSource, const BlockPos& pos);
    virtual RenderShape getRenderShape(const BlockState* state);
    virtual bool hasInHandRenderOffset();
    virtual bool mayReplaceWithPlace(LevelSource* levelSource, const BlockPos& pos);
    virtual Block* setDestroyTime(float destroyTime);
    virtual Block* setIndestructible();
    virtual bool isIndestructible();
    virtual float getDestroySpeed(const BlockState* state, Level* level, const BlockPos& pos);
    virtual void setTicking(bool ticking);
    virtual Block* disableMipmap();
    virtual Block* setSemiTransparent();
    virtual bool isTicking();
    virtual const AABB* getShape(const BlockState* state, LevelSource* levelSource, const BlockPos& pos);
    virtual int getLightColor(const BlockState* state, LevelSource* levelSource, const BlockPos& pos, int);
    virtual bool shouldRenderFace(const BlockState* state, LevelSource* levelSource, const BlockPos& pos,
                                  const Direction* direction);
    virtual arrayWithLength<const AABB*>* getShapes(const BlockState* state, LevelSource* levelSource,
                                                    const BlockPos& pos);
    virtual bool isSolidFace(LevelSource* levelSource, const BlockPos& pos, const Direction* direction);
    virtual int getBlockFaceShape(LevelSource* levelSource, const BlockState* state, const BlockPos& pos,
                                  const Direction* direction);
    virtual const AABB* getOutlineAABB(const BlockState* state, Level* level, const BlockPos& pos);
    virtual void addCollisionAABBs(const BlockState* state, Level* level, const BlockPos& pos,
                                   AABB const* aabb, std::vector<AABB*>* AABBs, std::shared_ptr<Entity> ent,
                                   bool);
    virtual void addCollisionAABB(const BlockPos& pos, AABB const* aabb, std::vector<AABB*>* AABBs,
                                  AABB const* aabb2);
    virtual const AABB* getClipAABB(const BlockState* state, LevelSource* levelSource, const BlockPos& pos);
    virtual bool isSolidRender(const BlockState* state) const;
    virtual bool mayPick(const BlockState* state, bool);
    virtual bool mayPick();
    virtual void randomTick(Level* level, const BlockPos& pos, const BlockState* state, Random*);
    virtual void tick(Level* level, const BlockPos& pos, const BlockState* state, Random*);
    virtual void animateTick(const BlockState* state, Level* level, const BlockPos& pos, Random*);
    virtual void destroy(Level* level, const BlockPos& pos, const BlockState* state);
    virtual void neighborChanged(const BlockState* state, Level* level, const BlockPos& pos, Block*,
                                 const BlockPos& neighborPos);
    virtual void addLights(Level* level, const BlockPos& pos);
    virtual int getTickDelay(Level* level);
    virtual void onPlace(Level* level, const BlockPos& pos, const BlockState* state);
    virtual void onRemove(Level* level, const BlockPos& pos, const BlockState* state);
    virtual int getResourceCount(Random*);
    virtual Item* getResource(const BlockState* state, Random*, int);
    virtual float getDestroyProgress(const BlockState* state, std::shared_ptr<Player> player, Level* level,
                                     const BlockPos& pos);
    virtual void spawnResources(Level* level, const BlockPos& pos, const BlockState* state, int);
    virtual void spawnResources(Level* level, const BlockPos& pos, const BlockState* state, float chance,
                                int fortuneLevel);
    virtual void popExperience(Level* level, const BlockPos& pos, int amount);
    virtual int getSpawnResourcesAuxValue(const BlockState* state);
    virtual float getExplosionResistance(std::shared_ptr<Entity>);
    virtual HitResult* clip(const BlockState* state, Level* level, const BlockPos& pos, Vec3*, Vec3*);
    virtual HitResult* clip(const BlockPos& pos, Vec3*, Vec3*, AABB const*);
    virtual void wasExploded(Level* level, const BlockPos& pos, Explosion*);
    virtual int getRenderLayer();
    virtual bool mayPlace(Level* level, const BlockPos& pos, const Direction* direction);
    virtual bool mayPlace(Level* level, const BlockPos& pos);
    virtual bool TestUse();
    virtual bool TestUse(Level* level, const BlockPos& pos, const BlockState* state,
                         std::shared_ptr<Player> player);
    virtual bool use(Level* level, const BlockPos& pos, const BlockState* state,
                     std::shared_ptr<Player> player, InteractionHand::EInteractionHand,
                     const Direction* direction, float, float, float, bool);
    virtual void stepOn(Level* level, const BlockPos& pos, std::shared_ptr<Entity>);
    virtual const BlockState* getStateForPlacement(Level* level, const BlockPos& pos,
                                                   const Direction* direction, float, float, float, int,
                                                   std::shared_ptr<LivingEntity>);
    virtual void prepareRender(Level* level, const BlockPos& pos);
    virtual void attack(Level* level, const BlockPos& pos, std::shared_ptr<Player> player);
    virtual Vec3* handleEntityInside(Level* level, const BlockPos& pos, std::shared_ptr<Entity>, Vec3*);
    virtual int getColor() const;
    virtual int getColor(const BlockState* state);
    virtual int getColor(LevelSource* levelSource, const BlockPos& pos, int);
    virtual int getColor(LevelSource* levelSource, const BlockPos& pos);
    virtual int getColor(LevelSource* levelSource, const BlockPos& pos, const BlockState* state);
    virtual int getSignal(const BlockState* state, LevelSource* levelSource, const BlockPos& pos,
                          const Direction* direction);
    virtual bool isSignalSource(const BlockState* state);
    virtual void entityInside(Level* level, const BlockPos& pos, const BlockState* state,
                              const std::shared_ptr<Entity>&);
    virtual int getDirectSignal(const BlockState* state, LevelSource* levelSource, const BlockPos& pos,
                                const Direction* direction);
    virtual void playerDestroy(Level* level, std::shared_ptr<Player> player, const BlockPos& pos,
                               const BlockState* state, std::shared_ptr<BlockEntity>,
                               not_null_ptr<ItemInstance>);
    virtual bool isSilkTouchable();
    virtual not_null_ptr<ItemInstance> getSilkTouchItemInstance(const BlockState* state);
    virtual int getResourceCountForLootBonus(int fortuneLevel, Random* random);
    virtual void setPlacedBy(Level* level, const BlockPos& pos, const BlockState* state,
                             std::shared_ptr<LivingEntity>, not_null_ptr<ItemInstance>);
    virtual Block* setNameAndDescriptionId(int name, int desc);
    virtual bool isPossibleToRespawnInThis();
    virtual std::wstring getName();
    virtual unsigned int getDescriptionId(int);
    virtual unsigned int getUseDescriptionId();
    virtual bool triggerEvent(const BlockState* state, Level* level, const BlockPos& pos, int, int);
    virtual bool isCollectStatistics();
    virtual bool shouldBlockTick(Level* level, const BlockPos& pos, const BlockState* state);
    virtual Block* setNotCollectStatistics();
    virtual int getPistonPushReaction(const BlockState* state);
    virtual float getShadeBrightness(const BlockState* state);
    virtual void fallOn(Level* level, const BlockPos& pos, std::shared_ptr<Entity>, float);
    virtual void updateEntityAfterFallOn(Level* level, std::shared_ptr<Entity>);
    virtual not_null_ptr<ItemInstance> getCloneItemInstance(Level* level, const BlockPos& pos,
                                                            const BlockState* state);
    virtual void playerWillDestroy(Level* level, const BlockPos& pos, const BlockState* state,
                                   std::shared_ptr<Player> player);
    virtual void handleRain(Level* level, const BlockPos& pos);
    virtual bool canInstantlyTick();
    virtual bool dropFromExplosion(Explosion*);
    virtual bool isMatching(Block*);
    virtual bool hasAnalogOutputSignal(const BlockState* state);
    virtual int getAnalogOutputSignal(const BlockState* state, Level* level, const BlockPos& pos);
    virtual Block* setIconName(const std::wstring&);
    virtual std::wstring getIconName();
    virtual void registerIcons(IconRegister*);
    virtual std::wstring getTileItemIconName();
    virtual TextureAtlasSprite* getIconTexture(const Direction* direction, const BlockState* state);
    virtual TextureAtlasSprite* getTexture(LevelSource* levelSource, const BlockPos& pos,
                                           const Direction* direction, const BlockState* state);
    virtual TextureAtlasSprite* getTexture(const Direction* direction, const BlockState* state);
    virtual TextureAtlasSprite* getTexture(const Direction* direction);
    virtual const BlockState* getInventoryRenderState(const BlockState* state);
    virtual BlockStateDefinition* createBlockStateDefinition();
    virtual BlockStateDefinition* getBlockStateDefinition();
    virtual int getOffsetType();  // enum prob
    virtual Vec3* getOffset(const BlockState* state, LevelSource* levelSource, const BlockPos& pos);
    virtual const SoundType* getSoundType();
    virtual std::wstring toString();
    virtual void appendHoverText(not_null_ptr<ItemInstance>, std::shared_ptr<Player> player,
                                 std::vector<HtmlString>*, bool);
    virtual bool isLiquidBlock();

    Material* getMaterial();
    int getId();
    bool neighbourVisibleThroughShapes(const arrayWithLength<AABB const*>*, LevelSource*, const BlockPos&,
                                       const Direction*);

    static Block* byId(int id);
    static void popResource(Level*, const BlockPos&, not_null_ptr<ItemInstance>);
    static int getIdWithData(const BlockState*);
    static bool isExceptionBlockForAttaching(Block*);
    static bool isExceptionBlockForAttachingPlusPiston(Block*);

    static void staticCtor();
    Block* setBaseItemTypeAndMaterial(int, int);

    bool isBlockEntity() const {
        return mSilkTouchable;
    }  // I think we have this one wrong... also guessed name

    int getLightEmission(const BlockState* state) const { return this->mLightEmission; }

    START_DECLARE_THREAD_STORAGE()
    void* fill;
    bool fill2;
    arrayWithLength<const AABB*> mAABBs;
    END_DECLARE_THREAD_STORAGE()

private:
    static const AABB* defaultBlockShape;
    static int sDefaultDirectSignal;

public:
    int field_8;
    bool field_C;
    std::wstring mIconName;
    int mId;
    bool field_28;
    int mLightBlock;
    bool isBlocksLight;
    int mLightEmission;
    bool field_3C;
    bool mMipmapEnabled;
    uchar mSendBlockData;
    bool mSemiTransparent;
    float mDestroyTime;
    float mExplosionResistance;
    bool mCollectStatistics;
    bool mTicking;
    bool mSilkTouchable;
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
    unsigned int mDescriptionId;
    unsigned int mUseDescriptionId;
    TextureAtlasSprite* mTexture;
    int field_A0;
};

ASSERT_SIZEOF(Block, 0xA8)
