#include "net/minecraft/world/level/block/Block.h"

#include "NX/Platform.h"
#include "net/minecraft/client/Minecraft.h"
#include "net/minecraft/client/multiplayer/MultiPlayerLevel.h"
#include "net/minecraft/client/ui/StringIDs.h"
#include "net/minecraft/core/BlockPos.h"
#include "net/minecraft/resources/ResourceLocation.h"
#include "net/minecraft/util/Mth.h"
#include "net/minecraft/world/eINSTANCEOF.h"
#include "net/minecraft/world/entity/Entity.h"
#include "net/minecraft/world/entity/item/ExperienceOrb.h"
#include "net/minecraft/world/entity/item/FireworksRocketEntity.h"
#include "net/minecraft/world/entity/player/MultiplayerLocalPlayer.h"
#include "net/minecraft/world/item/DyeColor.h"
#include "net/minecraft/world/item/InteractionResultHolder.h"
#include "net/minecraft/world/item/Item.h"
#include "net/minecraft/world/item/ItemInstance.h"
#include "net/minecraft/world/item/Items.h"
#include "net/minecraft/world/item/LeadItem.h"
#include "net/minecraft/world/level/Explosion.h"
#include "net/minecraft/world/level/block/AirBlock.h"
#include "net/minecraft/world/level/block/AnvilBlock.h"
#include "net/minecraft/world/level/block/BannerBlock.h"
#include "net/minecraft/world/level/block/BedBlock.h"
#include "net/minecraft/world/level/block/BlockShapes.h"
#include "net/minecraft/world/level/block/BlockTooltipDataHolder.h"
#include "net/minecraft/world/level/block/Blocks.h"
#include "net/minecraft/world/level/block/ButtonBlock.h"
#include "net/minecraft/world/level/block/ChestBlock.h"
#include "net/minecraft/world/level/block/ColoredBlock.h"
#include "net/minecraft/world/level/block/ComparatorBlock.h"
#include "net/minecraft/world/level/block/ConcretePowderBlock.h"
#include "net/minecraft/world/level/block/DetectorRailBlock.h"
#include "net/minecraft/world/level/block/DirectionalBlock.h"
#include "net/minecraft/world/level/block/DirtBlock.h"
#include "net/minecraft/world/level/block/DispenserBlock.h"
#include "net/minecraft/world/level/block/DoorBlock.h"
#include "net/minecraft/world/level/block/DoublePlantBlock.h"
#include "net/minecraft/world/level/block/EndPortalFrameBlock.h"
#include "net/minecraft/world/level/block/EnderChestBlock.h"
#include "net/minecraft/world/level/block/FlowerPotBlock.h"
#include "net/minecraft/world/level/block/FurnaceBlock.h"
#include "net/minecraft/world/level/block/HalfSlabBlock.h"
#include "net/minecraft/world/level/block/HopperBlock.h"
#include "net/minecraft/world/level/block/HorizontalDirectionalBlock.h"
#include "net/minecraft/world/level/block/HugeMushroomBlock.h"
#include "net/minecraft/world/level/block/LadderBlock.h"
#include "net/minecraft/world/level/block/LeafBlock.h"
#include "net/minecraft/world/level/block/LeverBlock.h"
#include "net/minecraft/world/level/block/LogBlock.h"
#include "net/minecraft/world/level/block/MonsterEggBlock.h"
#include "net/minecraft/world/level/block/NewLeafBlock.h"
#include "net/minecraft/world/level/block/NewLogBlock.h"
#include "net/minecraft/world/level/block/NewStoneSlabBlock.h"
#include "net/minecraft/world/level/block/NoteBlock.h"
#include "net/minecraft/world/level/block/OldLeafBlock.h"
#include "net/minecraft/world/level/block/OldLogBlock.h"
#include "net/minecraft/world/level/block/PistonBaseBlock.h"
#include "net/minecraft/world/level/block/PistonHeadBlock.h"
#include "net/minecraft/world/level/block/PistonMagicBlock.h"
#include "net/minecraft/world/level/block/PlanksBlock.h"
#include "net/minecraft/world/level/block/PortalBlock.h"
#include "net/minecraft/world/level/block/PoweredRailBlock.h"
#include "net/minecraft/world/level/block/PrismarineBlock.h"
#include "net/minecraft/world/level/block/PurpurSlabBlock.h"
#include "net/minecraft/world/level/block/QuartzBlock.h"
#include "net/minecraft/world/level/block/RailBlock.h"
#include "net/minecraft/world/level/block/RedSandStoneBlock.h"
#include "net/minecraft/world/level/block/RedStoneWireBlock.h"
#include "net/minecraft/world/level/block/RotatedPillarBlock.h"
#include "net/minecraft/world/level/block/SandBlock.h"
#include "net/minecraft/world/level/block/SandStoneBlock.h"
#include "net/minecraft/world/level/block/SaplingBlock.h"
#include "net/minecraft/world/level/block/ShulkerBoxBlock.h"
#include "net/minecraft/world/level/block/SkullBlock.h"
#include "net/minecraft/world/level/block/SoundType.h"
#include "net/minecraft/world/level/block/StainedGlassBlock.h"
#include "net/minecraft/world/level/block/StainedGlassPaneBlock.h"
#include "net/minecraft/world/level/block/StainedHardenedClayBlock.h"
#include "net/minecraft/world/level/block/StairBlock.h"
#include "net/minecraft/world/level/block/StemBlock.h"
#include "net/minecraft/world/level/block/StoneBlock.h"
#include "net/minecraft/world/level/block/StoneBrickBlock.h"
#include "net/minecraft/world/level/block/StoneSlabBlock.h"
#include "net/minecraft/world/level/block/TallGrassBlock.h"
#include "net/minecraft/world/level/block/TorchBlock.h"
#include "net/minecraft/world/level/block/TrapDoorBlock.h"
#include "net/minecraft/world/level/block/TripWireHookBlock.h"
#include "net/minecraft/world/level/block/WallBlock.h"
#include "net/minecraft/world/level/block/WallSignBlock.h"
#include "net/minecraft/world/level/block/WoodSlabBlock.h"
#include "net/minecraft/world/level/block/WoolCarpetBlock.h"
#include "net/minecraft/world/level/block/state/BlockState.h"
#include "net/minecraft/world/level/block/state/BlockStateDefinition.h"
#include "net/minecraft/world/level/dimension/Dimension.h"
#include "net/minecraft/world/level/gamemode/GameMode.h"
#include "net/minecraft/world/level/material/Material.h"
#include "net/minecraft/world/phys/AABB.h"
#include "net/minecraft/world/phys/HitResult.h"

#include <cstdint>
#include <memory>
#include <string>

const AABB* Block::defaultBlockShape = AABB::newPermanent(0.0, 0.0, 0.0, 1.0, 1.0, 1.0);

Block::Block(Material* material) {
    init(material, material->getColor());
}

Block::Block(Material* material, const MaterialColor* color) {
    init(material, color);
}

Block::~Block() {}

const BlockState* Block::defaultBlockState() {
    return mBlockState;
}

void Block::registerDefaultState(const BlockState* state) {
    mBlockState = state;
}

void Block::init(Material* material, const MaterialColor* color) {
    field_A0 = 0;
    mExplosionResistance = 0.0f;
    mCollectStatistics = true;

    mSoundType = SoundType::STONE;

    mDestroyTime = 0.0f;
    mTicking = false;
    mSilkTouchable = false;
    field_60 = 1.0f;
    mFriction = 0.6f;
    mMaterial = material;
    mMapColor = color;
    mLightEmission = 0;

    bool isEnableLight = material->blocksLight();

    mMipmapEnabled = true;
    mSemiTransparent = false;
    field_3C = false;
    mMaterialType = 0;
    mBaseItemType = 0;

    isBlocksLight = !isEnableLight;

    mTexture = nullptr;
    isInited = false;
    field_8 = 0;
    field_C = false;
}

bool Block::isTopSolidBlocking(const BlockState* state) {
    return state->getMaterial()->isSolidBlocking() && state->isCubeShaped();
}

bool Block::isValidSpawn(const BlockState* state, std::shared_ptr<Entity>) {
    return true;
}

bool Block::ParticlesSurviveWithin() {
    return false;
}

// NON_MATCHING: play with ifs in cases (so they are not optimised, the ifs) logic should be the same (unless
// I broke something while trying to match)
int Block::GetInteractTooltip(const BlockTooltipDataHolder& data) {
    int blockId = data.mItemInstance->getItem()->getId();
    // int returnValue = 0xFFFFFFFF;
    switch (blockId) {
    case 0:
    case 126:
        if (data.mInteractionResult != InteractionResult::FAIL && data.mBelowBuildHeight)
            return StringIDs::Ignite;
        return 0xFFFFFFFF;
    case 36:
    case 79:
    case 102:
    case 103:
    case 113:
    case 132:
    case 133:
    case 176:
        if (data.mInteractionResult != InteractionResult::FAIL)
            return StringIDs::Plant;
        if (!data.mBelowBuildHeight)
            return 0xFFFFFFFF;
        return StringIDs::Plant;
    case 62:
    case 130:
        if (data.mInteractionResult != InteractionResult::SUCCESS)
            return StringIDs::Hang;
        return 0xFFFFFFFF;
    case 66:
        return 0xFFFFFFFF;
    case 67:
    case 68:
        if (!data.mInteractionResult && data.mBelowBuildHeight)
            return StringIDs::Empty;
        return 0xFFFFFFFF;
    case 92:
        if (data.mInteractionResult != InteractionResult::FAIL
            && DyeColor::byItemData(data.mItemInstance->getAuxValue())->getBlockData() == 12)
            return StringIDs::Plant;
        return 0xFFFFFFFF;
    case 142:
        if (data.mInteractionResult != InteractionResult::FAIL && data.mBelowBuildHeight)
            return StringIDs::Launch;
        return 0xFFFFFFFF;
    case 161:
        if (!data.mInteractionResult && data.mBelowBuildHeight) {
            if (LeadItem::bindPlayerMobsTest((std::shared_ptr<Player>)data.mPlayer, (Level*)data.mLevel,
                                             BlockPos((std::shared_ptr<Entity>)data.mPlayer))) {
                return StringIDs::Attach;
            }
        }
        return 0xFFFFFFFF;
    default:
        if (!data.mInteractionResult && data.mBelowBuildHeight)
            return StringIDs::Place;
        return 0xFFFFFFFF;
    }
}

int Block::GetHitTooltip(const BlockTooltipDataHolder& data) {
    if (!data.mPlayerAllowedToMine)
        return 0xFFFFFFFF;

    if (data.mBlockState->getBlock()->getId() == 7
        && (!data.mPlayer->GetGameMode()->isCreative()
            || !data.mLevel->mDimension->inPlayerConstraints(data.mPos))) {
        return 0xFFFFFFFF;
    }

    return StringIDs::Mine_1;
}

const MaterialColor* Block::getMapColor(const BlockState* state, LevelSource* levelSource,
                                        const BlockPos& pos) {
    return this->mMapColor;
}

const BlockState* Block::getBlockState(int) {
    return this->defaultBlockState();
}

int Block::convertBlockStateToLegacyData(const BlockState* state) {
    state->getProperties();  // some leftover
    return 0;
}

const BlockState* Block::fillVirtualBlockStateProperties(const BlockState* state, LevelSource* levelSource,
                                                         const BlockPos& pos) {
    return state;
}

const BlockState* Block::rotate(const BlockState* state, Rotation*) {
    return state;
}

const BlockState* Block::mirror(const BlockState* state, Mirror*) {
    return state;
}

void Block::DerivedInit() {
    isInited = true;

    mBlockStateDefinition = createBlockStateDefinition();
    registerDefaultState(mBlockStateDefinition->any());

    bool isSolidRender = defaultBlockState()->isSolidRender();
    field_28 = isSolidRender;
    mLightBlock = isSolidRender ? 255 : 0;
}

void Block::sendBlockData(uchar sendBlockData) {
    this->mSendBlockData = sendBlockData;
}

Block* Block::setSoundType(const SoundType* soundType) {
    this->mSoundType = soundType;
    return this;
}

Block* Block::setLightBlock(int light) {
    this->mLightBlock = light;
    return this;
}

Block* Block::setLightEmission(float emission) {
    this->mLightEmission = emission * 15.0f;
    return this;
}

Block* Block::setExplodeable(float explodePower) {
    this->mExplosionResistance = explodePower * 3.0f;
    return this;
}

bool Block::isSolidBlockingCube(const BlockState* state) {
    return this->mMaterial->blocksMotion() && state->isCubeShaped();
}

bool Block::isSolidBlockingCubeAndNotSignalSource(const BlockState* state) {
    return this->mMaterial->isSolidBlocking() && state->isCubeShaped() && !state->isSignalSource();
}

bool Block::isViewBlocking(const BlockState* state) {
    return this->mMaterial->blocksMotion() && this->defaultBlockState()->isCubeShaped();
}

bool Block::isCubeShaped(const BlockState* state) {
    return true;
}

bool Block::hasCustomBreakingProgress(const BlockState* state) {
    return false;
}

bool Block::isPathfindable(LevelSource* levelSource, const BlockPos& pos) {
    return !this->mMaterial->blocksMotion();
}

RenderShape Block::getRenderShape(const BlockState* state) {
    return RenderShape::RenderShape_BLOCK;
}

bool Block::hasInHandRenderOffset() {
    return false;
}

bool Block::mayReplaceWithPlace(LevelSource* levelSource, const BlockPos& pos) {
    return false;
}

Block* Block::setDestroyTime(float time) {
    this->mDestroyTime = time;
    if (this->mExplosionResistance < time * 5.0f)
        this->mExplosionResistance = time * 5.0f;
    return this;
}

Block* Block::setIndestructible() {
    this->setDestroyTime(340282350000000000000000000000000000000.0f);  // wtf is that magic number
    return this;
}

bool Block::isIndestructible() {
    return this->mDestroyTime == 340282350000000000000000000000000000000.0f;
}

float Block::getDestroySpeed(const BlockState* state, Level* level, const BlockPos& pos) {
    return this->mDestroyTime;
}

void Block::setTicking(bool ticking) {
    this->mTicking = ticking;
}

Block* Block::disableMipmap() {
    this->mMipmapEnabled = false;
    return this;
}

Block* Block::setSemiTransparent() {
    this->mSemiTransparent = true;
    return this;
}

bool Block::isTicking() {
    return this->mTicking;
}

const AABB* Block::getShape(const BlockState* state, LevelSource* levelSource, const BlockPos& pos) {
    return Block::defaultBlockShape;
}

// NON_MATCHING: i don't have a clue
int Block::getLightColor(const BlockState* state, LevelSource* levelSource, const BlockPos& pos, int) {
    Block* blockFromLevel = levelSource->getBlockState(pos)->getBlock();
    int color = levelSource->getLightColor(pos, blockFromLevel->getLightEmission(state), 0xFFFFFFFF);

    if (color == 0 && dynamic_cast<HalfSlabBlock*>(blockFromLevel)) {
        BlockPos pos1 = pos.below();
        blockFromLevel = levelSource->getBlockState(pos1)->getBlock();
        color = levelSource->getLightColor(pos1, blockFromLevel->getLightEmission(state), 0xFFFFFFFF);
    }

    return color;
}

bool Block::shouldRenderFace(const BlockState* state, LevelSource* levelSource, const BlockPos& pos,
                             const Direction* direction) {
    if (this->neighbourVisibleThroughShapes(this->getShapes(state, levelSource, pos), levelSource, pos,
                                            direction))
        return true;

    return !levelSource->getBlockState(pos.relative(direction))->isSolidRender();
}

arrayWithLength<const AABB*>* Block::getShapes(const BlockState* state, LevelSource* levelSource,
                                               const BlockPos& pos) {
    ThreadStorage* threadStorage = (ThreadStorage*)TlsGetValue(sThreadStorageIndex);
    threadStorage->mAABBs[0] = this->getShape(state, levelSource, pos);
    threadStorage->mAABBs[1] = nullptr;
    threadStorage->mAABBs[2] = nullptr;
    return &threadStorage->mAABBs;
}

bool Block::isSolidFace(LevelSource* levelSource, const BlockPos& pos, const Direction* direction) {
    return levelSource->getBlockState(pos)->getMaterial()->isSolid();
}

int Block::getBlockFaceShape(LevelSource* levelSource, const BlockState* state, const BlockPos& pos,
                             const Direction* direction) {
    return 0;
}

const AABB* Block::getOutlineAABB(const BlockState* state, Level* level, const BlockPos& pos) {
    return state->getShape(level, pos)->move(pos);
}

void Block::addCollisionAABBs(const BlockState* state, Level* level, const BlockPos& pos, AABB const* aabb,
                              std::vector<AABB*>* aabbsOut, std::shared_ptr<Entity>, bool) {
    return this->addCollisionAABB(pos, aabb, aabbsOut, state->getClipAABB(level, pos));
}

void Block::addCollisionAABB(const BlockPos& pos, AABB const* aabb, std::vector<AABB*>* aabbsOut,
                             AABB const* aabb2) {
    if (aabb2) {
        AABB* moved = aabb2->move(pos);
        if (aabb->intersects(moved)) {
            aabbsOut->push_back(moved);
        }
    }
}

const AABB* Block::getClipAABB(const BlockState* state, LevelSource* levelSource, const BlockPos& pos) {
    return state->getShape(levelSource, pos);
}

bool Block::isSolidRender(const BlockState* state) const {
    return true;
}

bool Block::mayPick(const BlockState* state, bool) {
    return this->mayPick();
}

bool Block::mayPick() {
    return true;
}

void Block::randomTick(Level* level, const BlockPos& pos, const BlockState* state, Random* random) {
    this->tick(level, pos, state, random);
}

void Block::tick(Level* level, const BlockPos& pos, const BlockState* state, Random*) {}

void Block::animateTick(const BlockState* state, Level* level, const BlockPos& pos, Random*) {}

void Block::destroy(Level* level, const BlockPos& pos, const BlockState* state) {}

void Block::neighborChanged(const BlockState* state, Level* level, const BlockPos& pos, Block*,
                            const BlockPos& neighborPos) {}

void Block::addLights(Level* level, const BlockPos& pos) {}

int Block::getTickDelay(Level* level) {
    return 10;
}

void Block::onPlace(Level* level, const BlockPos& pos, const BlockState* state) {}

void Block::onRemove(Level* level, const BlockPos& pos, const BlockState* state) {}

int Block::getResourceCount(Random*) {
    return 1;
}

Item* Block::getResource(const BlockState* state, Random*, int) {
    return Item::byBlock(this);
}

// NON_MATCHING: I don't have a clue
float Block::getDestroyProgress(const BlockState* state, std::shared_ptr<Player> player, Level* level,
                                const BlockPos& pos) {
    float destSpeed = state->getDestroySpeed(level, pos);
    if (destSpeed <= 0.0f)
        return 1.0f;

    int i = player->canDestroy(state) ? 30 : 100;
    return player->getDestroySpeed(state) / destSpeed / i;
}

void Block::spawnResources(Level* level, const BlockPos& pos, const BlockState* state, int fortuneLevel) {
    this->spawnResources(level, pos, state, 1.0f, fortuneLevel);
}

void Block::spawnResources(Level* level, const BlockPos& pos, const BlockState* state, float chance,
                           int fortuneLevel) {
    if (!level->mIsLocal) {
        int resourceCount = this->getResourceCountForLootBonus(fortuneLevel, level->mRandom);
        for (int i = 0; i < resourceCount; i++) {
            if (level->mRandom->nextFloat() > chance)
                continue;

            if (Item* item = this->getResource(state, level->mRandom, fortuneLevel); item != Items::AIR) {
                Block::popResource(level, pos,
                                   new ItemInstance(item, 1, this->getSpawnResourcesAuxValue(state)));
            }
        }
    }
}

void Block::popExperience(Level* level, const BlockPos& pos, int amount) {
    if (!level->mIsLocal && level->getGameRules()->getBoolean(5)) {
        while (amount > 0) {
            int dropAmount = ExperienceOrb::getExperienceValue(amount);
            amount -= dropAmount;
            level->addEntity(std::shared_ptr<ExperienceOrb>(
                new ExperienceOrb(level, pos.getX() + 0.5, pos.getY() + 0.5, pos.getZ() + 0.5, dropAmount)));
        }
    }
}

int Block::getSpawnResourcesAuxValue(const BlockState* state) {
    return 0;
}

float Block::getExplosionResistance(std::shared_ptr<Entity>) {
    return this->mExplosionResistance / 5.0;
}

HitResult* Block::clip(const BlockState* state, Level* level, const BlockPos& pos, Vec3* begin, Vec3* end) {
    return this->clip(pos, begin, end, state->getShape(level, pos));
}

HitResult* Block::clip(const BlockPos& pos, Vec3* begin, Vec3* end, AABB const* shape) {
    Vec3* beginSub = begin->subtract(pos.getX(), pos.getY(), pos.getZ());
    Vec3* endSub = end->subtract(pos.getX(), pos.getY(), pos.getZ());
    HitResult* tempResult = shape->clip(beginSub, endSub);
    if (!tempResult)
        return nullptr;

    HitResult* finalResult = new HitResult(tempResult->mHitVector->add(pos.getX(), pos.getY(), pos.getZ()),
                                           tempResult->mDirection, pos);
    delete tempResult;
    return finalResult;
}

void Block::wasExploded(Level* level, const BlockPos& pos, Explosion* explosion) {
    if (!level->mIsLocal) {
        if (Minecraft::InMiniGame(EMiniGameId::NORMAL_WORLD, true) && explosion) {
            std::shared_ptr<Entity> directSrc = explosion->getDirectSource();
            if (directSrc && directSrc->isType(eFireworksRocketEntity)) {
                std::shared_ptr<FireworksRocketEntity> fireworksEnt
                    = std::static_pointer_cast<FireworksRocketEntity>(directSrc);
                directSrc = fireworksEnt->getOwner();
            }
            if (directSrc && directSrc->isType(ePlayer)) {
                std::shared_ptr<Player> owner = std::static_pointer_cast<Player>(directSrc);
                owner->GetGameMode()->RecordBlockDestroyed(pos, this->getId());
            }
        }
    }
}

int Block::getRenderLayer() {
    return 0;
}

bool Block::mayPlace(Level* level, const BlockPos& pos, const Direction* direction) {
    return this->mayPlace(level, pos);
}

bool Block::mayPlace(Level* level, const BlockPos& pos) {
    return level->getBlockState(pos)->getBlock()->mMaterial->isReplaceable();
}

bool Block::TestUse() {
    return false;
}

bool Block::TestUse(Level* level, const BlockPos& pos, const BlockState* state,
                    std::shared_ptr<Player> player) {
    return false;
}

bool Block::use(Level* level, const BlockPos& pos, const BlockState* state, std::shared_ptr<Player> player,
                InteractionHand::EInteractionHand, const Direction* direction, float, float, float, bool) {
    return false;
}

void Block::stepOn(Level* level, const BlockPos& pos, std::shared_ptr<Entity>) {}

const BlockState* Block::getStateForPlacement(Level* level, const BlockPos& pos, const Direction* direction,
                                              float, float, float, int data, std::shared_ptr<LivingEntity>) {
    return this->getBlockState(data);
}

void Block::prepareRender(Level* level, const BlockPos& pos) {}

void Block::attack(Level* level, const BlockPos& pos, std::shared_ptr<Player> player) {}

Vec3* Block::handleEntityInside(Level* level, const BlockPos& pos, std::shared_ptr<Entity>, Vec3* vec3) {
    return vec3;
}

int Block::getColor() const {
    return 0xFFFFFF;
}

int Block::getColor(const BlockState* state) {
    return 0xFFFFFF;
}

int Block::getColor(LevelSource* levelSource, const BlockPos& pos, int) {
    return 0xFFFFFF;
}

int Block::getColor(LevelSource* levelSource, const BlockPos& pos) {
    return this->getColor(levelSource, pos, 0);
}

int Block::getColor(LevelSource* levelSource, const BlockPos& pos, const BlockState* state) {
    return 0xFFFFFF;
}

int Block::getSignal(const BlockState* state, LevelSource* levelSource, const BlockPos& pos,
                     const Direction* direction) {
    return 0;
}

bool Block::isSignalSource(const BlockState* state) {
    return false;
}

void Block::entityInside(Level* level, const BlockPos& pos, const BlockState* state,
                         const std::shared_ptr<Entity>&) {}

int Block::getDirectSignal(const BlockState* state, LevelSource* levelSource, const BlockPos& pos,
                           const Direction* direction) {
    return Block::sDefaultDirectSignal;
}

// Too lazy to figure out the Stats, CommonStats etc.
// void Block::playerDestroy(Level* level, std::shared_ptr<Player> player, const BlockPos& pos,
//                          const BlockState* state, std::shared_ptr<BlockEntity>, not_null_ptr<ItemInstance>)
//                          {}

bool Block::isSilkTouchable() {
    return this->defaultBlockState()->isCubeShaped() && !this->mSilkTouchable;
}

not_null_ptr<ItemInstance> Block::getSilkTouchItemInstance(const BlockState* state) {
    Item* item = Item::byBlock(this);
    int data = item->isStackedByData() ? this->convertBlockStateToLegacyData(state) : 0;
    return new ItemInstance(item, 1, data);
}

int Block::getResourceCountForLootBonus(int fortuneLevel, Random* random) {
    return this->getResourceCount(random);
}

void Block::setPlacedBy(Level* level, const BlockPos& pos, const BlockState* state,
                        std::shared_ptr<LivingEntity>, not_null_ptr<ItemInstance>) {}

Block* Block::setNameAndDescriptionId(int name, int desc) {
    this->mDescriptionId = name;
    this->mUseDescriptionId = desc;
    return this;
}

bool Block::isPossibleToRespawnInThis() {
    return !this->mMaterial->isSolid() && !this->mMaterial->isLiquid();
}

std::wstring Block::getName() {
    return L"";
}

unsigned int Block::getDescriptionId(int) {
    return this->mDescriptionId;
}

unsigned int Block::getUseDescriptionId() {
    return this->mUseDescriptionId;
}

bool Block::triggerEvent(const BlockState* state, Level* level, const BlockPos& pos, int, int) {
    return false;
}

bool Block::isCollectStatistics() {
    return this->mCollectStatistics;
}

bool Block::shouldBlockTick(Level* level, const BlockPos& pos, const BlockState* state) {
    return true;
}

Block* Block::setNotCollectStatistics() {
    this->mCollectStatistics = false;
    return this;
}

int Block::getPistonPushReaction(const BlockState* state) {
    return this->mMaterial->getPushReaction();
}

float Block::getShadeBrightness(const BlockState* state) {
    return state->isSolidBlockingCube() ? 0.2f : 1.0f;
}

void Block::fallOn(Level* level, const BlockPos& pos, std::shared_ptr<Entity> faller, float distance) {
    faller->causeFallDamage(distance, 1.0f);
}

void Block::updateEntityAfterFallOn(Level* level, std::shared_ptr<Entity> faller) {
    faller->mDeltaMovementY = 0.0f;
}

not_null_ptr<ItemInstance> Block::getCloneItemInstance(Level* level, const BlockPos& pos,
                                                       const BlockState* state) {
    return new ItemInstance(Item::byBlock(this), 1, this->getSpawnResourcesAuxValue(state));
}

void Block::playerWillDestroy(Level* level, const BlockPos& pos, const BlockState* state,
                              std::shared_ptr<Player> player) {}

void Block::handleRain(Level* level, const BlockPos& pos) {}

bool Block::canInstantlyTick() {
    return true;
}

bool Block::dropFromExplosion(Explosion*) {
    return true;
}

bool Block::isMatching(Block* other) {
    return this == other;
}

bool Block::hasAnalogOutputSignal(const BlockState* state) {
    return false;
}

int Block::getAnalogOutputSignal(const BlockState* state, Level* level, const BlockPos& pos) {
    return Block::sDefaultDirectSignal;
}

Block* Block::setIconName(const std::wstring& icon) {
    this->mIconName = icon;
    return this;
}

std::wstring Block::getIconName() {
    return this->mIconName.empty() ? L"MISSING_ICON_TILE_" + std::to_wstring(this->getId()) + L"_"
                                         + std::to_wstring(this->mDescriptionId) :
                                     this->mIconName;
}

void Block::registerIcons(IconRegister* iconReg) {
    this->mTexture = iconReg->registerIcon(this->getIconName());
}

std::wstring Block::getTileItemIconName() {
    return L"";
}

TextureAtlasSprite* Block::getIconTexture(const Direction* direction, const BlockState* state) {
    return this->getTexture(direction, state);
}

int xOffsets[6] = {1, -1, 0, 0, 0, 0};
int yOffsets[6] = {0, 0, 1, -1, 0, 0};
int zOffsets[6] = {0, 0, 0, 0, 1, -1};

// NON_MATCHING: too lazy to figure out this, wasLeaves is probably someshit generated by compiler and that's
// prob why it's not matching
TextureAtlasSprite* Block::getTexture(LevelSource* levelSource, const BlockPos& pos,
                                      const Direction* direction, const BlockState* state) {
    if (LeafBlock::isLeaves(state->getBlock()))
        return this->getTexture(direction, state);

    bool wasLeaves;
    for (int i = 0; i < 6; i++) {
        const BlockState* neighbourState
            = levelSource->getBlockState(pos.offset(xOffsets[i], yOffsets[i], zOffsets[i]));
        if (LeafBlock::isLeaves(neighbourState->getBlock())) {
            wasLeaves = true;
        } else {
            wasLeaves = neighbourState->isSolidRender();
            if (wasLeaves)
                break;
        }
    }
    if (!wasLeaves)
        return this->getTexture(direction, state);

    Blocks::LEAVES->setFancy(false);
    Blocks::LEAVES2->setFancy(false);
    Blocks::LEAVES->setFancy(true);
    Blocks::LEAVES2->setFancy(true);
    return this->getTexture(direction, state);
}

TextureAtlasSprite* Block::getTexture(const Direction* direction, const BlockState* state) {
    return this->mTexture;
}

TextureAtlasSprite* Block::getTexture(const Direction* direction) {
    return this->getTexture(direction, this->defaultBlockState());
}

const BlockState* Block::getInventoryRenderState(const BlockState* state) {
    return state;
}

BlockStateDefinition* Block::createBlockStateDefinition() {
    return new BlockStateDefinition(this);
}

BlockStateDefinition* Block::getBlockStateDefinition() {
    return this->mBlockStateDefinition;
}

int Block::getOffsetType() {
    return 0;
}

const Vec3* ZERO = new Vec3(0, 0, 0);

Vec3* Block::getOffset(const BlockState* state, LevelSource* levelSource, const BlockPos& pos) {
    int offsetType = this->getOffsetType();
    if (!offsetType)
        return Vec3::newTemp(ZERO);

    int64_t seed = Mth::getSeed(pos.getX(), 0, pos.getZ());
    return Vec3::newTemp((((seed >> 16 & 0xF) / 15.0f) - 0.5) * 0.5,
                         offsetType == 2 ? (((seed >> 20 & 0xF) / 15.0f) - 1.0) * 0.2 : 0,
                         (((seed >> 24 & 0xF) / 15.0f) - 0.5) * 0.5);
}

const SoundType* Block::getSoundType() {
    return this->mSoundType;
}

std::wstring Block::toString() {
    return L"Block{" + Blocks::Registry->getKey(this).toString() + L"}";
}

void Block::appendHoverText(not_null_ptr<ItemInstance>, std::shared_ptr<Player> player,
                            std::vector<HtmlString>*, bool) {}

bool Block::isLiquidBlock() {
    return false;
}

bool Block::isExceptionBlockForAttaching(Block* block) {
    if (dynamic_cast<ShulkerBoxBlock*>(block) || dynamic_cast<LeafBlock*>(block)
        || dynamic_cast<TrapDoorBlock*>(block))
        return true;

    return block == Blocks::CAULDRON;
}

bool Block::isExceptionBlockForAttachingPlusPiston(Block* block) {
    return Block::isExceptionBlockForAttaching(block);
}

// NON_MATCHING | Score: 1479270 (lower is better)
// This is the second-largest method in the entire executable
// It might be easier than it would seem, since most of it is just block registry
// but the main issue is that IDA does not give a clean enough decomp since every chained method creates a
// new lvar... To be able to see vftable calls, you have to set that lvar's type to Block *... for every
// single one (there's about 2000 lvars)
void Block::staticCtor() {
    DirectionalBlock::blockStaticCtor();
    HorizontalDirectionalBlock::blockStaticCtor();
    AnvilBlock::blockStaticCtor();
    BannerBlock::blockStaticCtor();
    BedBlock::blockStaticCtor();
    ButtonBlock::blockStaticCtor();
    ChestBlock::blockStaticCtor();
    ColoredBlock::blockStaticCtor();
    ComparatorBlock::blockStaticCtor();
    DetectorRailBlock::blockStaticCtor();
    DirtBlock::blockStaticCtor();
    DispenserBlock::blockStaticCtor();
    DoorBlock::blockStaticCtor();
    DoublePlantBlock::blockStaticCtor();
    EnderChestBlock::blockStaticCtor();
    EndPortalFrameBlock::blockStaticCtor();
    FlowerPotBlock::blockStaticCtor();
    FurnaceBlock::blockStaticCtor();
    HalfSlabBlock::blockStaticCtor();
    HopperBlock::blockStaticCtor();
    HugeMushroomBlock::blockStaticCtor();
    LadderBlock::blockStaticCtor();
    LeverBlock::blockStaticCtor();
    LogBlock::blockStaticCtor();
    MonsterEggBlock::blockStaticCtor();
    PistonBaseBlock::blockStaticCtor();
    PistonHeadBlock::blockStaticCtor();
    PistonMagicBlock::blockStaticCtor();
    PlanksBlock::blockStaticCtor();
    NewLeafBlock::blockStaticCtor();
    NewLogBlock::blockStaticCtor();
    SandBlock::blockStaticCtor();
    NewStoneSlabBlock::blockStaticCtor();
    OldLeafBlock::blockStaticCtor();
    OldLogBlock::blockStaticCtor();
    PortalBlock::blockStaticCtor();
    PoweredRailBlock::blockStaticCtor();
    PrismarineBlock::blockStaticCtor();
    QuartzBlock::blockStaticCtor();
    RailBlock::blockStaticCtor();
    RedSandStoneBlock::blockStaticCtor();
    RedStoneWireBlock::blockStaticCtor();
    RotatedPillarBlock::blockStaticCtor();
    SandStoneBlock::blockStaticCtor();
    SaplingBlock::blockStaticCtor();
    SkullBlock::blockStaticCtor();
    StainedGlassBlock::blockStaticCtor();
    StainedGlassPaneBlock::blockStaticCtor();
    StairBlock::blockStaticCtor();
    StoneBlock::blockStaticCtor();
    StoneBrickBlock::blockStaticCtor();
    StoneSlabBlock::blockStaticCtor();
    TallGrassBlock::blockStaticCtor();
    TorchBlock::blockStaticCtor();
    StemBlock::blockStaticCtor();
    TrapDoorBlock::blockStaticCtor();
    TripWireHookBlock::blockStaticCtor();
    WallBlock::blockStaticCtor();
    WallSignBlock::blockStaticCtor();
    WoodSlabBlock::blockStaticCtor();
    WoolCarpetBlock::blockStaticCtor();
    PurpurSlabBlock::blockStaticCtor();
    NoteBlock::blockStaticCtor();
    ConcretePowderBlock::blockStaticCtor();
    StainedHardenedClayBlock::staticCtor();

    Block* airBlock = (new AirBlock())->setNameAndDescriptionId(0xFFFFFFFF, 0xFFFFFFFF);
    registerBlock(0, *Blocks::AIR_RSRC, airBlock);

    Block* stoneBlock = (new StoneBlock())
                            ->setDestroyTime(1.5)
                            ->setExplodeable(10.0)
                            ->setSoundType(SoundType::STONE)
                            ->setIconName(L"stone")
                            ->setNameAndDescriptionId(StringIDs::Stone,
                                                      StringIDs::CanBeMinedWithAPickaxeToCollectCobblestone);

    stoneBlock->setBaseItemTypeAndMaterial(14, 2);
    registerBlock(1, L"stone", stoneBlock);
}
