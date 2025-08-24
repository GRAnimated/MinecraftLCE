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
#include "net/minecraft/world/level/block/BarrierBlock.h"
#include "net/minecraft/world/level/block/BeaconBlock.h"
#include "net/minecraft/world/level/block/BedBlock.h"
#include "net/minecraft/world/level/block/BeetrootBlock.h"
#include "net/minecraft/world/level/block/BlockImpl.h"
#include "net/minecraft/world/level/block/BlockShapes.h"
#include "net/minecraft/world/level/block/BlockTooltipDataHolder.h"
#include "net/minecraft/world/level/block/Blocks.h"
#include "net/minecraft/world/level/block/BoneBlock.h"
#include "net/minecraft/world/level/block/BookshelfBlock.h"
#include "net/minecraft/world/level/block/BrewingStandBlock.h"
#include "net/minecraft/world/level/block/ButtonBlock.h"
#include "net/minecraft/world/level/block/CactusBlock.h"
#include "net/minecraft/world/level/block/CakeBlock.h"
#include "net/minecraft/world/level/block/CarrotBlock.h"
#include "net/minecraft/world/level/block/CauldronBlock.h"
#include "net/minecraft/world/level/block/ChestBlock.h"
#include "net/minecraft/world/level/block/ChorusFlowerBlock.h"
#include "net/minecraft/world/level/block/ChorusPlantBlock.h"
#include "net/minecraft/world/level/block/ClayBlock.h"
#include "net/minecraft/world/level/block/CocoaBlock.h"
#include "net/minecraft/world/level/block/ColoredBlock.h"
#include "net/minecraft/world/level/block/ComparatorBlock.h"
#include "net/minecraft/world/level/block/ConcretePowderBlock.h"
#include "net/minecraft/world/level/block/CraftingTableBlock.h"
#include "net/minecraft/world/level/block/CropBlock.h"
#include "net/minecraft/world/level/block/DaylightDetectorBlock.h"
#include "net/minecraft/world/level/block/DeadBushBlock.h"
#include "net/minecraft/world/level/block/DetectorRailBlock.h"
#include "net/minecraft/world/level/block/DirectionalBlock.h"
#include "net/minecraft/world/level/block/DirtBlock.h"
#include "net/minecraft/world/level/block/DispenserBlock.h"
#include "net/minecraft/world/level/block/DoorBlock.h"
#include "net/minecraft/world/level/block/DoublePlantBlock.h"
#include "net/minecraft/world/level/block/DragonEggBlock.h"
#include "net/minecraft/world/level/block/DropperBlock.h"
#include "net/minecraft/world/level/block/DynamicLiquidBlock.h"
#include "net/minecraft/world/level/block/EnchantmentTableBlock.h"
#include "net/minecraft/world/level/block/EndGatewayBlock.h"
#include "net/minecraft/world/level/block/EndPortalBlock.h"
#include "net/minecraft/world/level/block/EndPortalFrameBlock.h"
#include "net/minecraft/world/level/block/EndRodBlock.h"
#include "net/minecraft/world/level/block/EnderChestBlock.h"
#include "net/minecraft/world/level/block/FarmBlock.h"
#include "net/minecraft/world/level/block/FenceBlock.h"
#include "net/minecraft/world/level/block/FenceGateBlock.h"
#include "net/minecraft/world/level/block/FireBlock.h"
#include "net/minecraft/world/level/block/FlowerPotBlock.h"
#include "net/minecraft/world/level/block/FrostedIceBlock.h"
#include "net/minecraft/world/level/block/FullNewStoneSlabBlock.h"
#include "net/minecraft/world/level/block/FullStoneSlabBlock.h"
#include "net/minecraft/world/level/block/FullWoodSlabBlock.h"
#include "net/minecraft/world/level/block/FurnaceBlock.h"
#include "net/minecraft/world/level/block/GlassBlock.h"
#include "net/minecraft/world/level/block/GlazedTerracottaBlock.h"
#include "net/minecraft/world/level/block/GlowstoneBlock.h"
#include "net/minecraft/world/level/block/GrassBlock.h"
#include "net/minecraft/world/level/block/GrassPathBlock.h"
#include "net/minecraft/world/level/block/GravelBlock.h"
#include "net/minecraft/world/level/block/HalfNewStoneSlabBlock.h"
#include "net/minecraft/world/level/block/HalfSlabBlock.h"
#include "net/minecraft/world/level/block/HalfStoneSlabBlock.h"
#include "net/minecraft/world/level/block/HalfWoodSlabBlock.h"
#include "net/minecraft/world/level/block/HardenedClayBlock.h"
#include "net/minecraft/world/level/block/HayBlock.h"
#include "net/minecraft/world/level/block/HopperBlock.h"
#include "net/minecraft/world/level/block/HorizontalDirectionalBlock.h"
#include "net/minecraft/world/level/block/HugeMushroomBlock.h"
#include "net/minecraft/world/level/block/IceBlock.h"
#include "net/minecraft/world/level/block/JukeboxBlock.h"
#include "net/minecraft/world/level/block/LadderBlock.h"
#include "net/minecraft/world/level/block/LeafBlock.h"
#include "net/minecraft/world/level/block/LeverBlock.h"
#include "net/minecraft/world/level/block/LogBlock.h"
#include "net/minecraft/world/level/block/MagmaBlock.h"
#include "net/minecraft/world/level/block/MelonBlock.h"
#include "net/minecraft/world/level/block/MobSpawnerBlock.h"
#include "net/minecraft/world/level/block/MonsterEggBlock.h"
#include "net/minecraft/world/level/block/MushroomBlock.h"
#include "net/minecraft/world/level/block/MyceliumBlock.h"
#include "net/minecraft/world/level/block/NetherBrickBlock.h"
#include "net/minecraft/world/level/block/NetherWartBlock.h"
#include "net/minecraft/world/level/block/NetherrackBlock.h"
#include "net/minecraft/world/level/block/NewLeafBlock.h"
#include "net/minecraft/world/level/block/NewLogBlock.h"
#include "net/minecraft/world/level/block/NewStoneSlabBlock.h"
#include "net/minecraft/world/level/block/NoteBlock.h"
#include "net/minecraft/world/level/block/ObserverBlock.h"
#include "net/minecraft/world/level/block/ObsidianBlock.h"
#include "net/minecraft/world/level/block/OldLeafBlock.h"
#include "net/minecraft/world/level/block/OldLogBlock.h"
#include "net/minecraft/world/level/block/OreBlock.h"
#include "net/minecraft/world/level/block/PackedIceBlock.h"
#include "net/minecraft/world/level/block/PistonBaseBlock.h"
#include "net/minecraft/world/level/block/PistonHeadBlock.h"
#include "net/minecraft/world/level/block/PistonMagicBlock.h"
#include "net/minecraft/world/level/block/PlanksBlock.h"
#include "net/minecraft/world/level/block/PortalBlock.h"
#include "net/minecraft/world/level/block/PotatoBlock.h"
#include "net/minecraft/world/level/block/PoweredBlock.h"
#include "net/minecraft/world/level/block/PoweredRailBlock.h"
#include "net/minecraft/world/level/block/PressurePlateBlock.h"
#include "net/minecraft/world/level/block/PrismarineBlock.h"
#include "net/minecraft/world/level/block/PumpkinBlock.h"
#include "net/minecraft/world/level/block/PurpurSlabBlock.h"
#include "net/minecraft/world/level/block/PurpurSlabBlockFull.h"
#include "net/minecraft/world/level/block/PurpurSlabBlockHalf.h"
#include "net/minecraft/world/level/block/QuartzBlock.h"
#include "net/minecraft/world/level/block/RailBlock.h"
#include "net/minecraft/world/level/block/RedFlowerBlock.h"
#include "net/minecraft/world/level/block/RedSandStoneBlock.h"
#include "net/minecraft/world/level/block/RedStoneOreBlock.h"
#include "net/minecraft/world/level/block/RedStoneWireBlock.h"
#include "net/minecraft/world/level/block/RedstoneLampBlock.h"
#include "net/minecraft/world/level/block/RedstoneTorchBlock.h"
#include "net/minecraft/world/level/block/ReedsBlock.h"
#include "net/minecraft/world/level/block/RepeaterBlock.h"
#include "net/minecraft/world/level/block/RotatedPillarBlock.h"
#include "net/minecraft/world/level/block/RotatedPillarBlockImpl.h"
#include "net/minecraft/world/level/block/SandBlock.h"
#include "net/minecraft/world/level/block/SandStoneBlock.h"
#include "net/minecraft/world/level/block/SaplingBlock.h"
#include "net/minecraft/world/level/block/SeaLanternBlock.h"
#include "net/minecraft/world/level/block/ShulkerBoxBlock.h"
#include "net/minecraft/world/level/block/SkullBlock.h"
#include "net/minecraft/world/level/block/SlimeBlock.h"
#include "net/minecraft/world/level/block/SnowBlock.h"
#include "net/minecraft/world/level/block/SnowLayerBlock.h"
#include "net/minecraft/world/level/block/SoulSandBlock.h"
#include "net/minecraft/world/level/block/SoundType.h"
#include "net/minecraft/world/level/block/SpongeBlock.h"
#include "net/minecraft/world/level/block/StainedGlassBlock.h"
#include "net/minecraft/world/level/block/StainedGlassPaneBlock.h"
#include "net/minecraft/world/level/block/StainedHardenedClayBlock.h"
#include "net/minecraft/world/level/block/StairBlock.h"
#include "net/minecraft/world/level/block/StandingBannerBlock.h"
#include "net/minecraft/world/level/block/StandingSignBlock.h"
#include "net/minecraft/world/level/block/StaticLiquidBlock.h"
#include "net/minecraft/world/level/block/StemBlock.h"
#include "net/minecraft/world/level/block/StoneBlock.h"
#include "net/minecraft/world/level/block/StoneBrickBlock.h"
#include "net/minecraft/world/level/block/StoneButtonBlock.h"
#include "net/minecraft/world/level/block/StoneSlabBlock.h"
#include "net/minecraft/world/level/block/StructureBlock.h"
#include "net/minecraft/world/level/block/StructureVoidBlock.h"
#include "net/minecraft/world/level/block/TallGrassBlock.h"
#include "net/minecraft/world/level/block/ThinFenceBlock.h"
#include "net/minecraft/world/level/block/TntBlock.h"
#include "net/minecraft/world/level/block/TorchBlock.h"
#include "net/minecraft/world/level/block/TrapDoorBlock.h"
#include "net/minecraft/world/level/block/TripWireBlock.h"
#include "net/minecraft/world/level/block/TripWireHookBlock.h"
#include "net/minecraft/world/level/block/VineBlock.h"
#include "net/minecraft/world/level/block/WallBannerBlock.h"
#include "net/minecraft/world/level/block/WallBlock.h"
#include "net/minecraft/world/level/block/WallSignBlock.h"
#include "net/minecraft/world/level/block/WaterlilyBlock.h"
#include "net/minecraft/world/level/block/WebBlock.h"
#include "net/minecraft/world/level/block/WeightedPressurePlateBlock.h"
#include "net/minecraft/world/level/block/WoodButtonBlock.h"
#include "net/minecraft/world/level/block/WoodSlabBlock.h"
#include "net/minecraft/world/level/block/WoolCarpetBlock.h"
#include "net/minecraft/world/level/block/YellowFlowerBlock.h"
#include "net/minecraft/world/level/block/state/BlockState.h"
#include "net/minecraft/world/level/block/state/BlockStateDefinition.h"
#include "net/minecraft/world/level/dimension/Dimension.h"
#include "net/minecraft/world/level/gamemode/GameMode.h"
#include "net/minecraft/world/level/material/Material.h"
#include "net/minecraft/world/phys/AABB.h"
#include "net/minecraft/world/phys/HitResult.h"

#include <cfloat>
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

Block* Block::sendBlockData(uchar sendBlockData) {
    this->mSendBlockData = sendBlockData;
    return this;
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
    this->setDestroyTime(FLT_MAX);
    return this;
}

bool Block::isIndestructible() {
    return this->mDestroyTime == FLT_MAX;
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

// NON_MATCHING | Score: 385975 (lower is better)
// This is the second-largest method in the entire executable
// I (Dexrn) automated the block registry code, but I'm not sure how well it worked
// Also, there's stuff missing at both the header and the footer... so it won't match until that's done.
// Additionally, it seems that setBaseItemTypeAndMaterial is sometimes called outside of the chain...
// e.g:
// Block *someBlock = new SomeBlock()
//                      ->setDestroyTime(0)
//                      ->setExplodeable(10.0);
// someBlock->setBaseItemTypeAndMaterial(14, 2);
// Block::registerBlock(1, L"some_block", someBlock);
//
// The size given in the comments above every block was from the `operator new` call to allocate space for the
// block This gives us the class size of every block that is registered.
void Block::staticCtor() {
    // some stuff happens up here btw
    // I think it sets some static DirectionProperty vars

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
    Block::registerBlock(0, *Blocks::AIR_RSRC, airBlock);

    // Size: 0xA8u
    Block* stoneBlock = (new StoneBlock())
                            ->setDestroyTime(1.5)
                            ->setExplodeable(10.0)
                            ->setSoundType(SoundType::STONE)
                            ->setIconName(L"stone")
                            ->setNameAndDescriptionId(StringIDs::Stone,
                                                      StringIDs::CanBeMinedWithAPickaxeToCollectCobblestone)
                            ->setBaseItemTypeAndMaterial(14, 2);
    Block::registerBlock(1, L"stone", stoneBlock);

    // Size: 0xC8u
    Block* grassBlock
        = (new GrassBlock())
              ->setDestroyTime(0.6)
              ->setSoundType(SoundType::GRASS)
              ->setIconName(L"grass")
              ->setNameAndDescriptionId(StringIDs::GrassBlock, StringIDs::ABlockOfDirtWithGrassGrowingOn)
              ->setBaseItemTypeAndMaterial(13, 58);
    Block::registerBlock(2, L"grass", grassBlock);

    // Size: 0xA8u
    Block* dirtBlock
        = (new DirtBlock())
              ->setDestroyTime(0.5)
              ->setSoundType(SoundType::DIRT)
              ->setIconName(L"dirt")
              ->setNameAndDescriptionId(StringIDs::Dirt, StringIDs::CollectedUsingAShovelCanBeUsedFor)
              ->setBaseItemTypeAndMaterial(13, 58);
    Block::registerBlock(3, L"dirt", dirtBlock);

    Block* cobblestoneBlock
        = (new BlockImpl(Material::STONE))
              ->setDestroyTime(2.0)
              ->setExplodeable(10.0)
              ->setSoundType(SoundType::STONE)
              ->setIconName(L"cobblestone")
              ->setNameAndDescriptionId(StringIDs::Cobblestone, StringIDs::MinedFromStoneUsingAPickaxeCanBe)
              ->setBaseItemTypeAndMaterial(14, 2);
    Block::registerBlock(4, L"cobblestone", cobblestoneBlock);

    Block* planksBlock
        = (new PlanksBlock())
              ->setIconName(L"planks")
              ->setDestroyTime(2.0)
              ->setExplodeable(5.0)
              ->setSoundType(SoundType::WOOD)
              ->sendBlockData(15)
              ->setNameAndDescriptionId(StringIDs::OakPlanks, StringIDs::UsedAsABuildingMaterialAndCanBe)
              ->setBaseItemTypeAndMaterial(50, 1);

    Block::registerBlock(5, L"planks", planksBlock);
    Block* saplingBlock
        = (new SaplingBlock())
              ->setDestroyTime(0.0)
              ->setSoundType(SoundType::GRASS)
              ->setIconName(L"sapling")
              ->sendBlockData(15)
              ->setNameAndDescriptionId(StringIDs::Sapling, StringIDs::CanBePlantedAndWillEventuallyGrowInto)
              ->disableMipmap();

    Block::registerBlock(6, L"sapling", saplingBlock);

    Block* bedrockBlock = (new BlockImpl(Material::STONE))
                              ->setIndestructible()
                              ->setExplodeable(6000000.0)
                              ->setSoundType(SoundType::STONE)
                              ->setIconName(L"bedrock")
                              ->setNotCollectStatistics()
                              ->setNameAndDescriptionId(StringIDs::Bedrock, 0xab4b374);
    Block::registerBlock(7, L"bedrock", bedrockBlock);

    // Size: 0xF0u
    Block* flowingWaterBlock
        = (new DynamicLiquidBlock(Material::WATER))
              ->setDestroyTime(100.0)
              ->setLightBlock(3)
              ->setIconName(L"water_flow")
              ->setNotCollectStatistics()
              ->sendBlockData(15)
              ->setNameAndDescriptionId(StringIDs::Water, StringIDs::ExtinguishesFireAndHelpsCropsGrowCanBe);
    Block::registerBlock(8, L"flowing_water", flowingWaterBlock);

    // Size: 0xB8u
    Block* waterBlock
        = (new StaticLiquidBlock(Material::WATER))
              ->setDestroyTime(100.0)
              ->setLightBlock(3)
              ->setIconName(L"water_still")
              ->setNotCollectStatistics()
              ->sendBlockData(15)
              ->setNameAndDescriptionId(StringIDs::Water, StringIDs::ExtinguishesFireAndHelpsCropsGrowCanBe);
    Block::registerBlock(9, L"water", waterBlock);

    // Size: 0xF0u
    Block* flowingLavaBlock
        = (new DynamicLiquidBlock(Material::LAVA))
              ->setDestroyTime(100.0)
              ->setLightEmission(1.0)
              ->setIconName(L"lava_flow")
              ->setLightBlock(14)
              ->setNotCollectStatistics()
              ->sendBlockData(15)
              ->setNameAndDescriptionId(StringIDs::Lava, StringIDs::SetsFireToAnythingThatTouchesItCan);
    Block::registerBlock(10, L"flowing_lava", flowingLavaBlock);

    // Size: 0xB8u
    Block* lavaBlock
        = (new StaticLiquidBlock(Material::LAVA))
              ->setDestroyTime(100.0)
              ->setLightEmission(1.0)
              ->setIconName(L"lava_still")
              ->setLightBlock(14)
              ->setNotCollectStatistics()
              ->sendBlockData(15)
              ->setNameAndDescriptionId(StringIDs::Lava, StringIDs::SetsFireToAnythingThatTouchesItCan);
    Block::registerBlock(11, L"lava", lavaBlock);

    // Size: 0xB8u
    Block* sandBlock
        = (new SandBlock())
              ->setDestroyTime(0.5)
              ->setSoundType(SoundType::SAND)
              ->setIconName(L"sand")
              ->setNameAndDescriptionId(StringIDs::Sand, StringIDs::CollectedUsingAShovelCanBeSmeltedInto)
              ->setBaseItemTypeAndMaterial(13, 13);
    Block::registerBlock(12, L"sand", sandBlock);

    // Size: 0xA8u
    Block* gravelBlock
        = (new GravelBlock())
              ->setDestroyTime(0.6)
              ->setSoundType(SoundType::DIRT)
              ->setIconName(L"gravel")
              ->setNameAndDescriptionId(StringIDs::Gravel,
                                        StringIDs::CollectedUsingAShovelSometimesProducesFlintWhen);
    Block::registerBlock(13, L"gravel", gravelBlock);

    // Size: 0xA8u
    Block* goldOreBlock
        = (new OreBlock())
              ->setDestroyTime(3.0)
              ->setExplodeable(5.0)
              ->setSoundType(SoundType::STONE)
              ->setIconName(L"gold_ore")
              ->setNameAndDescriptionId(0x53aa5c8, StringIDs::CanBeMinedWithAnIronPickaxeOrIronNSmeltedInA);
    Block::registerBlock(14, L"gold_ore", goldOreBlock);

    // Size: 0xA8u
    Block* ironOreBlock
        = (new OreBlock())
              ->setDestroyTime(3.0)
              ->setExplodeable(5.0)
              ->setSoundType(SoundType::STONE)
              ->setIconName(L"iron_ore")
              ->setNameAndDescriptionId(StringIDs::IronOre, StringIDs::CanBeMinedWithAStonePickaxeOr);
    Block::registerBlock(15, L"iron_ore", ironOreBlock);

    // Size: 0xA8u
    Block* coalOreBlock
        = (new OreBlock())
              ->setDestroyTime(3.0)
              ->setExplodeable(5.0)
              ->setSoundType(SoundType::STONE)
              ->setIconName(L"coal_ore")
              ->setNameAndDescriptionId(StringIDs::CoalOre, StringIDs::CanBeMinedWithAPickaxeToCollectCoal);
    Block::registerBlock(16, L"coal_ore", coalOreBlock);

    // Size: 0x110u
    Block* oldLogBlock
        = (new OldLogBlock())
              ->setIconName(L"log")
              ->sendBlockData(15)
              ->setNameAndDescriptionId(StringIDs::Wood, StringIDs::ChoppedUsingAnAxeAndCanBeCrafted);
    Block::registerBlock(17, L"log", oldLogBlock);

    // Size: 0x110u
    Block* oldLeafBlock = (new OldLeafBlock())
                              ->setIconName(L"leaves")
                              ->sendBlockData(3)
                              ->setNameAndDescriptionId(StringIDs::Leaves,
                                                        StringIDs::WhenBrokenSometimesDropsASaplingWhichCan);
    Block::registerBlock(18, L"leaves", oldLeafBlock);

    // Size: 0xB0u
    Block* spongeBlock
        = (new SpongeBlock())
              ->setDestroyTime(0.6)
              ->setSoundType(SoundType::GRASS)
              ->setIconName(L"sponge")
              ->setNameAndDescriptionId(StringIDs::Sponge, StringIDs::CanAbsorbWaterNearbyTurningIntoAWet);
    Block::registerBlock(19, L"sponge", spongeBlock);

    // Size: 0xC0u
    Block* glassBlock
        = (new GlassBlock(Material::GLASS, false))
              ->setDestroyTime(0.3)
              ->setSoundType(SoundType::GLASS)
              ->setIconName(L"glass")
              ->setNameAndDescriptionId(StringIDs::Glass, StringIDs::CreatedInAFurnaceBySmeltingSandCan)
              ->setBaseItemTypeAndMaterial(42, 34);
    Block::registerBlock(20, L"glass", glassBlock);

    // Size: 0xA8u
    Block* lapisOreBlock
        = (new OreBlock())
              ->setDestroyTime(3.0)
              ->setExplodeable(5.0)
              ->setSoundType(SoundType::STONE)
              ->setIconName(L"lapis_ore")
              ->setNameAndDescriptionId(StringIDs::LapisLazuliOre,
                                        StringIDs::CanBeMinedWithAStonePickaxeOrCollectLapisLazuli);
    Block::registerBlock(21, L"lapis_ore", lapisOreBlock);

    // Size: 0xA8u
    Block* lapisBlock = (new BlockImpl(Material::METAL))
                            ->setDestroyTime(3.0)
                            ->setExplodeable(5.0)
                            ->setSoundType(SoundType::STONE)
                            ->setIconName(L"lapis_block")
                            ->setNameAndDescriptionId(StringIDs::LapisLazuliBlock,
                                                      StringIDs::ACompactWayOfStoringLapisLazuli)
                            ->setBaseItemTypeAndMaterial(32, 10);
    Block::registerBlock(22, L"lapis_block", lapisBlock);

    // Size: 0xE0u
    Block* dispenserBlock
        = (new DispenserBlock())
              ->setDestroyTime(3.5)
              ->setSoundType(SoundType::STONE)
              ->setIconName(L"dispenser")
              ->sendBlockData(15)
              ->setNameAndDescriptionId(StringIDs::Dispenser_2, StringIDs::UsedToHoldAndShootOutItemsIn)
              ->setBaseItemTypeAndMaterial(51, 2);
    Block::registerBlock(23, L"dispenser", dispenserBlock);

    // Size: 0xD0u
    Block* sandStoneBlock = (new SandStoneBlock())
                                ->setSoundType(SoundType::STONE)
                                ->setIconName(L"sandstone")
                                ->setDestroyTime(0.8)
                                ->sendBlockData(15)
                                ->sendBlockData(15)
                                ->setNameAndDescriptionId(StringIDs::Sandstone,
                                                          StringIDs::UsedAsABuildingMaterialIsNotInfluenced)
                                ->setBaseItemTypeAndMaterial(13, 13);
    Block::registerBlock(24, L"sandstone", sandStoneBlock);

    // Size: 0xB0u
    Block* noteBlock = (new NoteBlock())
                           ->setSoundType(SoundType::WOOD)
                           ->setDestroyTime(0.8)
                           ->setIconName(L"noteblock")
                           ->sendBlockData(15)
                           ->setBaseItemTypeAndMaterial(56, 0)
                           ->setNameAndDescriptionId(StringIDs::NoteBlock, 0xef9d20b);
    Block::registerBlock(25, L"noteblock", noteBlock);

    // Size: 0xE0u
    Block* bedBlock
        = (new BedBlock())
              ->setSoundType(SoundType::WOOD)
              ->setDestroyTime(0.2)
              ->setIconName(L"bed")
              ->setNotCollectStatistics()
              ->sendBlockData(15)
              ->setNameAndDescriptionId(StringIDs::Bed_1, StringIDs::UsedToForwardTimeFromAnyTimeAt);
    Block::registerBlock(26, L"bed", bedBlock);

    // Size: 0xB0u
    Block* poweredRailBlock
        = (new PoweredRailBlock())
              ->setDestroyTime(0.7)
              ->setSoundType(SoundType::METAL)
              ->setIconName(L"rail_golden")
              ->sendBlockData(15)
              ->setNameAndDescriptionId(StringIDs::PoweredRail,
                                        StringIDs::WhenPoweredAcceleratesMinecartsThatPassOverIt)
              ->setBaseItemTypeAndMaterial(12, 9)
              ->disableMipmap();
    Block::registerBlock(27, L"golden_rail", poweredRailBlock);

    // Size: 0xB8u
    Block* detectorRailBlock
        = (new DetectorRailBlock())
              ->setDestroyTime(0.7)
              ->setSoundType(SoundType::METAL)
              ->setIconName(L"rail_detector")
              ->sendBlockData(15)
              ->setNameAndDescriptionId(StringIDs::DetectorRail,
                                        StringIDs::FunctionsLikeAPressurePlateSendsARedstone)
              ->disableMipmap()
              ->setBaseItemTypeAndMaterial(12, 8);
    Block::registerBlock(28, L"detector_rail", detectorRailBlock);

    // Size: 0xC0u
    Block* stickyPistonBaseBlock
        = (new PistonBaseBlock(true))
              ->sendBlockData(15)
              ->setNameAndDescriptionId(
                  StringIDs::StickyPiston,
                  StringIDs::WhenPoweredUsingAButtonALeverARetractsPullsBackBlockTouching)
              ->setBaseItemTypeAndMaterial(27, 28)
              ->setIconName(L"pistonStickyBase");
    Block::registerBlock(29, L"sticky_piston", stickyPistonBaseBlock);

    // Size: 0xA8u
    Block* webBlock
        = (new WebBlock())
              ->setLightBlock(1)
              ->setDestroyTime(4.0)
              ->setIconName(L"web")
              ->setNameAndDescriptionId(StringIDs::Cobweb, StringIDs::SlowsMovementWhenWalkingThroughItCanBe)
              ->disableMipmap();
    Block::registerBlock(30, L"web", webBlock);

    // Size: 0xC8u
    Block* tallGrassBlock = (new TallGrassBlock())
                                ->setDestroyTime(0.0)
                                ->setSoundType(SoundType::GRASS)
                                ->setIconName(L"tallgrass")
                                ->setNameAndDescriptionId(StringIDs::TallGrass,
                                                          StringIDs::SometimesProducesWheatSeedsWhenBroken)
                                ->disableMipmap();
    Block::registerBlock(31, L"tallgrass", tallGrassBlock);

    // Size: 0xA8u
    Block* deadBushBlock
        = (new DeadBushBlock())
              ->setDestroyTime(0.0)
              ->setSoundType(SoundType::GRASS)
              ->setIconName(L"deadbush")
              ->setNameAndDescriptionId(StringIDs::DeadBush, StringIDs::CanBeUsedAsDecoration)
              ->disableMipmap();
    Block::registerBlock(32, L"deadbush", deadBushBlock);

    // Size: 0xC0u
    Block* pistonBaseBlock
        = (new PistonBaseBlock(false))
              ->sendBlockData(15)
              ->setNameAndDescriptionId(StringIDs::Piston, StringIDs::WhenPoweredUsingAButtonALeverA)
              ->setBaseItemTypeAndMaterial(27, 28)
              ->setIconName(L"pistonBase");
    Block::registerBlock(33, L"piston", pistonBaseBlock);

    // Size: 0xB0u
    Block* pistonHeadBlock
        = (new PistonHeadBlock())
              ->setNameAndDescriptionId(StringIDs::Piston, StringIDs::WhenPoweredUsingAButtonALeverA)
              ->sendBlockData(15);
    Block::registerBlock(34, L"piston_head", pistonHeadBlock);

    // Size: 0x128u
    Block* woolBlock = (new ColoredBlock(Material::WOOL))
                           ->setDestroyTime(0.8)
                           ->setSoundType(SoundType::WOOL)
                           ->setIconName(L"wool_colored")
                           ->sendBlockData(15)
                           ->setNameAndDescriptionId(StringIDs::Wool, 0x9c006f1)
                           ->setBaseItemTypeAndMaterial(49, 55);
    Block::registerBlock(35, L"wool", woolBlock);

    // Size: 0xB0u
    Block* pistonMagicBlock = (new PistonMagicBlock())
                                  ->setIconName(L"pistonBase")
                                  ->setNameAndDescriptionId(StringIDs::Piston, 0xFFFFFFFF);
    Block::registerBlock(36, L"piston_extension", pistonMagicBlock);

    // Size: 0xB8u
    Block* yellowFlowerBlock
        = (new YellowFlowerBlock())
              ->setDestroyTime(0.0)
              ->setSoundType(SoundType::GRASS)
              ->setIconName(L"flower_dandelion")
              ->setNameAndDescriptionId(StringIDs::Flower, StringIDs::CanBeCraftedIntoADye)
              ->disableMipmap();
    Block::registerBlock(37, L"yellow_flower", yellowFlowerBlock);

    // Size: 0xB8u
    Block* redFlowerBlock = (new RedFlowerBlock())
                                ->setDestroyTime(0.0)
                                ->setSoundType(SoundType::GRASS)
                                ->setIconName(L"flower_rose")
                                ->setNameAndDescriptionId(StringIDs::Poppy, StringIDs::CanBeCraftedIntoADye)
                                ->disableMipmap();
    Block::registerBlock(38, L"red_flower", redFlowerBlock);

    // Size: 0xB0u
    Block* brownMushroomBlock
        = (new MushroomBlock())
              ->setDestroyTime(0.0)
              ->setSoundType(SoundType::GRASS)
              ->setLightEmission(0.125)
              ->setIconName(L"mushroom_brown")
              ->setNameAndDescriptionId(0xb7adaeb, StringIDs::CanBeCraftedWithABowlToMakeStew)
              ->disableMipmap();
    Block::registerBlock(39, L"brown_mushroom", brownMushroomBlock);

    // Size: 0xB0u
    Block* redMushroomBlock
        = (new MushroomBlock())
              ->setDestroyTime(0.0)
              ->setSoundType(SoundType::GRASS)
              ->setIconName(L"mushroom_red")
              ->setNameAndDescriptionId(0xb7adaeb, StringIDs::CanBeCraftedWithABowlToMakeStew)
              ->disableMipmap();
    Block::registerBlock(40, L"red_mushroom", redMushroomBlock);

    // Size: 0xA8u
    Block* goldBlock
        = (new BlockImpl(Material::METAL, MaterialColor::GOLD))
              ->setDestroyTime(3.0)
              ->setExplodeable(10.0)
              ->setSoundType(SoundType::METAL)
              ->setIconName(L"gold_block")
              ->setNameAndDescriptionId(StringIDs::BlockOfGold, StringIDs::ACompactWayOfStoringGold)
              ->setBaseItemTypeAndMaterial(32, 4);
    Block::registerBlock(41, L"gold_block", goldBlock);

    // Size: 0xA8u
    Block* ironBlock
        = (new BlockImpl(Material::METAL, MaterialColor::METAL))
              ->setDestroyTime(5.0)
              ->setExplodeable(10.0)
              ->setSoundType(SoundType::METAL)
              ->setIconName(L"iron_block")
              ->setNameAndDescriptionId(StringIDs::BlockOfIron, StringIDs::ACompactWayOfStoringIron)
              ->setBaseItemTypeAndMaterial(32, 3);
    Block::registerBlock(42, L"iron_block", ironBlock);

    // Size: 0xB0u
    Block* fullStoneSlabBlock
        = (new FullStoneSlabBlock())
              ->setDestroyTime(2.0)
              ->setExplodeable(10.0)
              ->setSoundType(SoundType::STONE)
              ->setIconName(L"stoneSlab")
              ->setNameAndDescriptionId(StringIDs::StoneSlab,
                                        StringIDs::UsedForMakingLongStaircasesTwoSlabsPlaced_2)
              ->setBaseItemTypeAndMaterial(21, 2);
    Block::registerBlock(43, L"double_stone_slab", fullStoneSlabBlock);

    // Size: 0xB0u
    Block* halfStoneSlabBlock
        = (new HalfStoneSlabBlock())
              ->setDestroyTime(2.0)
              ->setExplodeable(10.0)
              ->setSoundType(SoundType::STONE)
              ->setIconName(L"stoneSlab")
              ->setNameAndDescriptionId(StringIDs::StoneSlab,
                                        StringIDs::UsedForMakingLongStaircasesTwoSlabsPlaced)
              ->setBaseItemTypeAndMaterial(22, 2);
    Block::registerBlock(44, L"stone_slab", halfStoneSlabBlock);

    // Size: 0xA8u
    Block* brickBlock = (new BlockImpl(Material::STONE, MaterialColor::COLOR_RED))
                            ->setDestroyTime(2.0)
                            ->setExplodeable(10.0)
                            ->setSoundType(SoundType::STONE)
                            ->setIconName(L"brick")
                            ->setNameAndDescriptionId(StringIDs::Bricks, 0x43fc433)
                            ->setBaseItemTypeAndMaterial(13, 14);
    Block::registerBlock(45, L"brick_block", brickBlock);

    // Size: 0xB8u
    Block* tntBlock = (new TntBlock())
                          ->setDestroyTime(0.0)
                          ->setSoundType(SoundType::GRASS)
                          ->setIconName(L"tnt")
                          ->setNameAndDescriptionId(StringIDs::Tnt_2,
                                                    StringIDs::UsedToCauseExplosionsActivatedAfterPlacingBy)
                          ->setBaseItemTypeAndMaterial(28, 0);
    Block::registerBlock(46, L"tnt", tntBlock);

    // Size: 0xA8u
    Block* bookshelfBlock
        = (new BookshelfBlock())
              ->setDestroyTime(1.5)
              ->setSoundType(SoundType::WOOD)
              ->setIconName(L"bookshelf")
              ->setIconName(L"bookshelf")
              ->setNameAndDescriptionId(StringIDs::Bookshelf,
                                        StringIDs::AllowsCreationOfMorePowerfulEnchantmentsWhenPlaced)
              ->setBaseItemTypeAndMaterial(46, 52);
    Block::registerBlock(47, L"bookshelf", bookshelfBlock);

    // Size: 0xA8u
    Block* mossyCobblestoneBlock
        = (new BlockImpl(Material::STONE))
              ->setIconName(L"cobblestone_mossy")
              ->setDestroyTime(2.0)
              ->setExplodeable(10.0)
              ->setSoundType(SoundType::STONE)
              ->setNameAndDescriptionId(StringIDs::MossStone,
                                        StringIDs::FoundInDungeonsCanBeUsedForConstruction)
              ->setBaseItemTypeAndMaterial(14, 2);
    Block::registerBlock(48, L"mossy_cobblestone", mossyCobblestoneBlock);

    // Size: 0xA8u
    Block* obsidianBlock
        = (new ObsidianBlock())
              ->setDestroyTime(50.0)
              ->setExplodeable(2000.0)
              ->setSoundType(SoundType::STONE)
              ->setIconName(L"obsidian")
              ->setNameAndDescriptionId(0x47cbe1a, StringIDs::CanOnlyBeMinedWithADiamondPickaxe)
              ->setBaseItemTypeAndMaterial(13, 2);
    Block::registerBlock(49, L"obsidian", obsidianBlock);

    // Size: 0xA8u
    Block* torchBlock
        = (new TorchBlock())
              ->setDestroyTime(0.0)
              ->setLightEmission(0.9375)
              ->setSoundType(SoundType::WOOD)
              ->setIconName(L"torch_on")
              ->setNameAndDescriptionId(StringIDs::Torch, StringIDs::UsedToCreateLightTorchesAlsoMeltSnow)
              ->disableMipmap()
              ->setBaseItemTypeAndMaterial(23, 1);
    Block::registerBlock(50, L"torch", torchBlock);

    // Size: 0x108u
    Block* fireBlock = (new FireBlock())
                           ->setDestroyTime(0.0)
                           ->setLightEmission(1.0)
                           ->setSoundType(SoundType::WOOL)
                           ->setIconName(L"fire")
                           ->setNotCollectStatistics()
                           ->setNameAndDescriptionId(StringIDs::Fire, 0xFFFFFFFF)
                           ->disableMipmap();
    Block::registerBlock(51, L"fire", fireBlock);

    // Size: 0xB0u
    Block* mobSpawnerBlock = (new MobSpawnerBlock())
                                 ->setDestroyTime(5.0)
                                 ->setSoundType(SoundType::METAL)
                                 ->setIconName(L"mob_spawner")
                                 ->setNotCollectStatistics()
                                 ->setNameAndDescriptionId(StringIDs::MonsterSpawner, 0x4330c9);
    Block::registerBlock(52, L"mob_spawner", mobSpawnerBlock);

    // Size: 0xC0u
    const BlockState* stairBlockVariant = planksBlock->defaultBlockState()->setValue<PlanksBlock::Variant*>(
        PlanksBlock::VARIANT, PlanksBlock::Variant::OAK);
    Block* stairBlock
        = (new StairBlock(stairBlockVariant))
              ->setIconName(L"stairsWood")
              ->sendBlockData(15)
              ->setNameAndDescriptionId(StringIDs::OakWoodStairs, StringIDs::UsedForCompactStaircases_1)
              ->setBaseItemTypeAndMaterial(16, 1);
    Block::registerBlock(53, L"oak_stairs", stairBlock);

    // Size: 0xB8u
    Block* chestBlock = (new ChestBlock(0))
                            ->setDestroyTime(2.5)
                            ->setSoundType(SoundType::WOOD)
                            ->setIconName(L"chest")
                            ->sendBlockData(15)
                            ->setNameAndDescriptionId(StringIDs::Chest_1,
                                                      StringIDs::StoresBlocksAndItemsInsidePlaceTwoChests)
                            ->setBaseItemTypeAndMaterial(36, 1);
    Block::registerBlock(54, L"chest", chestBlock);

    // Size: 0xF8u
    Block* redStoneWireBlock
        = (new RedStoneWireBlock())
              ->setDestroyTime(0.0)
              ->setSoundType(SoundType::STONE)
              ->setIconName(L"redstone_dust")
              ->setNotCollectStatistics()
              ->sendBlockData(15)
              ->setNameAndDescriptionId(StringIDs::RedstoneDust, StringIDs::CanBePlacedOnGroundToCarryAn)
              ->disableMipmap();
    Block::registerBlock(55, L"redstone_wire", redStoneWireBlock);

    // Size: 0xA8u
    Block* oreBlock = (new OreBlock())
                          ->setDestroyTime(3.0)
                          ->setExplodeable(5.0)
                          ->setSoundType(SoundType::STONE)
                          ->setIconName(L"diamond_ore")
                          ->setNameAndDescriptionId(StringIDs::DiamondOre,
                                                    StringIDs::CanBeMinedWithAnIronPickaxeOrIronDiamonds);
    Block::registerBlock(56, L"diamond_ore", oreBlock);

    // Size: 0xA8u
    Block* diamondBlock
        = (new BlockImpl(Material::METAL, MaterialColor::DIAMOND))
              ->setDestroyTime(5.0)
              ->setExplodeable(10.0)
              ->setSoundType(SoundType::METAL)
              ->setIconName(L"diamond_block")
              ->setNameAndDescriptionId(StringIDs::BlockOfDiamond, StringIDs::ACompactWayOfStoringDiamonds)
              ->setBaseItemTypeAndMaterial(32, 5);
    Block::registerBlock(57, L"diamond_block", diamondBlock);

    // Size: 0xB8u
    Block* craftingTableBlock = (new CraftingTableBlock())
                                    ->setDestroyTime(2.5)
                                    ->setSoundType(SoundType::WOOD)
                                    ->setIconName(L"crafting_table")
                                    ->setNameAndDescriptionId(StringIDs::CraftingTable,
                                                              StringIDs::AllowsYouToCraftAMoreVariedSelection)
                                    ->setBaseItemTypeAndMaterial(30, 1);
    Block::registerBlock(58, L"crafting_table", craftingTableBlock);

    // Size: 0xF0u
    Block* cropBlock
        = (new CropBlock(false))
              ->setIconName(L"wheat")
              ->setNotCollectStatistics()
              ->sendBlockData(15)
              ->setNameAndDescriptionId(StringIDs::Crops, StringIDs::WhenFullyGrownCropsCanBeHarvestedTo)
              ->disableMipmap();
    Block::registerBlock(59, L"wheat", cropBlock);

    // Size: 0xB8u
    Block* farmBlock = (new FarmBlock())
                           ->setDestroyTime(0.6)
                           ->setSoundType(SoundType::DIRT)
                           ->setIconName(L"farmland")
                           ->sendBlockData(15)
                           ->setNameAndDescriptionId(StringIDs::Farmland,
                                                     StringIDs::GroundThatHasBeenPreparedReadyToPlant);
    Block* v2182 = farmBlock;  // ???
    Block::registerBlock(60, L"farmland", farmBlock);

    // Size: 0xC8u
    Block* furnaceBlock
        = (new FurnaceBlock(false))
              ->setDestroyTime(3.5)
              ->setSoundType(SoundType::STONE)
              ->setIconName(L"furnace")
              ->sendBlockData(15)
              ->setNameAndDescriptionId(StringIDs::Furnace_2, StringIDs::AllowsYouToSmeltOreCreateCharcoalAnd)
              ->setBaseItemTypeAndMaterial(30, 2);
    Block::registerBlock(61, L"furnace", furnaceBlock);

    // Size: 0xC8u
    Block* litFurnaceBlock = (new FurnaceBlock(true))
                                 ->setDestroyTime(3.5)
                                 ->setSoundType(SoundType::STONE)
                                 ->setIconName(L"furnace")
                                 ->setLightEmission(0.875)
                                 ->sendBlockData(15)
                                 ->setNameAndDescriptionId(StringIDs::Furnace_2,
                                                           StringIDs::AllowsYouToSmeltOreCreateCharcoalAnd);
    Block::registerBlock(62, L"lit_furnace", litFurnaceBlock);

    // Size: 0xB0u
    Block* standingSignBlock
        = (new StandingSignBlock())
              ->setDestroyTime(1.0)
              ->setSoundType(SoundType::WOOD)
              ->setIconName(L"sign")
              ->setNotCollectStatistics()
              ->sendBlockData(15)
              ->setNameAndDescriptionId(StringIDs::Sign_1, StringIDs::ShowsTextEnteredByYouOrOtherPlayers);
    Block::registerBlock(63, L"standing_sign", standingSignBlock);

    // Size: 0xC8u
    Block* doorBlock = (new DoorBlock(Material::WOOD))
                           ->setDestroyTime(3.0)
                           ->setSoundType(SoundType::WOOD)
                           ->setIconName(L"door_wood")
                           ->setNotCollectStatistics()
                           ->sendBlockData(15)
                           ->setNameAndDescriptionId(StringIDs::OakDoor_1,
                                                     StringIDs::WoodenDoorsAreActivatedByUsingHittingmOr);
    Block::registerBlock(64, L"wooden_door", doorBlock);

    // Size: 0xA8u
    Block* ladderBlock = (new LadderBlock())
                             ->setDestroyTime(0.4)
                             ->setSoundType(SoundType::LADDER)
                             ->setIconName(L"ladder")
                             ->sendBlockData(15)
                             ->setNameAndDescriptionId(StringIDs::Ladder, StringIDs::UsedToClimbVertically)
                             ->disableMipmap()
                             ->setBaseItemTypeAndMaterial(48, 1);
    Block::registerBlock(65, L"ladder", ladderBlock);

    // Size: 0xB0u
    Block* railBlock = (new RailBlock())
                           ->setDestroyTime(0.7)
                           ->setSoundType(SoundType::METAL)
                           ->setIconName(L"rail_normal")
                           ->sendBlockData(15)
                           ->setNameAndDescriptionId(StringIDs::Rail, 0xc6204ec)
                           ->setBaseItemTypeAndMaterial(12, 9)
                           ->disableMipmap();
    Block::registerBlock(66, L"rail", railBlock);

    // Size: 0xC0u
    Block* stoneStairBlock
        = (new StairBlock(cobblestoneBlock->defaultBlockState()))
              ->setIconName(L"stairsStone")
              ->sendBlockData(15)
              ->setNameAndDescriptionId(StringIDs::CobblestoneStairs, StringIDs::UsedForCompactStaircases_1)
              ->setBaseItemTypeAndMaterial(16, 2);
    Block::registerBlock(67, L"stone_stairs", stoneStairBlock);

    // Size: 0xB0u
    Block* wallSignBlock
        = (new WallSignBlock())
              ->setDestroyTime(1.0)
              ->setSoundType(SoundType::WOOD)
              ->setIconName(L"sign")
              ->setNotCollectStatistics()
              ->sendBlockData(15)
              ->setNameAndDescriptionId(StringIDs::Sign_1, StringIDs::ShowsTextEnteredByYouOrOtherPlayers);
    Block::registerBlock(68, L"wall_sign", wallSignBlock);

    // Size: 0xA8u
    Block* leverBlock
        = (new LeverBlock())
              ->setDestroyTime(0.5)
              ->setSoundType(SoundType::WOOD)
              ->setIconName(L"lever")
              ->sendBlockData(15)
              ->setNameAndDescriptionId(StringIDs::Lever,
                                        StringIDs::UsedToSendAnElectricalChargeByBeingTurnedOnOrInOn)
              ->setBaseItemTypeAndMaterial(45, 1);
    Block::registerBlock(69, L"lever", leverBlock);

    // Size: 0xC8u
    Block* stonePressurePlateBlock
        = (new PressurePlateBlock(L"stone", Material::STONE, PressurePlateBlock::Sensitivity::STONE))
              ->setDestroyTime(0.5)
              ->setSoundType(SoundType::STONE)
              ->sendBlockData(15)
              ->setNameAndDescriptionId(StringIDs::StonePressurePlate,
                                        StringIDs::APressureSensitivePadThatWillActivateWhen)
              ->setBaseItemTypeAndMaterial(15, 2);
    Block::registerBlock(70, L"stone_pressure_plate", stonePressurePlateBlock);

    // Size: 0xC8u
    Block* ironDoorBlock
        = (new DoorBlock(Material::METAL))
              ->setIconName(L"door_iron")
              ->setDestroyTime(5.0)
              ->setSoundType(SoundType::METAL)
              ->setNotCollectStatistics()
              ->sendBlockData(15)
              ->setNameAndDescriptionId(StringIDs::IronDoor_1, StringIDs::IronDoorsCanOnlyBeOpenedByRedstone);
    Block::registerBlock(71, L"iron_door", ironDoorBlock);

    // Size: 0xC8u
    Block* woodenPressurePlateBlock
        = (new PressurePlateBlock(L"planks_oak", Material::WOOD, PressurePlateBlock::Sensitivity::WOOD))
              ->setDestroyTime(0.5)
              ->setSoundType(SoundType::WOOD)
              ->sendBlockData(15)
              ->setNameAndDescriptionId(0x3827f5, StringIDs::AMoreSensitivePressurePlateThatCanBe)
              ->setBaseItemTypeAndMaterial(15, 1);
    Block::registerBlock(72, L"wooden_pressure_plate", woodenPressurePlateBlock);

    // Size: 0xA8u
    Block* redStoneOreBlock
        = (new RedStoneOreBlock(false))
              ->setIconName(L"redstone_ore")
              ->setDestroyTime(3.0)
              ->setExplodeable(5.0)
              ->setSoundType(SoundType::STONE)
              ->sendBlockData(15)
              ->setNameAndDescriptionId(StringIDs::RedstoneOre,
                                        StringIDs::CanBeMinedWithAnIronPickaxeOrIronRedstoneDust);
    Block::registerBlock(73, L"redstone_ore", redStoneOreBlock);

    // Size: 0xA8u
    Block* litRedStoneOreBlock
        = (new RedStoneOreBlock(true))
              ->setIconName(L"redstone_ore")
              ->setLightEmission(0.625)
              ->setDestroyTime(3.0)
              ->setExplodeable(5.0)
              ->setSoundType(SoundType::STONE)
              ->sendBlockData(15)
              ->setNameAndDescriptionId(StringIDs::RedstoneOre,
                                        StringIDs::CanBeMinedWithAnIronPickaxeOrIronRedstoneDust);
    Block::registerBlock(74, L"lit_redstone_ore", litRedStoneOreBlock);

    // Size: 0xA8u
    Block* unlitRedstoneTorchBlock
        = (new RedstoneTorchBlock(false))
              ->setIconName(L"redstone_torch_off")
              ->setDestroyTime(0.0)
              ->setSoundType(SoundType::WOOD)
              ->sendBlockData(15)
              ->setNameAndDescriptionId(StringIDs::RedstoneTorch,
                                        StringIDs::ConstantlySendsAnElectricalChargeOrCanBe)
              ->disableMipmap();
    Block::registerBlock(75, L"unlit_redstone_torch", unlitRedstoneTorchBlock);

    // Size: 0xA8u
    Block* redstoneTorchBlock
        = (new RedstoneTorchBlock(true))
              ->setIconName(L"redstone_torch_on")
              ->setDestroyTime(0.0)
              ->setLightEmission(0.5)
              ->setSoundType(SoundType::WOOD)
              ->sendBlockData(15)
              ->setNameAndDescriptionId(StringIDs::RedstoneTorch,
                                        StringIDs::ConstantlySendsAnElectricalChargeOrCanBe)
              ->disableMipmap();
    Block::registerBlock(76, L"redstone_torch", redstoneTorchBlock);

    // Size: 0xA8u
    Block* stoneButtonBlock = (new StoneButtonBlock())
                                  ->setIconName(L"button")
                                  ->setDestroyTime(0.5)
                                  ->setSoundType(SoundType::STONE)
                                  ->sendBlockData(15)
                                  ->setNameAndDescriptionId(StringIDs::ButtonButton,
                                                            StringIDs::UsedToSendAnElectricalChargeByBeing)
                                  ->setBaseItemTypeAndMaterial(35, 2);
    Block::registerBlock(77, L"stone_button", stoneButtonBlock);

    // Size: 0xA8u
    Block* snowLayerBlock
        = (new SnowLayerBlock())
              ->setIconName(L"snow")
              ->setDestroyTime(0.1)
              ->setSoundType(SoundType::SNOW)
              ->sendBlockData(15)
              ->setLightBlock(0)
              ->setNameAndDescriptionId(StringIDs::Snow, StringIDs::CanBeDugWithAShovelToCreateSnowballs)
              ->setBaseItemTypeAndMaterial(13, 16);
    Block::registerBlock(78, L"snow_layer", snowLayerBlock);

    // Size: 0xC0u
    Block* iceBlock
        = (new IceBlock(false))
              ->setIconName(L"ice")
              ->setDestroyTime(0.5)
              ->setLightBlock(3)
              ->setSoundType(SoundType::GLASS)
              ->setSemiTransparent()
              ->setNameAndDescriptionId(StringIDs::Ice, StringIDs::SlipperyWhenWalkedOnTurnsIntoWaterIf);
    Block::registerBlock(79, L"ice", iceBlock);

    // Size: 0xA8u
    Block* snowBlock = (new SnowBlock())
                           ->setIconName(L"snow")
                           ->setDestroyTime(0.2)
                           ->setSoundType(SoundType::WOOL)
                           ->setNameAndDescriptionId(StringIDs::Snow, StringIDs::ACompactWayToStoreSnowballs)
                           ->setBaseItemTypeAndMaterial(13, 16);
    Block::registerBlock(80, L"snow", snowBlock);

    // Size: 0xB8u
    Block* cactusBlock
        = (new CactusBlock())
              ->setIconName(L"cactus")
              ->setDestroyTime(0.4)
              ->setSoundType(SoundType::WOOL)
              ->setNameAndDescriptionId(StringIDs::Cactus, StringIDs::CanBeCookedInAFurnaceToCreateAGreenDye)
              ->disableMipmap();
    Block::registerBlock(81, L"cactus", cactusBlock);

    // Size: 0xA8u
    Block* clayBlock
        = (new ClayBlock())
              ->setIconName(L"clay")
              ->setDestroyTime(0.6)
              ->setSoundType(SoundType::DIRT)
              ->setNameAndDescriptionId(StringIDs::Clay_1, StringIDs::WhenBrokenDropsClayBallsWhichCanBe)
              ->setBaseItemTypeAndMaterial(13, 15);
    Block::registerBlock(82, L"clay", clayBlock);

    // Size: 0xB0u
    Block* reedsBlock
        = (new ReedsBlock())
              ->setIconName(L"reeds")
              ->setDestroyTime(0.0)
              ->setSoundType(SoundType::GRASS)
              ->setNotCollectStatistics()
              ->setNameAndDescriptionId(StringIDs::SugarCane, StringIDs::CanBeCraftedToCreateSugar)
              ->disableMipmap();
    Block::registerBlock(83, L"reeds", reedsBlock);

    // Size: 0xB8u
    Block* jukeboxBlock = (new JukeboxBlock())
                              ->setIconName(L"jukebox")
                              ->setDestroyTime(2.0)
                              ->setExplodeable(10.0)
                              ->setSoundType(SoundType::STONE)
                              ->sendBlockData(15)
                              ->setNameAndDescriptionId(StringIDs::Jukebox, StringIDs::PlaysMusicDiscs)
                              ->setBaseItemTypeAndMaterial(53, 0);
    Block::registerBlock(84, L"jukebox", jukeboxBlock);

    // Size: 0xC0u
    Block* fenceBlock
        = (new FenceBlock(L"planks_oak", Material::WOOD, PlanksBlock::Variant::OAK->getMaterialColor()))
              ->setDestroyTime(2.0)
              ->setExplodeable(5.0)
              ->setSoundType(SoundType::WOOD)
              ->setNameAndDescriptionId(StringIDs::OakFence, StringIDs::UsedAsABarrierThatCannotBeJumped)
              ->setBaseItemTypeAndMaterial(29, 1);
    Block::registerBlock(85, L"fence", fenceBlock);

    // Size: 0xD8u
    Block* pumpkinBlock
        = (new PumpkinBlock())
              ->setIconName(L"pumpkin")
              ->setDestroyTime(1.0)
              ->setSoundType(SoundType::WOOD)
              ->sendBlockData(15)
              ->setNameAndDescriptionId(StringIDs::Pumpkin, StringIDs::CanBeWornAsAHelmetOrCrafted);
    Block::registerBlock(86, L"pumpkin", pumpkinBlock);

    // Size: 0xA8u
    Block* netherrackBlock
        = (new NetherrackBlock())
              ->setIconName(L"netherrack")
              ->setDestroyTime(0.4)
              ->setSoundType(SoundType::STONE)
              ->setNameAndDescriptionId(StringIDs::Netherrack, StringIDs::BurnsForeverIfSetAlight);
    Block::registerBlock(87, L"netherrack", netherrackBlock);

    // Size: 0xA8u
    Block* soulSandBlock
        = (new SoulSandBlock())
              ->setIconName(L"soul_sand")
              ->setDestroyTime(0.5)
              ->setSoundType(SoundType::SAND)
              ->setNameAndDescriptionId(StringIDs::SoulSand, StringIDs::SlowsMovementOfAnythingWalkingOverIt);
    Block::registerBlock(88, L"soul_sand", soulSandBlock);

    // Size: 0xA8u
    Block* glowstoneblock
        = (new Glowstoneblock(Material::GLASS))  // they forgot to capitalize block it seems
              ->setIconName(L"glowstone")
              ->setDestroyTime(0.3)
              ->setSoundType(SoundType::GLASS)
              ->setLightEmission(1.0)
              ->setNameAndDescriptionId(StringIDs::Glowstone,
                                        StringIDs::UsedToCreateBrighterLightThanTorchesMelts)
              ->setBaseItemTypeAndMaterial(23, 23);
    Block::registerBlock(89, L"glowstone", glowstoneblock);

    // Size: 0xC0u
    Block* portalBlock
        = (new PortalBlock())
              ->setDestroyTime(-1.0)
              ->setIconName(L"portal")
              ->setSoundType(SoundType::GLASS)
              ->setLightEmission(0.75)
              ->setNameAndDescriptionId(StringIDs::Portal, StringIDs::StandingInPortalAllowsYouToPassBetween);
    Block::registerBlock(90, L"portal", portalBlock);

    // Size: 0xD8u
    Block* litPumpkinBlock = (new PumpkinBlock())
                                 ->setIconName(L"pumpkin")
                                 ->setDestroyTime(1.0)
                                 ->setSoundType(SoundType::WOOD)
                                 ->setLightEmission(1.0)
                                 ->sendBlockData(15)
                                 ->setNameAndDescriptionId(StringIDs::JackOLantern, 0xc9d5fb8)
                                 ->setBaseItemTypeAndMaterial(23, 22);
    Block::registerBlock(91, L"lit_pumpkin", litPumpkinBlock);

    // Size: 0xC0u
    Block* cakeBlock
        = (new CakeBlock())
              ->setIconName(L"cake")
              ->setDestroyTime(0.5)
              ->setSoundType(SoundType::WOOL)
              ->setNotCollectStatistics()
              ->sendBlockData(15)
              ->setNameAndDescriptionId(StringIDs::Cake_1, StringIDs::Restores1IconShank01CanBeUsed7Times);
    Block::registerBlock(92, L"cake", cakeBlock);

    // Size: 0xA8u
    Block* unpoweredRepeaterBlock
        = (new RepeaterBlock(false))
              ->setIconName(L"repeater_off")
              ->setDestroyTime(0.0)
              ->setSoundType(SoundType::WOOD)
              ->setNotCollectStatistics()
              ->sendBlockData(15)
              ->setNameAndDescriptionId(StringIDs::RedstoneRepeater,
                                        StringIDs::UsedInRedstoneCircuitsAsARepeaterA)
              ->disableMipmap()
              ->setBaseItemTypeAndMaterial(59, 0);
    Block::registerBlock(93, L"unpowered_repeater", unpoweredRepeaterBlock);

    // Size: 0xA8u
    Block* poweredRepeaterBlock = (new RepeaterBlock(true))
                                      ->setIconName(L"repeater_on")
                                      ->setDestroyTime(0.0)
                                      ->setSoundType(SoundType::WOOD)
                                      ->setNotCollectStatistics()
                                      ->sendBlockData(15)
                                      ->setNameAndDescriptionId(StringIDs::RedstoneRepeater,
                                                                StringIDs::UsedInRedstoneCircuitsAsARepeaterA)
                                      ->disableMipmap()
                                      ->setBaseItemTypeAndMaterial(59, 0);
    Block::registerBlock(94, L"powered_repeater", poweredRepeaterBlock);

    // Size: 0xC0u
    Block* stainedGlassBlock
        = (new StainedGlassBlock(Material::GLASS))
              ->setIconName(L"glass")
              ->setDestroyTime(0.3)
              ->setSoundType(SoundType::GLASS)
              ->setNameAndDescriptionId(StringIDs::StainedGlass, StringIDs::CraftedFromGlassAndADye)
              ->setSemiTransparent()
              ->setBaseItemTypeAndMaterial(42, 34);
    Block::registerBlock(95, L"stained_glass", stainedGlassBlock);

    // Size: 0xA8u
    Block* trapDoorBlock
        = (new TrapDoorBlock(Material::WOOD))
              ->setIconName(L"trapdoor")
              ->setDestroyTime(3.0)
              ->setSoundType(SoundType::WOOD)
              ->setNotCollectStatistics()
              ->sendBlockData(15)
              ->setNameAndDescriptionId(StringIDs::WoodenTrapdoor,
                                        StringIDs::ActivatedByUsingHittingmOrWithRedstoneThey)
              ->setBaseItemTypeAndMaterial(6, 25);
    Block::registerBlock(96, L"trapdoor", trapDoorBlock);

    // Size: 0xA8u
    Block* monsterEggBlock
        = (new MonsterEggBlock())
              ->setIconName(L"monsterStoneEgg")
              ->setDestroyTime(0.75)
              ->setNameAndDescriptionId(StringIDs::SilverfishStone,
                                        StringIDs::SpawnsASilverfishWhenDestroyedMayAlsoSpawn);
    Block::registerBlock(97, L"monster_egg", monsterEggBlock);

    // Size: 0xC8u
    Block* stoneBrickBlock
        = (new StoneBrickBlock())
              ->setIconName(L"stonebrick")
              ->setDestroyTime(1.5)
              ->setExplodeable(10.0)
              ->setSoundType(SoundType::STONE)
              ->setNameAndDescriptionId(StringIDs::StoneBricks,
                                        StringIDs::MadeFromStoneBlocksCommonlyFoundInStrongholds)
              ->setBaseItemTypeAndMaterial(14, 31);
    Block::registerBlock(98, L"stonebrick", stoneBrickBlock);

    // Size: 0xD8u
    Block* brownHugeMushroomBlock
        = (new HugeMushroomBlock(Material::WOOD, MaterialColor::DIRT, brownMushroomBlock))
              ->setIconName(L"mushroom_block")
              ->setDestroyTime(0.2)
              ->setSoundType(SoundType::WOOD)
              ->setNameAndDescriptionId(StringIDs::Mushroom, StringIDs::CanBeUsedAsDecoration_1)
              ->sendBlockData(15);
    Block::registerBlock(99, L"brown_mushroom_block", brownHugeMushroomBlock);

    // Size: 0xD8u
    Block* redHugeMushroomBlock
        = (new HugeMushroomBlock(Material::WOOD, MaterialColor::COLOR_RED, redMushroomBlock))
              ->setIconName(L"mushroom_block")
              ->setDestroyTime(0.2)
              ->setSoundType(SoundType::WOOD)
              ->setNameAndDescriptionId(StringIDs::Mushroom_1, StringIDs::CanBeUsedAsDecoration_1)
              ->sendBlockData(15);
    Block::registerBlock(100, L"red_mushroom_block", redHugeMushroomBlock);

    // Size: 0xE0u
    Block* thinFenceBlock
        = (new ThinFenceBlock(L"iron_bars", L"iron_bars", Material::METAL, true))
              ->setDestroyTime(5.0)
              ->setExplodeable(10.0)
              ->setSoundType(SoundType::METAL)
              ->setNameAndDescriptionId(StringIDs::IronBars, StringIDs::UsedAsABarrierSimilarToFences)
              ->setBaseItemTypeAndMaterial(29, 3);
    Block::registerBlock(101, L"iron_bars", thinFenceBlock);

    // Size: 0xE0u
    Block* glassPaneBlock
        = (new ThinFenceBlock(L"glass", L"glass_pane_top", Material::GLASS, false))
              ->setDestroyTime(0.3)
              ->setSoundType(SoundType::GLASS)
              ->setNameAndDescriptionId(StringIDs::GlassPane, StringIDs::TransparentBlocksThatCanBeUsedAsAn)
              ->setBaseItemTypeAndMaterial(42, 34);
    Block::registerBlock(102, L"glass_pane", glassPaneBlock);

    // Size: 0xB0u
    Block* melonBlock
        = (new MelonBlock())
              ->setIconName(L"melon")
              ->setDestroyTime(1.0)
              ->setSoundType(SoundType::WOOD)
              ->setNameAndDescriptionId(StringIDs::Melon, StringIDs::CanBeCraftedFromMelonSlices);
    Block::registerBlock(103, L"melon_block", melonBlock);

    // Size: 0xC0u
    Block* pumpkinStemBlock = (new StemBlock(pumpkinBlock))
                                  ->setIconName(L"pumpkin_stem")
                                  ->setDestroyTime(0.0)
                                  ->setSoundType(SoundType::WOOD)
                                  ->sendBlockData(15)
                                  ->setNameAndDescriptionId(StringIDs::PumpkinStem, 0xFFFFFFFF)
                                  ->disableMipmap();
    Block::registerBlock(104, L"pumpkin_stem", pumpkinStemBlock);

    // Size: 0xC0u
    Block* melonStemBlock = (new StemBlock(melonBlock))
                                ->setIconName(L"melon_stem")
                                ->setDestroyTime(0.0)
                                ->setSoundType(SoundType::WOOD)
                                ->sendBlockData(15)
                                ->setNameAndDescriptionId(StringIDs::MelonStem, 0xFFFFFFFF)
                                ->disableMipmap();
    Block::registerBlock(105, L"melon_stem", melonStemBlock);

    // Size: 0xA8u
    Block* vineBlock
        = (new VineBlock())
              ->setIconName(L"vine")
              ->setDestroyTime(0.2)
              ->setSoundType(SoundType::GRASS)
              ->sendBlockData(15)
              ->setNameAndDescriptionId(StringIDs::Vines, StringIDs::GrowsOverTimeWhenPlacedCanBeCollected)
              ->disableMipmap();
    Block::registerBlock(106, L"vine", vineBlock);

    // Size: 0xC0u
    Block* fenceGateBlock = (new FenceGateBlock(L"planks_oak", PlanksBlock::Variant::OAK))
                                ->setIconName(L"fenceGate")
                                ->setDestroyTime(2.0)
                                ->setExplodeable(5.0)
                                ->setSoundType(SoundType::WOOD)
                                ->sendBlockData(15)
                                ->setNameAndDescriptionId(StringIDs::OakFenceGate,
                                                          StringIDs::SimilarToADoorButUsedPrimarilyWithFences)
                                ->setBaseItemTypeAndMaterial(47, 1);
    Block::registerBlock(107, L"fence_gate", fenceGateBlock);

    // Size: 0xC0u
    Block* brickStairBlock
        = (new StairBlock(brickBlock->defaultBlockState()))
              ->setIconName(L"stairsBrick")
              ->sendBlockData(15)
              ->setNameAndDescriptionId(StringIDs::BrickStairs, StringIDs::UsedForCompactStaircases_1)
              ->setBaseItemTypeAndMaterial(16, 14);
    Block::registerBlock(108, L"brick_stairs", brickStairBlock);

    // Size: 0xC0u
    const BlockState* stoneBrickStairBlockVariant
        = stoneBrickBlock->defaultBlockState()->setValue<StoneBrickBlock::Variant*>(
            StoneBrickBlock::VARIANT, StoneBrickBlock::Variant::DEFAULT);
    Block* stoneBrickStairBlock
        = (new StairBlock(stoneBrickStairBlockVariant))
              ->setIconName(L"stairsStoneBrickSmooth")
              ->sendBlockData(15)
              ->setNameAndDescriptionId(StringIDs::StoneBrickStairs, StringIDs::UsedForCompactStaircases_1)
              ->setBaseItemTypeAndMaterial(16, 31);
    Block::registerBlock(109, L"stone_brick_stairs", stoneBrickStairBlock);

    // Size: 0xB8u
    Block* myceliumBlock
        = (new MyceliumBlock())
              ->setIconName(L"mycelium")
              ->setDestroyTime(0.6)
              ->setSoundType(SoundType::GRASS)
              ->setNameAndDescriptionId(StringIDs::Mycelium, StringIDs::SimilarToGrassBlocksButVeryGoodFor);
    Block::registerBlock(110, L"mycelium", myceliumBlock);

    // Size: 0xA8u
    Block* waterlilyBlock
        = (new WaterlilyBlock())
              ->setIconName(L"waterlily")
              ->setDestroyTime(0.0)
              ->setSoundType(SoundType::GRASS)
              ->setNameAndDescriptionId(StringIDs::LilyPad, StringIDs::FloatsOnWaterAndCanBeWalkedOn)
              ->disableMipmap();
    Block::registerBlock(111, L"waterlily", waterlilyBlock);

    // Size: 0xA8u
    Block* netherBrickBlock
        = (new NetherBrickBlock())
              ->setIconName(L"nether_brick")
              ->setDestroyTime(2.0)
              ->setExplodeable(10.0)
              ->setSoundType(SoundType::STONE)
              ->setNameAndDescriptionId(StringIDs::NetherBrick_1,
                                        StringIDs::UsedToBuildNetherFortressesImmuneToGhast)
              ->setBaseItemTypeAndMaterial(13, 32);
    Block::registerBlock(112, L"nether_brick", netherBrickBlock);

    // Size: 0xC0u
    Block* netherBrickFenceBlock
        = (new FenceBlock(L"nether_brick", Material::STONE, MaterialColor::NETHER))
              ->setDestroyTime(2.0)
              ->setExplodeable(10.0)
              ->setSoundType(SoundType::STONE)
              ->setNameAndDescriptionId(StringIDs::NetherBrickFence, StringIDs::UsedInNetherFortresses)
              ->setBaseItemTypeAndMaterial(29, 32);
    Block::registerBlock(113, L"nether_brick_fence", netherBrickFenceBlock);

    // Size: 0xC0u
    Block* netherBrickStairBlock
        = (new StairBlock(netherBrickBlock->defaultBlockState()))
              ->setIconName(L"stairsNetherBrick")
              ->sendBlockData(15)
              ->setNameAndDescriptionId(StringIDs::NetherBrickStairs, StringIDs::UsedForCompactStaircases_1)
              ->setBaseItemTypeAndMaterial(16, 32);
    Block::registerBlock(114, L"nether_brick_stairs", netherBrickStairBlock);

    // Size: 0xC0u
    Block* netherWartCropBlock
        = (new NetherWartBlock())
              ->setIconName(L"nether_wart")
              ->sendBlockData(15)
              ->setNameAndDescriptionId(StringIDs::NetherWart_1,
                                        StringIDs::FoundInNetherFortressesWillDropNetherWart)
              ->disableMipmap();
    Block::registerBlock(115, L"nether_wart", netherWartCropBlock);

    // Size: 0xC0u
    Block* enchantmentTableBlock
        = (new EnchantmentTableBlock())
              ->setIconName(L"enchanting_table")
              ->setDestroyTime(5.0)
              ->setExplodeable(2000.0)
              ->setNameAndDescriptionId(StringIDs::EnchantmentTable,
                                        StringIDs::ThisAllowsPlayersToEnchantSwordsPickaxesAxes)
              ->setBaseItemTypeAndMaterial(30, 36);
    Block::registerBlock(116, L"enchanting_table", enchantmentTableBlock);

    // Size: 0xB8u
    Block* brewingStandBlock = (new BrewingStandBlock())
                                   ->setIconName(L"brewing_stand")
                                   ->setDestroyTime(0.5)
                                   ->setLightEmission(0.125)
                                   ->sendBlockData(15)
                                   ->setNameAndDescriptionId(StringIDs::BrewingStand_2,
                                                             StringIDs::UsedForMakingPotionsAndSplashPotions)
                                   ->setBaseItemTypeAndMaterial(30, 35);
    Block::registerBlock(117, L"brewing_stand", brewingStandBlock);

    // Size: 0xD0u
    Block* cauldronBlock
        = (new CauldronBlock())
              ->setIconName(L"cauldron")
              ->setDestroyTime(2.0)
              ->sendBlockData(15)
              ->setNameAndDescriptionId(StringIDs::Cauldron_1, StringIDs::UsedToMixDyesAndDyeArmorOr);
    Block::registerBlock(118, L"cauldron", cauldronBlock);

    // Size: 0xB0u
    Block* endPortalBlock
        = (new EndPortalBlock(Material::PORTAL))
              ->setDestroyTime(3.4028e38)
              ->setExplodeable(6000000.0)
              ->setNameAndDescriptionId(StringIDs::EndPortal, StringIDs::ThisCanBeActivatedUsingTwelveEyeOf);
    Block::registerBlock(119, L"end_portal", endPortalBlock);

    // Size: 0xB8u
    Block* endPortalFrameBlock
        = (new EndPortalFrameBlock())
              ->setIconName(L"endframe")
              ->setSoundType(SoundType::GLASS)
              ->setLightEmission(0.125)
              ->setDestroyTime(3.4028e38)
              ->sendBlockData(15)
              ->setExplodeable(6000000.0)
              ->setNameAndDescriptionId(StringIDs::EndPortalFrame, StringIDs::UsedToFormAnEndPortal);
    Block::registerBlock(120, L"end_portal_frame", endPortalFrameBlock);

    // Size: 0xA8u
    Block* endStoneBlock
        = (new BlockImpl(Material::STONE, MaterialColor::SAND))
              ->setIconName(L"end_stone")
              ->setDestroyTime(3.0)
              ->setExplodeable(15.0)
              ->setSoundType(SoundType::STONE)
              ->setNameAndDescriptionId(StringIDs::EndStone, StringIDs::ABlockTypeFoundInTheEndIt);
    Block::registerBlock(121, L"end_stone", endStoneBlock);

    // Size: 0xA8u
    Block* dragonEggBlock
        = (new DragonEggBlock())
              ->setDestroyTime(3.0)
              ->setIconName(L"dragon_egg")
              ->setExplodeable(15.0)
              ->setSoundType(SoundType::STONE)
              ->setLightEmission(0.125)
              ->setNameAndDescriptionId(StringIDs::DragonEgg, StringIDs::ThisBlockIsCreatedByDefeatOfDragon);
    Block::registerBlock(122, L"dragon_egg", dragonEggBlock);

    // Size: 0xA8u
    Block* redstoneLampBlock
        = (new RedstoneLampBlock(false))
              ->setIconName(L"redstone_lamp_off")
              ->setDestroyTime(0.3)
              ->setSoundType(SoundType::GLASS)
              ->setBaseItemTypeAndMaterial(56, 0)
              ->setNameAndDescriptionId(StringIDs::RedstoneLamp, StringIDs::EmitsLightWhenPowered);
    Block::registerBlock(123, L"redstone_lamp", redstoneLampBlock);

    // Size: 0xA8u
    Block* litRedstoneLampBlock
        = (new RedstoneLampBlock(true))
              ->setIconName(L"redstone_lamp_on")
              ->setDestroyTime(0.3)
              ->setSoundType(SoundType::GLASS)
              ->setBaseItemTypeAndMaterial(56, 0)
              ->setNameAndDescriptionId(StringIDs::RedstoneLamp, StringIDs::EmitsLightWhenPowered);
    Block::registerBlock(124, L"lit_redstone_lamp", litRedstoneLampBlock);

    // Size: 0xA8u
    Block* fullWoodSlabBlock
        = (new FullWoodSlabBlock())
              ->setIconName(L"woodSlab")
              ->setDestroyTime(2.0)
              ->setExplodeable(5.0)
              ->setSoundType(SoundType::WOOD)
              ->setNameAndDescriptionId(StringIDs::UsedForMakingLongStaircasesTwoSlabsPlaced_5,
                                        StringIDs::UsedForMakingLongStaircasesTwoSlabsPlaced_5)
              ->setBaseItemTypeAndMaterial(21, 1);
    Block::registerBlock(125, L"double_wooden_slab", fullWoodSlabBlock);

    // Size: 0xA8u
    Block* halfWoodSlabBlock
        = (new HalfWoodSlabBlock())
              ->setIconName(L"woodSlab")
              ->setDestroyTime(2.0)
              ->setExplodeable(5.0)
              ->setSoundType(SoundType::WOOD)
              ->setNameAndDescriptionId(StringIDs::UsedForMakingLongStaircasesTwoSlabsPlaced_5,
                                        StringIDs::UsedForMakingLongStaircasesTwoSlabsPlaced_5)
              ->setBaseItemTypeAndMaterial(22, 1);
    Block::registerBlock(126, L"wooden_slab", halfWoodSlabBlock);

    // Size: 0xC8u
    Block* cocoaBlock
        = (new CocoaBlock())
              ->setIconName(L"cocoa")
              ->setDestroyTime(0.2)
              ->setExplodeable(5.0)
              ->setSoundType(SoundType::WOOD)
              ->sendBlockData(15)
              ->setNameAndDescriptionId(StringIDs::Cocoa, StringIDs::CanBeFarmedToCollectCocoaBeans);
    Block::registerBlock(127, L"cocoa", cocoaBlock);

    // Size: 0xC0u
    const BlockState* sandStoneStairBlockVariant
        = sandStoneBlock->defaultBlockState()->setValue<SandStoneBlock::Variant*>(
            SandStoneBlock::TYPE, SandStoneBlock::Variant::DEFAULT);
    Block* sandStoneStairBlock
        = (new StairBlock(sandStoneStairBlockVariant))
              ->setIconName(L"stairsSandstone")
              ->sendBlockData(15)
              ->setNameAndDescriptionId(StringIDs::SandstoneStairs, StringIDs::UsedForCompactStaircases_1)
              ->setBaseItemTypeAndMaterial(16, 13);
    Block::registerBlock(128, L"sandstone_stairs", sandStoneStairBlock);

    // Size: 0xA8u
    Block* emeraldOreBlock
        = (new OreBlock())
              ->setIconName(L"emerald_ore")
              ->setDestroyTime(3.0)
              ->setExplodeable(5.0)
              ->setSoundType(SoundType::STONE)
              ->setNameAndDescriptionId(StringIDs::EmeraldOre, StringIDs::CanBeMinedWithAnIronPickaxeOr);
    Block::registerBlock(129, L"emerald_ore", emeraldOreBlock);

    // Size: 0xB0u
    Block* enderChestBlock = (new EnderChestBlock())
                                 ->setDestroyTime(22.5)
                                 ->setIconName(L"enderChest")
                                 ->setExplodeable(1000.0)
                                 ->setSoundType(SoundType::STONE)
                                 ->sendBlockData(15)
                                 ->setLightEmission(0.5)
                                 ->setNameAndDescriptionId(StringIDs::EnderChest,
                                                           StringIDs::SimilarToAChestExceptThatItemsPlaced)
                                 ->setBaseItemTypeAndMaterial(36, 33);
    Block::registerBlock(130, L"ender_chest", enderChestBlock);

    // Size: 0xA8u
    Block* tripWireHookBlock = (new TripWireHookBlock())
                                   ->setIconName(L"trip_wire_source")
                                   ->sendBlockData(15)
                                   ->setNameAndDescriptionId(StringIDs::TripwireHook,
                                                             StringIDs::IsActivatedWhenAnEntityPassesThroughA)
                                   ->setBaseItemTypeAndMaterial(45, 0);
    Block::registerBlock(131, L"tripwire_hook", tripWireHookBlock);

    // Size: 0xA8u
    Block* tripWireBlock
        = (new TripWireBlock())
              ->setIconName(L"trip_wire")
              ->sendBlockData(15)
              ->setNameAndDescriptionId(0x36c80c9, StringIDs::ActivatesAConnectedTripwireHookWhenAnEntity)
              ->disableMipmap();
    Block::registerBlock(132, L"tripwire", tripWireBlock);

    // Size: 0xA8u
    Block* emeraldBlock
        = (new BlockImpl(Material::METAL, MaterialColor::EMERALD))
              ->setIconName(L"emerald_block")
              ->setDestroyTime(5.0)
              ->setExplodeable(10.0)
              ->setSoundType(SoundType::METAL)
              ->setNameAndDescriptionId(StringIDs::BlockOfEmerald, StringIDs::ACompactWayOfStoringEmeralds)
              ->setBaseItemTypeAndMaterial(32, 44);
    Block::registerBlock(133, L"emerald_block", emeraldBlock);

    // Size: 0xC0u
    const BlockState* spruceStairBlockVariant
        = planksBlock->defaultBlockState()->setValue<PlanksBlock::Variant*>(PlanksBlock::VARIANT,
                                                                            PlanksBlock::Variant::SPRUCE);
    Block* spruceStairBlock
        = (new StairBlock(spruceStairBlockVariant))
              ->setIconName(L"stairsWoodSpruce")
              ->sendBlockData(15)
              ->setNameAndDescriptionId(StringIDs::SpruceWoodStairs, StringIDs::UsedForCompactStaircases_1)
              ->setBaseItemTypeAndMaterial(16, 39);
    Block::registerBlock(134, L"spruce_stairs", stairBlock);

    // Size: 0xC0u
    const BlockState* birchStairBlockVariant
        = planksBlock->defaultBlockState()->setValue<PlanksBlock::Variant*>(PlanksBlock::VARIANT,
                                                                            PlanksBlock::Variant::BIRCH);
    Block* birchStairBlock
        = (new StairBlock(birchStairBlockVariant))
              ->setIconName(L"stairsWoodBirch")
              ->sendBlockData(15)
              ->setNameAndDescriptionId(StringIDs::BirchWoodStairs, StringIDs::UsedForCompactStaircases_1)
              ->setBaseItemTypeAndMaterial(16, 40);
    Block::registerBlock(135, L"birch_stairs", birchStairBlock);

    // Size: 0xC0u
    const BlockState* jungleStairBlockVariant
        = planksBlock->defaultBlockState()->setValue<PlanksBlock::Variant*>(PlanksBlock::VARIANT,
                                                                            PlanksBlock::Variant::JUNGLE);
    Block* jungleStairBlock
        = (new StairBlock(jungleStairBlockVariant))
              ->setIconName(L"stairsWoodJungle")
              ->sendBlockData(15)
              ->setNameAndDescriptionId(StringIDs::JungleWoodStairs, StringIDs::UsedForCompactStaircases_1)
              ->setBaseItemTypeAndMaterial(16, 41);
    Block::registerBlock(136, L"jungle_stairs", jungleStairBlock);

    // Size: 0xB0u
    Block* beaconBlock
        = (new BeaconBlock())
              ->setIconName(L"beacon")
              ->setLightEmission(1.0)
              ->setSoundType(SoundType::GLASS)
              ->setNameAndDescriptionId(StringIDs::Beacon_1, StringIDs::ProjectsABeamOfLightIntoSkyAnd);
    Block::registerBlock(138, L"beacon", beaconBlock);

    // Size: 0xA8u
    Block* cobblestoneWallBlock
        = (new WallBlock(cobblestoneBlock))
              ->setIconName(L"cobbleWall")
              ->setNameAndDescriptionId(StringIDs::CobblestoneWall, StringIDs::AWallMadeOfCobblestone)
              ->setBaseItemTypeAndMaterial(29, 2);
    Block::registerBlock(139, L"cobblestone_wall", cobblestoneWallBlock);

    // Size: 0xB0u
    Block* flowerPotBlock
        = (new FlowerPotBlock())
              ->setDestroyTime(0.0)
              ->setIconName(L"flower_pot")
              ->setSoundType(SoundType::STONE)
              ->setNameAndDescriptionId(StringIDs::FlowerPot_1,
                                        StringIDs::UsedAsADecorationFlowersSaplingsCactiAnd);
    Block::registerBlock(140, L"flower_pot", flowerPotBlock);

    // Size: 0x110u
    Block* carrotBlock
        = (new CarrotBlock())
              ->setIconName(L"carrots")
              ->setNameAndDescriptionId(StringIDs::Carrots, StringIDs::Restores15IconShank01AndCan)
              ->disableMipmap();
    Block::registerBlock(141, L"carrots", carrotBlock);

    // Size: 0x110u
    Block* potatoBlock
        = (new PotatoBlock())
              ->setIconName(L"potatoes")
              ->setNameAndDescriptionId(StringIDs::Potatoes, StringIDs::Restores05IconShank01OrCan)
              ->disableMipmap();
    Block::registerBlock(142, L"potatoes", potatoBlock);

    // Size: 0xA8u
    Block* woodButtonBlock = (new WoodButtonBlock())
                                 ->setIconName(L"button")
                                 ->setBaseItemTypeAndMaterial(35, 1)
                                 ->setDestroyTime(0.5)
                                 ->setSoundType(SoundType::WOOD)
                                 ->sendBlockData(15)
                                 ->setNameAndDescriptionId(StringIDs::ButtonButton,
                                                           StringIDs::UsedToSendAnElectricalChargeByBeing);
    Block::registerBlock(143, L"wooden_button", woodButtonBlock);

    // Size: 0xC0u
    Block* skullBlock
        = (new SkullBlock())
              ->setIconName(L"")
              ->setDestroyTime(1.0)
              ->setSoundType(SoundType::STONE)
              ->setNameAndDescriptionId(StringIDs::Skull_1, StringIDs::MobHeadsCanBePlacedAsADecoration);
    Block::registerBlock(144, L"skull", skullBlock);

    // Size: 0xC0u
    Block* anvilBlock
        = (new AnvilBlock())
              ->setIconName(L"anvil")
              ->setBaseItemTypeAndMaterial(30, 3)
              ->setDestroyTime(5.0)
              ->setSoundType(SoundType::ANVIL)
              ->setExplodeable(2000.0)
              ->sendBlockData(15)
              ->setNameAndDescriptionId(StringIDs::Anvil_1, StringIDs::CanBeUsedToRepairWeaponsToolsAndArmor);
    Block::registerBlock(145, L"anvil", anvilBlock);

    // Size: 0xB8u
    Block* trappedChestBlock
        = (new ChestBlock(true))
              ->setBaseItemTypeAndMaterial(36, 25)
              ->setDestroyTime(2.5)
              ->setSoundType(SoundType::WOOD)
              ->setNameAndDescriptionId(
                  StringIDs::TrappedChest,
                  StringIDs::StoresBlocksAndItemsInsidePlaceTwoChestsATrappedAlsoCreatesRedstone);
    Block::registerBlock(146, L"trapped_chest", trappedChestBlock);

    // Size: 0xC8u
    Block* lightWeightedPressurePlateBlock
        = (new WeightedPressurePlateBlock(L"gold_block", Material::METAL, 15, MaterialColor::GOLD))
              ->setBaseItemTypeAndMaterial(15, 4)
              ->setDestroyTime(0.5)
              ->setSoundType(SoundType::WOOD)
              ->setNameAndDescriptionId(StringIDs::WeightedPressurePlateLight,
                                        StringIDs::ProvidesARedstoneChargeTheChargeWillBe_1);
    Block::registerBlock(147, L"light_weighted_pressure_plate", lightWeightedPressurePlateBlock);

    // Size: 0xC8u
    Block* heavyWeightedPressurePlateBlock
        = (new WeightedPressurePlateBlock(L"iron_block", Material::METAL, 150, 0))
              ->setBaseItemTypeAndMaterial(15, 3)
              ->setDestroyTime(0.5)
              ->setSoundType(SoundType::WOOD)
              ->setNameAndDescriptionId(StringIDs::WeightedPressurePlateHeavy,
                                        StringIDs::ProvidesARedstoneChargeTheChargeWillBe);
    Block::registerBlock(148, L"heavy_weighted_pressure_plate", heavyWeightedPressurePlateBlock);

    // Size: 0xB0u
    Block* unpoweredComparatorBlock
        = (new ComparatorBlock(false))
              ->setIconName(L"comparator_off")
              ->setDestroyTime(0.0)
              ->setSoundType(SoundType::WOOD)
              ->setNameAndDescriptionId(StringIDs::RedstoneComparator_1,
                                        StringIDs::UsedInRedstoneCircuitsToMaintainCompareOr)
              ->disableMipmap()
              ->setBaseItemTypeAndMaterial(59, 0);
    Block::registerBlock(149, L"unpowered_comparator", unpoweredComparatorBlock);

    // Size: 0xB0u
    Block* poweredComparatorBlock
        = (new ComparatorBlock(true))
              ->setIconName(L"comparator_on")
              ->setDestroyTime(0.0)
              ->setLightEmission(0.625)
              ->setSoundType(SoundType::WOOD)
              ->setNameAndDescriptionId(StringIDs::RedstoneComparator_1,
                                        StringIDs::UsedInRedstoneCircuitsToMaintainCompareOr)
              ->disableMipmap()
              ->setBaseItemTypeAndMaterial(59, 0);
    Block::registerBlock(150, L"powered_comparator", poweredComparatorBlock);

    // Size: 0xD0u
    Block* daylightDetectorBlock
        = (new DaylightDetectorBlock(false))
              ->setIconName(L"daylight_detector")
              ->setNameAndDescriptionId(StringIDs::DaylightSensor,
                                        StringIDs::ABlockThatOutputsARedstoneSignalBased);
    Block::registerBlock(151, L"daylight_detector", daylightDetectorBlock);

    // Size: 0xA8u
    Block* redstoneBlock = (new PoweredBlock(Material::METAL, MaterialColor::FIRE))
                               ->setIconName(L"redstone_block")
                               ->setDestroyTime(5.0)
                               ->setExplodeable(10.0)
                               ->setSoundType(SoundType::METAL)
                               ->setNameAndDescriptionId(StringIDs::BlockOfRedstone,
                                                         StringIDs::UsedAsARedstonePowerSourceCanBe)
                               ->setBaseItemTypeAndMaterial(32, 48);
    Block::registerBlock(152, L"redstone_block", redstoneBlock);

    // Size: 0xA8u
    Block* quartzOreBlock = (new OreBlock(MaterialColor::NETHER))
                                ->setIconName(L"quartz_ore")
                                ->setDestroyTime(3.0)
                                ->setExplodeable(5.0)
                                ->setSoundType(SoundType::STONE)
                                ->setNameAndDescriptionId(StringIDs::NetherQuartzOre,
                                                          StringIDs::CanBeMinedWithAPickaxeToCollect);
    Block::registerBlock(153, L"quartz_ore", quartzOreBlock);

    // Size: 0xC8u
    Block* hopperBlock
        = (new HopperBlock())
              ->setIconName(L"hopper")
              ->setDestroyTime(3.0)
              ->setExplodeable(8.0)
              ->setSoundType(SoundType::METAL)
              ->setNameAndDescriptionId(StringIDs::Hopper_1, StringIDs::UsedToCatchItemsOrToTransferItems)
              ->setBaseItemTypeAndMaterial(51, 0);
    Block::registerBlock(154, L"hopper", hopperBlock);

    // Size: 0xF0u
    Block* quartzBlock = (new QuartzBlock())
                             ->setIconName(L"quartz_block")
                             ->setSoundType(SoundType::STONE)
                             ->setDestroyTime(0.8)
                             ->setNameAndDescriptionId(StringIDs::BlockOfQuartz, StringIDs::UsedAsADecoration)
                             ->setBaseItemTypeAndMaterial(14, 45);
    Block::registerBlock(155, L"quartz_block", quartzBlock);

    // Size: 0xC0u
    const BlockState* variant = quartzBlock->defaultBlockState()->setValue<QuartzBlock::Variant*>(
        QuartzBlock::VARIANT, QuartzBlock::Variant::DEFAULT);
    Block* quartzStairsBlock
        = (new StairBlock(variant))
              ->setIconName(L"stairsQuartz")
              ->setNameAndDescriptionId(StringIDs::QuartzStairs, StringIDs::UsedForCompactStaircases_1)
              ->setBaseItemTypeAndMaterial(16, 45);
    Block::registerBlock(156, L"quartz_stairs", quartzStairsBlock);

    // Size: 0xB0u
    Block* activatorRailBlock = (new PoweredRailBlock())
                                    ->setIconName(L"rail_activator")
                                    ->setDestroyTime(0.7)
                                    ->setSoundType(SoundType::METAL)
                                    ->setNameAndDescriptionId(StringIDs::ActivatorRail, 0xe397c8a)
                                    ->setBaseItemTypeAndMaterial(12, 9);
    Block::registerBlock(157, L"activator_rail", activatorRailBlock);

    // Size: 0xE8u
    Block* dropperBlock
        = (new DropperBlock())
              ->setIconName(L"dropper")
              ->setDestroyTime(3.5)
              ->setSoundType(SoundType::STONE)
              ->setNameAndDescriptionId(StringIDs::Dropper_1, StringIDs::UsedToHoldAndDropItemsOrPush)
              ->setBaseItemTypeAndMaterial(51, 0);
    Block::registerBlock(158, L"dropper", dropperBlock);

    // Size: 0x128u
    Block* stainedHardenedClayBlock
        = (new StainedHardenedClayBlock())
              ->setIconName(L"hardened_clay_stained")
              ->setDestroyTime(1.25)
              ->setExplodeable(7.0)
              ->setSoundType(SoundType::STONE)
              ->setNameAndDescriptionId(StringIDs::StainedTerracotta,
                                        StringIDs::ColorfulBlocksCraftedByDyeingTerracotta)
              ->setBaseItemTypeAndMaterial(41, 15);
    Block::registerBlock(159, L"stained_hardened_clay", stainedHardenedClayBlock);

    // Size: 0xE0u
    Block* stainedGlassPaneBlock
        = (new StainedGlassPaneBlock())
              ->setIconName(L"glass")
              ->setDestroyTime(0.3)
              ->setSoundType(SoundType::GLASS)
              ->setSemiTransparent()
              ->setNameAndDescriptionId(StringIDs::StainedGlassPane, StringIDs::CraftedFromStainedGlass)
              ->setBaseItemTypeAndMaterial(42, 34);
    Block::registerBlock(160, L"stained_glass_pane", stainedGlassPaneBlock);

    // Size: 0x110u
    Block* newLeafBlock = (new NewLeafBlock())
                              ->setIconName(L"leaves")
                              ->sendBlockData(3)
                              ->setNameAndDescriptionId(StringIDs::Leaves,
                                                        StringIDs::WhenBrokenSometimesDropsASaplingWhichCan);
    Block::registerBlock(161, L"leaves2", newLeafBlock);

    // Size: 0x110u
    Block* newLogBlock
        = (new NewLogBlock())
              ->setIconName(L"log")
              ->sendBlockData(15)
              ->setNameAndDescriptionId(StringIDs::Wood, StringIDs::ChoppedUsingAnAxeAndCanBeCrafted);
    Block::registerBlock(162, L"log2", newLogBlock);

    // Size: 0xC0u
    const BlockState* acaciaStairsBlockVariant
        = planksBlock->defaultBlockState()->setValue<PlanksBlock::Variant*>(PlanksBlock::VARIANT,
                                                                            PlanksBlock::Variant::ACACIA);
    Block* acaciaStairsBlock
        = (new StairBlock(acaciaStairsBlockVariant))
              ->setIconName(L"stairsWoodAcacia")
              ->sendBlockData(15)
              ->setNameAndDescriptionId(StringIDs::AcaciaWoodStairs, StringIDs::UsedForCompactStaircases_1)
              ->setBaseItemTypeAndMaterial(16, 42);
    Block::registerBlock(163, L"acacia_stairs", acaciaStairsBlock);

    // Size: 0xC0u
    const BlockState* darkOakStairsBlockVariant
        = planksBlock->defaultBlockState()->setValue<PlanksBlock::Variant*>(PlanksBlock::VARIANT,
                                                                            PlanksBlock::Variant::DARK_OAK);
    Block* darkOakStairsBlock
        = (new StairBlock(darkOakStairsBlockVariant))
              ->setIconName(L"stairsWoodDarkOak")
              ->sendBlockData(15)
              ->setNameAndDescriptionId(StringIDs::DarkOakWoodStairs, StringIDs::UsedForCompactStaircases_1)
              ->setBaseItemTypeAndMaterial(16, 43);
    Block::registerBlock(164, L"dark_oak_stairs", darkOakStairsBlock);

    // Size: 0xC0u
    Block* slimeBlock = (new SlimeBlock())
                            ->setSoundType(SoundType::SLIME_BLOCK)
                            ->setNameAndDescriptionId(StringIDs::SlimeBlock, 0xc6ece52)
                            ->setBaseItemTypeAndMaterial(32, 57)
                            ->setSemiTransparent();
    Block::registerBlock(165, L"slime", slimeBlock);

    // Size: 0xA8u
    Block* barrierBlock = (new BarrierBlock())
                              ->setIconName(L"barrier")
                              ->setNameAndDescriptionId(0x435e342, StringIDs::AnInvisibleButSolidBlock);
    Block::registerBlock(166, L"barrier", barrierBlock);

    // Size: 0xA8u
    Block* ironTrapDoorBlock
        = (new TrapDoorBlock(Material::METAL))
              ->setIconName(L"iron_trapdoor")
              ->setDestroyTime(5.0)
              ->setSoundType(SoundType::METAL)
              ->setNotCollectStatistics()
              ->sendBlockData(15)
              ->setNameAndDescriptionId(StringIDs::IronTrapdoor,
                                        StringIDs::IronTrapdoorsCanOnlyBeOpenedByRedstone)
              ->setBaseItemTypeAndMaterial(6, 25);
    Block::registerBlock(167, L"iron_trapdoor", ironTrapDoorBlock);

    // Size: 0xA8u
    Block* prismarineBlock
        = (new PrismarineBlock())
              ->setIconName(L"prismarine_rough")
              ->setDestroyTime(1.5)
              ->setExplodeable(10.0)
              ->setSoundType(SoundType::STONE)
              ->setNameAndDescriptionId(StringIDs::Prismarine, StringIDs::RareDecorativeStoneThatCanBeFoundIn)
              ->setBaseItemTypeAndMaterial(13, 13);
    Block::registerBlock(168, L"prismarine", prismarineBlock);

    // Size: 0xA8u
    Block* seaLanternBlock = (new SeaLanternBlock(Material::GLASS))
                                 ->setIconName(L"sea_lantern")
                                 ->setDestroyTime(0.3)
                                 ->setSoundType(SoundType::GLASS)
                                 ->setLightEmission(1.0)
                                 ->setNameAndDescriptionId(StringIDs::SeaLantern,
                                                           StringIDs::UnderwaterLightSourcesThatCanBeFoundIn)
                                 ->setBaseItemTypeAndMaterial(23, 54);
    Block::registerBlock(169, L"sea_lantern", seaLanternBlock);

    // Size: 0xB0u
    Block* hayBlock
        = (new HayBlock())
              ->setDestroyTime(0.5)
              ->setIconName(L"hay_block")
              ->setSoundType(SoundType::GRASS)
              ->setNameAndDescriptionId(StringIDs::HayBale, StringIDs::CanBeFedToHorsesDonkeysMulesAnd)
              ->setBaseItemTypeAndMaterial(32, 53);
    Block::registerBlock(170, L"hay_block", hayBlock);

    // Size: 0xA8u
    Block* woolCarpetBlock = (new WoolCarpetBlock())
                                 ->setIconName(L"woolCarpet")
                                 ->setDestroyTime(0.1)
                                 ->setSoundType(SoundType::WOOL)
                                 ->setLightBlock(0)
                                 ->setNameAndDescriptionId(StringIDs::Carpet, 0x1c5501b)
                                 ->setBaseItemTypeAndMaterial(40, 6);
    Block::registerBlock(171, L"carpet", woolCarpetBlock);

    // Size: 0xA8u
    Block* hardenedClayBlock
        = (new HardenedClayBlock())
              ->setIconName(L"hardened_clay")
              ->setDestroyTime(1.25)
              ->setExplodeable(7.0)
              ->setSoundType(SoundType::STONE)
              ->setNameAndDescriptionId(StringIDs::Terracotta, StringIDs::CreatedBySmeltingClayInAFurnace)
              ->setBaseItemTypeAndMaterial(41, 15);
    Block::registerBlock(172, L"hardened_clay", hardenedClayBlock);

    // Size: 0xA8u
    Block* coalBlock
        = (new BlockImpl(Material::STONE, MaterialColor::COLOR_BLACK))
              ->setIconName(L"coal_block")
              ->setDestroyTime(5.0)
              ->setExplodeable(10.0)
              ->setSoundType(SoundType::STONE)
              ->setNameAndDescriptionId(StringIDs::BlockOfCoal, StringIDs::ACompactWayOfStoringCoalCanBe)
              ->setBaseItemTypeAndMaterial(32, 49);
    Block::registerBlock(173, L"coal_block", coalBlock);

    // Size: 0xA8u
    Block* packedIceBlock
        = (new PackedIceBlock())
              ->setIconName(L"ice_packed")
              ->setDestroyTime(0.5)
              ->setSoundType(SoundType::GLASS)
              ->setNameAndDescriptionId(StringIDs::PackedIce, StringIDs::ASolidUnmeltableBlockOfIceThatCan);
    Block::registerBlock(174, L"packed_ice", packedIceBlock);

    // Size: 0xB0u
    Block* doublePlantBlock
        = (new DoublePlantBlock())
              ->setNameAndDescriptionId(StringIDs::DoublePlantBlock, StringIDs::ALargePlant)
              ->disableMipmap();
    Block::registerBlock(175, L"double_plant", doublePlantBlock);

    // Size: 0xB0u
    Block* standingBannerBlock
        = (new StandingBannerBlock())
              ->setIconName(L"planks_oak")
              ->setDestroyTime(1.0)
              ->setSoundType(SoundType::WOOD)
              ->setNotCollectStatistics()
              ->setNameAndDescriptionId(StringIDs::StandingBanner,
                                        StringIDs::AHighlyCustomizableFreeStandingDecorationCanBe);
    Block::registerBlock(176, L"standing_banner", standingBannerBlock);

    // Size: 0xB0u
    Block* wallBannerBlock
        = (new WallBannerBlock())
              ->setIconName(L"planks_oak")
              ->setDestroyTime(1.0)
              ->setSoundType(SoundType::WOOD)
              ->setNotCollectStatistics()
              ->setNameAndDescriptionId(StringIDs::HangingBanner,
                                        StringIDs::AHighlyCustomizableDecorationAttachedToABlock);
    Block::registerBlock(177, L"wall_banner", wallBannerBlock);

    // Size: 0xD0u
    Block* invertedDaylightDetectorBlock
        = (new DaylightDetectorBlock(true))
              ->setIconName(L"daylight_detector")
              ->setNameAndDescriptionId(StringIDs::DaylightSensor,
                                        StringIDs::ABlockThatOutputsARedstoneSignalBased);
    Block::registerBlock(178, L"daylight_detector_inverted", invertedDaylightDetectorBlock);

    // Size: 0xD0u
    Block* redSandStoneBlock
        = (new RedSandStoneBlock())
              ->setIconName(L"red_sandstone")
              ->setSoundType(SoundType::STONE)
              ->setDestroyTime(0.8)
              ->setNameAndDescriptionId(StringIDs::RedSandstone,
                                        StringIDs::RedColoredSandstoneItIsNotInfluencedBy)
              ->setBaseItemTypeAndMaterial(13, 48);
    Block::registerBlock(179, L"red_sandstone", redSandStoneBlock);

    // Size: 0xC0u
    const BlockState* redSandstoneStairsBlockVariant
        = redSandStoneBlock->defaultBlockState()->setValue<RedSandStoneBlock::Variant*>(
            RedSandStoneBlock::TYPE, RedSandStoneBlock::Variant::DEFAULT);
    Block* redSandstoneStairsBlock
        = (new StairBlock(redSandstoneStairsBlockVariant))
              ->setIconName(L"red_sandstone")
              ->setNameAndDescriptionId(StringIDs::RedSandstoneStairs, StringIDs::UsedForCompactStaircases_2)
              ->setBaseItemTypeAndMaterial(16, 48);
    Block::registerBlock(180, L"red_sandstone_stairs", redSandstoneStairsBlock);

    // Size: 0xB0u
    Block* fullNewStoneSlabBlock
        = (new FullNewStoneSlabBlock())
              ->setIconName(L"double_stone_slab2")
              ->setDestroyTime(2.0)
              ->setExplodeable(10.0)
              ->setSoundType(SoundType::STONE)
              ->setNameAndDescriptionId(StringIDs::RedSandstoneSlab,
                                        StringIDs::UsedForMakingLongStaircasesTwoSlabsPlaced_4)
              ->setBaseItemTypeAndMaterial(21, 48);
    Block::registerBlock(181, L"double_stone_slab2", fullNewStoneSlabBlock);

    // Size: 0xB0u
    Block* halfNewStoneSlabBlock
        = (new HalfNewStoneSlabBlock())
              ->setIconName(L"stone_slab2")
              ->setDestroyTime(2.0)
              ->setExplodeable(10.0)
              ->setSoundType(SoundType::STONE)
              ->setNameAndDescriptionId(StringIDs::RedSandstoneSlab,
                                        StringIDs::UsedForMakingLongStaircasesTwoSlabsPlaced_4)
              ->setBaseItemTypeAndMaterial(22, 48);
    Block::registerBlock(182, L"stone_slab2", halfNewStoneSlabBlock);

    // Size: 0xC0u
    Block* spruceFenceGateBlock
        = (new FenceGateBlock(L"planks_spruce", PlanksBlock::Variant::SPRUCE))
              ->setIconName(L"fenceGate")
              ->setDestroyTime(2.0)
              ->setExplodeable(5.0)
              ->setSoundType(SoundType::WOOD)
              ->sendBlockData(15)
              ->setNameAndDescriptionId(StringIDs::SpruceFenceGate,
                                        StringIDs::SimilarToADoorButUsedPrimarilyWithFences)
              ->setBaseItemTypeAndMaterial(47, 39);
    Block::registerBlock(183, L"spruce_fence_gate", spruceFenceGateBlock);

    // Size: 0xC0u
    Block* birchFenceGateBlock
        = (new FenceGateBlock(L"planks_birch", PlanksBlock::Variant::BIRCH))
              ->setIconName(L"fenceGate")
              ->setDestroyTime(2.0)
              ->setExplodeable(5.0)
              ->setSoundType(SoundType::WOOD)
              ->sendBlockData(15)
              ->setNameAndDescriptionId(StringIDs::BirchFenceGate,
                                        StringIDs::SimilarToADoorButUsedPrimarilyWithFences)
              ->setBaseItemTypeAndMaterial(47, 40);
    Block::registerBlock(184, L"birch_fence_gate", birchFenceGateBlock);

    // Size: 0xC0u
    Block* jungleFenceGateBlock
        = (new FenceGateBlock(L"planks_jungle", PlanksBlock::Variant::JUNGLE))
              ->setIconName(L"fenceGate")
              ->setDestroyTime(2.0)
              ->setExplodeable(5.0)
              ->setSoundType(SoundType::WOOD)
              ->sendBlockData(15)
              ->setNameAndDescriptionId(StringIDs::JungleFenceGate,
                                        StringIDs::SimilarToADoorButUsedPrimarilyWithFences)
              ->setBaseItemTypeAndMaterial(47, 41);
    Block::registerBlock(185, L"jungle_fence_gate", jungleFenceGateBlock);

    // Size: 0xC0u
    Block* darkOakFenceGateBlock
        = (new FenceGateBlock(L"planks_big_oak", PlanksBlock::Variant::DARK_OAK))
              ->setIconName(L"fenceGate")
              ->setDestroyTime(2.0)
              ->setExplodeable(5.0)
              ->setSoundType(SoundType::WOOD)
              ->sendBlockData(15)
              ->setNameAndDescriptionId(StringIDs::DarkOakFenceGate,
                                        StringIDs::SimilarToADoorButUsedPrimarilyWithFences)
              ->setBaseItemTypeAndMaterial(47, 42);
    Block::registerBlock(186, L"dark_oak_fence_gate", darkOakFenceGateBlock);

    // Size: 0xC0u
    Block* acaciaFenceGateBlock
        = (new FenceGateBlock(L"planks_acacia", PlanksBlock::Variant::ACACIA))
              ->setIconName(L"fenceGate")
              ->setDestroyTime(2.0)
              ->setExplodeable(5.0)
              ->setSoundType(SoundType::WOOD)
              ->sendBlockData(15)
              ->setNameAndDescriptionId(StringIDs::AcaciaFenceGate,
                                        StringIDs::SimilarToADoorButUsedPrimarilyWithFences)
              ->setBaseItemTypeAndMaterial(47, 43);
    Block::registerBlock(187, L"acacia_fence_gate", acaciaFenceGateBlock);

    // Size: 0xC0u
    Block* spruceFenceBlock
        = (new FenceBlock(L"planks_spruce", Material::WOOD, PlanksBlock::Variant::SPRUCE->getMaterialColor()))
              ->setDestroyTime(2.0)
              ->setExplodeable(5.0)
              ->setSoundType(SoundType::WOOD)
              ->setNameAndDescriptionId(StringIDs::SpruceFence, StringIDs::UsedAsABarrierThatCannotBeJumped)
              ->setBaseItemTypeAndMaterial(29, 39);
    Block::registerBlock(188, L"spruce_fence", spruceFenceBlock);

    // Size: 0xC0u
    Block* birchFenceBlock
        = (new FenceBlock(L"planks_birch", Material::WOOD, PlanksBlock::Variant::BIRCH->getMaterialColor()))
              ->setDestroyTime(2.0)
              ->setExplodeable(5.0)
              ->setSoundType(SoundType::WOOD)
              ->setNameAndDescriptionId(StringIDs::BirchFence, StringIDs::UsedAsABarrierThatCannotBeJumped)
              ->setBaseItemTypeAndMaterial(29, 40);
    Block::registerBlock(189, L"birch_fence", birchFenceBlock);

    // Size: 0xC0u
    Block* jungleFenceBlock
        = (new FenceBlock(L"planks_jungle", Material::WOOD, PlanksBlock::Variant::JUNGLE->getMaterialColor()))
              ->setDestroyTime(2.0)
              ->setExplodeable(5.0)
              ->setSoundType(SoundType::WOOD)
              ->setNameAndDescriptionId(StringIDs::JungleFence, StringIDs::UsedAsABarrierThatCannotBeJumped)
              ->setBaseItemTypeAndMaterial(29, 41);
    Block::registerBlock(190, L"jungle_fence", jungleFenceBlock);

    // Size: 0xC0u
    Block* darkOakFenceBlock
        = (new FenceBlock(L"planks_big_oak", Material::WOOD,
                          PlanksBlock::Variant::DARK_OAK->getMaterialColor()))
              ->setDestroyTime(2.0)
              ->setExplodeable(5.0)
              ->setSoundType(SoundType::WOOD)
              ->setNameAndDescriptionId(StringIDs::DarkOakFence, StringIDs::UsedAsABarrierThatCannotBeJumped)
              ->setBaseItemTypeAndMaterial(29, 42);
    Block::registerBlock(191, L"dark_oak_fence", darkOakFenceBlock);

    // Size: 0xC0u
    Block* acaciaFenceBlock
        = (new FenceBlock(L"planks_acacia", Material::WOOD, PlanksBlock::Variant::ACACIA->getMaterialColor()))
              ->setDestroyTime(2.0)
              ->setExplodeable(5.0)
              ->setSoundType(SoundType::WOOD)
              ->setNameAndDescriptionId(StringIDs::AcaciaFence, StringIDs::UsedAsABarrierThatCannotBeJumped)
              ->setBaseItemTypeAndMaterial(29, 43);
    Block::registerBlock(192, L"acacia_fence", acaciaFenceBlock);

    // Size: 0xC8u
    Block* spruceDoorBlock
        = (new DoorBlock(Material::WOOD))
              ->setIconName(L"door_spruce")
              ->setDestroyTime(3.0)
              ->setSoundType(SoundType::WOOD)
              ->setNotCollectStatistics()
              ->sendBlockData(15)
              ->setNameAndDescriptionId(StringIDs::SpruceDoor_1,
                                        StringIDs::WoodenDoorsAreActivatedByUsingHittingmOr);
    Block::registerBlock(193, L"spruce_door", spruceDoorBlock);

    // Size: 0xC8u
    Block* birchDoorBlock
        = (new DoorBlock(Material::WOOD))
              ->setIconName(L"door_birch")
              ->setDestroyTime(3.0)
              ->setSoundType(SoundType::WOOD)
              ->setNotCollectStatistics()
              ->sendBlockData(15)
              ->setNameAndDescriptionId(StringIDs::BirchDoor_1,
                                        StringIDs::WoodenDoorsAreActivatedByUsingHittingmOr);
    Block::registerBlock(194, L"birch_door", birchDoorBlock);

    // Size: 0xC8u
    Block* jungleDoorBlock
        = (new DoorBlock(Material::WOOD))
              ->setIconName(L"door_jungle")
              ->setDestroyTime(3.0)
              ->setSoundType(SoundType::WOOD)
              ->setNotCollectStatistics()
              ->sendBlockData(15)
              ->setNameAndDescriptionId(StringIDs::JungleDoor_1,
                                        StringIDs::WoodenDoorsAreActivatedByUsingHittingmOr);
    Block::registerBlock(195, L"jungle_door", jungleDoorBlock);

    // Size: 0xC8u
    Block* acaciaDoorBlock
        = (new DoorBlock(Material::WOOD))
              ->setIconName(L"door_acacia")
              ->setDestroyTime(3.0)
              ->setSoundType(SoundType::WOOD)
              ->setNotCollectStatistics()
              ->sendBlockData(15)
              ->setNameAndDescriptionId(StringIDs::AcaciaDoor_1,
                                        StringIDs::WoodenDoorsAreActivatedByUsingHittingmOr);
    Block::registerBlock(196, L"acacia_door", acaciaDoorBlock);

    // Size: 0xC8u
    Block* darkOakDoorBlock
        = (new DoorBlock(Material::WOOD))
              ->setIconName(L"door_dark_oak")
              ->setDestroyTime(3.0)
              ->setSoundType(SoundType::WOOD)
              ->setNotCollectStatistics()
              ->sendBlockData(15)
              ->setNameAndDescriptionId(StringIDs::DarkOakDoor_1,
                                        StringIDs::WoodenDoorsAreActivatedByUsingHittingmOr);
    Block::registerBlock(197, L"dark_oak_door", darkOakDoorBlock);

    // Size: 0xA8u
    Block* endRodBlock
        = (new EndRodBlock())
              ->setIconName(L"end_rod")
              ->setDestroyTime(0.0)
              ->setLightEmission(0.9375)
              ->setSoundType(SoundType::WOOD)
              ->setNameAndDescriptionId(StringIDs::EndRod, StringIDs::ADecorativeLightSourceFoundInEndCities);
    Block::registerBlock(198, L"end_rod", endRodBlock);

    // Size: 0xA8u
    Block* chorusPlantBlock
        = (new ChorusPlantBlock())
              ->setIconName(L"chorus_flower_plant")
              ->setDestroyTime(0.4)
              ->setSoundType(SoundType::WOOD)
              ->setNameAndDescriptionId(StringIDs::ChorusPlant,
                                        StringIDs::GrowsFromChorusFlowersSometimesDropsChorusFruit);
    Block::registerBlock(199, L"chorus_plant", chorusPlantBlock);

    // Size: 0xC0u
    Block* chorusFlowerBlock
        = (new ChorusFlowerBlock())
              ->setIconName(L"chorus_flower")
              ->setDestroyTime(0.4)
              ->setSoundType(SoundType::WOOD)
              ->setNameAndDescriptionId(StringIDs::ChorusFlower, StringIDs::CanBePlantedOnEndStoneToGrow);
    Block::registerBlock(200, L"chorus_flower", chorusFlowerBlock);

    // Size: 0xA8u
    Block* purpurBlock
        = (new BlockImpl(Material::STONE, MaterialColor::COLOR_MAGENTA))
              ->setIconName(L"purpur_block")
              ->setDestroyTime(1.5)
              ->setExplodeable(10.0)
              ->setSoundType(SoundType::STONE)
              ->setNameAndDescriptionId(StringIDs::PurpurBlock, StringIDs::CanBeMinedWithAPickaxeOrCrafted)
              ->setBaseItemTypeAndMaterial(32, 62);
    Block::registerBlock(201, L"purpur_block", purpurBlock);

    // Size: 0xC8u
    Block* purpurPillarBlock
        = (new RotatedPillarBlockImpl(Material::STONE, MaterialColor::COLOR_MAGENTA))
              ->setIconTopName(L"purpur_pillar_top")  // TODO
              ->setIconName(L"purpur_pillar")
              ->setDestroyTime(1.5)
              ->setExplodeable(10.0)
              ->setSoundType(SoundType::STONE)
              ->setNameAndDescriptionId(0xa7b0f2a, StringIDs::CanBeMinedWithAPickaxeOrCraftedPurpurSlabs)
              ->setBaseItemTypeAndMaterial(14, 62);
    Block::registerBlock(202, L"purpur_pillar", purpurPillarBlock);

    // Size: 0xC0u
    Block* purpurStairsBlock = (new StairBlock(purpurBlock->defaultBlockState()))
                                   ->setNameAndDescriptionId(StringIDs::PurpurStairs, 0xdda0c93)
                                   ->setBaseItemTypeAndMaterial(16, 62);
    Block::registerBlock(203, L"purpur_stairs", purpurStairsBlock);

    // Size: 0xA8u
    Block* purpurSlabBlockFull
        = (new PurpurSlabBlockFull())
              ->setDestroyTime(2.0)
              ->setIconName(L"purpur_block")
              ->setExplodeable(10.0)
              ->setSoundType(SoundType::STONE)
              ->setNameAndDescriptionId(StringIDs::PurpurSlab,
                                        StringIDs::UsedForMakingLongStaircasesTwoSlabsPlaced_1)
              ->setBaseItemTypeAndMaterial(21, 62);
    Block::registerBlock(204, L"purpur_double_slab", purpurSlabBlockFull);

    // Size: 0xA8u
    Block* purpurSlabBlockHalf
        = (new PurpurSlabBlockHalf())
              ->setDestroyTime(2.0)
              ->setIconName(L"purpur_block")
              ->setExplodeable(10.0)
              ->setSoundType(SoundType::STONE)
              ->setNameAndDescriptionId(StringIDs::PurpurSlab,
                                        StringIDs::UsedForMakingLongStaircasesTwoSlabsPlaced_1)
              ->setBaseItemTypeAndMaterial(22, 62);
    Block::registerBlock(205, L"purpur_slab", purpurSlabBlockHalf);

    // Size: 0xA8u
    Block* endBricksBlock = (new BlockImpl(Material::STONE, MaterialColor::SAND))
                                ->setSoundType(SoundType::STONE)
                                ->setDestroyTime(0.8)
                                ->setIconName(L"end_bricks")
                                ->setNameAndDescriptionId(StringIDs::EndStoneBricks,
                                                          StringIDs::CraftedFromEndStoneCanBeUsedAsDecoration)
                                ->setBaseItemTypeAndMaterial(14, 33);
    Block::registerBlock(206, L"end_bricks", endBricksBlock);

    // Size: 0x110u
    Block* beetrootBlock
        = (new BeetrootBlock())
              ->setIconName(L"beetroots")
              ->disableMipmap()
              ->setNameAndDescriptionId(StringIDs::Beetroots,
                                        StringIDs::Restores05IconShank01WhenEatenThisCanPlantedInFarmland);
    Block::registerBlock(207, L"beetroots", beetrootBlock);

    // Size: 0xB0u
    Block* grassPathBlock
        = (new GrassPathBlock())
              ->setDestroyTime(0.65)
              ->setSoundType(SoundType::GRASS)
              ->setIconName(L"grass_path")
              ->setNotCollectStatistics()
              ->setNameAndDescriptionId(StringIDs::GrassPath, StringIDs::ADecorativeBlockThatCanBeCreatedBy);
    Block* notFullHeight_GrassPath = grassPathBlock;
    Block::registerBlock(208, L"grass_path", grassPathBlock);

    // Size: 0xB0u
    Block* endGatewayBlock
        = (new EndGatewayBlock(Material::PORTAL))
              ->setIconName(L"stone")
              ->setDestroyTime(3.4028e38)
              ->setExplodeable(6000000.0)
              ->setNameAndDescriptionId(StringIDs::EndGateway,
                                        StringIDs::GeneratedWhenEnderDragonIsKilledThrowingAn);
    Block::registerBlock(209, L"end_gateway", endGatewayBlock);

    // Size: 0xD8u
    Block* frostedIceBlock
        = (new FrostedIceBlock())
              ->setDestroyTime(0.5)
              ->setLightBlock(3)
              ->setSoundType(SoundType::GLASS)
              ->setNameAndDescriptionId(StringIDs::FrostedIce, StringIDs::ATypeOfIceThatMeltsQuickly);
    Block::registerBlock(212, L"frosted_ice", frostedIceBlock);

    // Size: 0xA8u
    Block* magmaBlock
        = (new MagmaBlock())
              ->setDestroyTime(0.5)
              ->setSoundType(SoundType::STONE)
              ->setIconName(L"magma")
              ->setNameAndDescriptionId(StringIDs::MagmaBlock, StringIDs::CausesFireDamageWhenYouStandOnIt)
              ->setBaseItemTypeAndMaterial(32, 61);
    Block::registerBlock(213, L"magma", magmaBlock);

    // Size: 0xA8u
    Block* netherWartBlock = (new BlockImpl(Material::GRASS, MaterialColor::COLOR_RED))
                                 ->setDestroyTime(1.0)
                                 ->setSoundType(SoundType::WOOD)
                                 ->setIconName(L"nether_wart_block")
                                 ->setNameAndDescriptionId(StringIDs::NetherWartBlock,
                                                           StringIDs::ADecorativeBlockCraftedFromNetherWart)
                                 ->setBaseItemTypeAndMaterial(32, 60);
    Block::registerBlock(214, L"nether_wart_block", netherWartBlock);

    // Size: 0xA8u
    Block* redNetherBrickBlock
        = (new NetherBrickBlock())
              ->setDestroyTime(2.0)
              ->setExplodeable(10.0)
              ->setSoundType(SoundType::STONE)
              ->setIconName(L"red_nether_brick")
              ->setNameAndDescriptionId(StringIDs::RedNetherBrick,
                                        StringIDs::CraftedFromNetherWartAndNetherBrickCan)
              ->setBaseItemTypeAndMaterial(14, 32);
    Block::registerBlock(215, L"red_nether_brick", redNetherBrickBlock);

    // Size: 0xB0u
    Block* boneBlock = (new BoneBlock())
                           ->setIconName(L"bone_block")
                           ->setNameAndDescriptionId(StringIDs::BoneBlock,
                                                     StringIDs::CraftedFromBoneMealOrFoundUndergroundIn)
                           ->setBaseItemTypeAndMaterial(13, 59);
    Block::registerBlock(216, L"bone_block", boneBlock);

    // Size: 0xA8u
    Block* structureVoidBlock = (new StructureVoidBlock())
                                    ->setIconName(L"structure_block")
                                    ->setNameAndDescriptionId(0xFFFFFFFF, 0xFFFFFFFF);
    Block::registerBlock(217, L"structure_void", structureVoidBlock);

    // Size: 0xD0u
    Block* observerBlock = (new ObserverBlock())
                               ->setDestroyTime(3.0)
                               ->setNameAndDescriptionId(
                                   StringIDs::Observer, StringIDs::EmitsARedstoneSignalWhenAdjacentBlocksAre);
    Block::registerBlock(218, L"observer", observerBlock);

    // Size: 0xB8u
    Block* whiteShulkerBoxBlock = (new ShulkerBoxBlock(DyeColor::WHITE))
                                      ->setIconName(L"shulker_top")
                                      ->setDestroyTime(2.0)
                                      ->setSoundType(SoundType::STONE)
                                      ->setNameAndDescriptionId(StringIDs::WhiteShulkerBox,
                                                                StringIDs::ASpecialKindOfChestThatCanContain)
                                      ->setBaseItemTypeAndMaterial(36, 70);
    Block::registerBlock(219, L"white_shulker_box", whiteShulkerBoxBlock);

    // Size: 0xB8u
    Block* orangeShulkerBoxBlock = (new ShulkerBoxBlock(DyeColor::ORANGE))
                                       ->setIconName(L"shulker_top")
                                       ->setDestroyTime(2.0)
                                       ->setSoundType(SoundType::STONE)
                                       ->setNameAndDescriptionId(StringIDs::OrangeShulkerBox,
                                                                 StringIDs::ASpecialKindOfChestThatCanContain)
                                       ->setBaseItemTypeAndMaterial(36, 70);
    Block::registerBlock(220, L"orange_shulker_box", orangeShulkerBoxBlock);

    // Size: 0xB8u
    Block* magentaShulkerBoxBlock
        = (new ShulkerBoxBlock(DyeColor::MAGENTA))
              ->setIconName(L"shulker_top")
              ->setDestroyTime(2.0)
              ->setSoundType(SoundType::STONE)
              ->setNameAndDescriptionId(StringIDs::MagentaShulkerBox,
                                        StringIDs::ASpecialKindOfChestThatCanContain)
              ->setBaseItemTypeAndMaterial(36, 70);
    Block::registerBlock(221, L"magenta_shulker_box", magentaShulkerBoxBlock);

    // Size: 0xB8u
    Block* lightBlueShulkerBoxBlock
        = (new ShulkerBoxBlock(DyeColor::LIGHT_BLUE))
              ->setIconName(L"shulker_top")
              ->setDestroyTime(2.0)
              ->setSoundType(SoundType::STONE)
              ->setNameAndDescriptionId(StringIDs::LightBlueShulkerBox,
                                        StringIDs::ASpecialKindOfChestThatCanContain)
              ->setBaseItemTypeAndMaterial(36, 70);
    Block::registerBlock(222, L"light_blue_shulker_box", lightBlueShulkerBoxBlock);

    // Size: 0xB8u
    Block* yellowShulkerBoxBlock = (new ShulkerBoxBlock(DyeColor::YELLOW))
                                       ->setIconName(L"shulker_top")
                                       ->setDestroyTime(2.0)
                                       ->setSoundType(SoundType::STONE)
                                       ->setNameAndDescriptionId(StringIDs::YellowShulkerBox,
                                                                 StringIDs::ASpecialKindOfChestThatCanContain)
                                       ->setBaseItemTypeAndMaterial(36, 70);
    Block::registerBlock(223, L"yellow_shulker_box", yellowShulkerBoxBlock);

    // Size: 0xB8u
    Block* limeShulkerBoxBlock = (new ShulkerBoxBlock(DyeColor::LIME))
                                     ->setIconName(L"shulker_top")
                                     ->setDestroyTime(2.0)
                                     ->setSoundType(SoundType::STONE)
                                     ->setNameAndDescriptionId(StringIDs::LimeShulkerBox,
                                                               StringIDs::ASpecialKindOfChestThatCanContain)
                                     ->setBaseItemTypeAndMaterial(36, 70);
    Block::registerBlock(224, L"lime_shulker_box", limeShulkerBoxBlock);

    // Size: 0xB8u
    Block* pinkShulkerBoxBlock = (new ShulkerBoxBlock(DyeColor::PINK))
                                     ->setIconName(L"shulker_top")
                                     ->setDestroyTime(2.0)
                                     ->setSoundType(SoundType::STONE)
                                     ->setNameAndDescriptionId(StringIDs::PinkShulkerBox,
                                                               StringIDs::ASpecialKindOfChestThatCanContain)
                                     ->setBaseItemTypeAndMaterial(36, 70);
    Block::registerBlock(225, L"pink_shulker_box", pinkShulkerBoxBlock);

    // Size: 0xB8u
    Block* grayShulkerBoxBlock = (new ShulkerBoxBlock(DyeColor::GRAY))
                                     ->setIconName(L"shulker_top")
                                     ->setDestroyTime(2.0)
                                     ->setSoundType(SoundType::STONE)
                                     ->setNameAndDescriptionId(StringIDs::GrayShulkerBox,
                                                               StringIDs::ASpecialKindOfChestThatCanContain)
                                     ->setBaseItemTypeAndMaterial(36, 70);
    Block::registerBlock(226, L"gray_shulker_box", grayShulkerBoxBlock);

    // Size: 0xB8u
    Block* silverShulkerBoxBlock = (new ShulkerBoxBlock(DyeColor::SILVER))
                                       ->setIconName(L"shulker_top")
                                       ->setDestroyTime(2.0)
                                       ->setSoundType(SoundType::STONE)
                                       ->setNameAndDescriptionId(StringIDs::LightGrayShulkerBox,
                                                                 StringIDs::ASpecialKindOfChestThatCanContain)
                                       ->setBaseItemTypeAndMaterial(36, 70);
    Block::registerBlock(227, L"silver_shulker_box", silverShulkerBoxBlock);

    // Size: 0xB8u
    Block* cyanShulkerBoxBlock = (new ShulkerBoxBlock(DyeColor::CYAN))
                                     ->setIconName(L"shulker_top")
                                     ->setDestroyTime(2.0)
                                     ->setSoundType(SoundType::STONE)
                                     ->setNameAndDescriptionId(StringIDs::CyanShulkerBox,
                                                               StringIDs::ASpecialKindOfChestThatCanContain)
                                     ->setBaseItemTypeAndMaterial(36, 70);
    Block::registerBlock(228, L"cyan_shulker_box", cyanShulkerBoxBlock);

    // Size: 0xB8u
    Block* purpleShulkerBoxBlock = (new ShulkerBoxBlock(DyeColor::PURPLE))
                                       ->setIconName(L"shulker_top")
                                       ->setDestroyTime(2.0)
                                       ->setSoundType(SoundType::STONE)
                                       ->setNameAndDescriptionId(StringIDs::PurpleShulkerBox,
                                                                 StringIDs::ASpecialKindOfChestThatCanContain)
                                       ->setBaseItemTypeAndMaterial(36, 70);
    Block::registerBlock(229, L"purple_shulker_box", purpleShulkerBoxBlock);

    // Size: 0xB8u
    Block* blueShulkerBoxBlock = (new ShulkerBoxBlock(DyeColor::BLUE))
                                     ->setIconName(L"shulker_top")
                                     ->setDestroyTime(2.0)
                                     ->setSoundType(SoundType::STONE)
                                     ->setNameAndDescriptionId(StringIDs::BlueShulkerBox,
                                                               StringIDs::ASpecialKindOfChestThatCanContain)
                                     ->setBaseItemTypeAndMaterial(36, 70);
    Block::registerBlock(230, L"blue_shulker_box", blueShulkerBoxBlock);

    // Size: 0xB8u
    Block* brownShulkerBoxBlock = (new ShulkerBoxBlock(DyeColor::BROWN))
                                      ->setIconName(L"shulker_top")
                                      ->setDestroyTime(2.0)
                                      ->setSoundType(SoundType::STONE)
                                      ->setNameAndDescriptionId(StringIDs::BrownShulkerBox,
                                                                StringIDs::ASpecialKindOfChestThatCanContain)
                                      ->setBaseItemTypeAndMaterial(36, 70);
    Block::registerBlock(231, L"brown_shulker_box", brownShulkerBoxBlock);

    // Size: 0xB8u
    Block* greenShulkerBoxBlock = (new ShulkerBoxBlock(DyeColor::GREEN))
                                      ->setIconName(L"shulker_top")
                                      ->setDestroyTime(2.0)
                                      ->setSoundType(SoundType::STONE)
                                      ->setNameAndDescriptionId(StringIDs::GreenShulkerBox,
                                                                StringIDs::ASpecialKindOfChestThatCanContain)
                                      ->setBaseItemTypeAndMaterial(36, 70);
    Block::registerBlock(232, L"green_shulker_box", greenShulkerBoxBlock);

    // Size: 0xB8u
    Block* redShulkerBoxBlock = (new ShulkerBoxBlock(DyeColor::RED))
                                    ->setIconName(L"shulker_top")
                                    ->setDestroyTime(2.0)
                                    ->setSoundType(SoundType::STONE)
                                    ->setNameAndDescriptionId(StringIDs::RedShulkerBox,
                                                              StringIDs::ASpecialKindOfChestThatCanContain)
                                    ->setBaseItemTypeAndMaterial(36, 70);
    Block::registerBlock(233, L"red_shulker_box", redShulkerBoxBlock);

    // Size: 0xB8u
    Block* blackShulkerBoxBlock
        = (new ShulkerBoxBlock(DyeColor::BLACK))
              ->setIconName(L"shulker_top")
              ->setDestroyTime(2.0)
              ->setSoundType(SoundType::STONE)
              ->setNameAndDescriptionId(0xc17c633, StringIDs::ASpecialKindOfChestThatCanContain)
              ->setBaseItemTypeAndMaterial(36, 70);
    Block::registerBlock(234, L"black_shulker_box", blackShulkerBoxBlock);

    // Size: 0xA8u
    Block* whiteGlazedTerracottaBlock
        = (new GlazedTerracottaBlock(DyeColor::WHITE))
              ->setIconName(L"glazed_terracotta_white")
              ->setNameAndDescriptionId(StringIDs::WhiteGlazedTerracotta,
                                        StringIDs::ADecorativeBlockCreatedByBakingWhiteTerracotta);
    Block::registerBlock(235, L"white_glazed_terracotta", whiteGlazedTerracottaBlock);

    // Size: 0xA8u
    Block* orangeGlazedTerracottaBlock
        = (new GlazedTerracottaBlock(DyeColor::ORANGE))
              ->setIconName(L"glazed_terracotta_orange")
              ->setNameAndDescriptionId(StringIDs::OrangeGlazedTerracotta,
                                        StringIDs::ADecorativeBlockCreatedByBakingOrangeTerracotta);
    Block::registerBlock(236, L"orange_glazed_terracotta", orangeGlazedTerracottaBlock);

    // Size: 0xA8u
    Block* magentaGlazedTerracottaBlock
        = (new GlazedTerracottaBlock(DyeColor::MAGENTA))
              ->setIconName(L"glazed_terracotta_magenta")
              ->setNameAndDescriptionId(StringIDs::MagentaGlazedTerracotta, 0x7b8dd58);
    Block::registerBlock(237, L"magenta_glazed_terracotta", magentaGlazedTerracottaBlock);

    // Size: 0xA8u
    Block* lightBlueGlazedTerracottaBlock
        = (new GlazedTerracottaBlock(DyeColor::LIGHT_BLUE))
              ->setIconName(L"glazed_terracotta_light_blue")
              ->setNameAndDescriptionId(StringIDs::LightBlueGlazedTerracotta,
                                        StringIDs::ADecorativeBlockCreatedByBakingLightBlue);
    Block::registerBlock(238, L"light_blue_glazed_terracotta", lightBlueGlazedTerracottaBlock);

    // Size: 0xA8u
    Block* yellowGlazedTerracottaBlock
        = (new GlazedTerracottaBlock(DyeColor::YELLOW))
              ->setIconName(L"glazed_terracotta_yellow")
              ->setNameAndDescriptionId(StringIDs::YellowGlazedTerracotta,
                                        StringIDs::ADecorativeBlockCreatedByBakingYellowTerracotta);
    Block::registerBlock(239, L"yellow_glazed_terracotta", yellowGlazedTerracottaBlock);

    // Size: 0xA8u
    Block* limeGlazedTerracottaBlock
        = (new GlazedTerracottaBlock(DyeColor::LIME))
              ->setIconName(L"glazed_terracotta_lime")
              ->setNameAndDescriptionId(StringIDs::LimeGlazedTerracotta,
                                        StringIDs::ADecorativeBlockCreatedByBakingLimeTerracotta);
    Block::registerBlock(240, L"lime_glazed_terracotta", limeGlazedTerracottaBlock);

    // Size: 0xA8u
    Block* pinkGlazedTerracottaBlock
        = (new GlazedTerracottaBlock(DyeColor::PINK))
              ->setIconName(L"glazed_terracotta_pink")
              ->setNameAndDescriptionId(StringIDs::PinkGlazedTerracotta,
                                        StringIDs::ADecorativeBlockCreatedByBakingPinkTerracotta);
    Block::registerBlock(241, L"pink_glazed_terracotta", pinkGlazedTerracottaBlock);

    // Size: 0xA8u
    Block* grayGlazedTerracottaBlock
        = (new GlazedTerracottaBlock(DyeColor::GRAY))
              ->setIconName(L"glazed_terracotta_gray")
              ->setNameAndDescriptionId(0xa10f3e, StringIDs::ADecorativeBlockCreatedByBakingGrayTerracotta);
    Block::registerBlock(242, L"gray_glazed_terracotta", grayGlazedTerracottaBlock);

    // Size: 0xA8u
    Block* silverGlazedTerracottaBlock
        = (new GlazedTerracottaBlock(DyeColor::SILVER))
              ->setIconName(L"glazed_terracotta_silver")
              ->setNameAndDescriptionId(StringIDs::LightGrayGlazedTerracotta,
                                        StringIDs::ADecorativeBlockCreatedByBakingLightGray);
    Block::registerBlock(243, L"silver_glazed_terracotta", silverGlazedTerracottaBlock);

    // Size: 0xA8u
    Block* cyanGlazedTerracottaBlock
        = (new GlazedTerracottaBlock(DyeColor::CYAN))
              ->setIconName(L"glazed_terracotta_cyan")
              ->setNameAndDescriptionId(0x22f7636, StringIDs::ADecorativeBlockCreatedByBakingCyanTerracotta);
    Block::registerBlock(244, L"cyan_glazed_terracotta", cyanGlazedTerracottaBlock);

    // Size: 0xA8u
    Block* purpleGlazedTerracottaBlock
        = (new GlazedTerracottaBlock(DyeColor::PURPLE))
              ->setIconName(L"glazed_terracotta_purple")
              ->setNameAndDescriptionId(StringIDs::PurpleGlazedTerracotta,
                                        StringIDs::ADecorativeBlockCreatedByBakingPurpleTerracotta);
    Block::registerBlock(245, L"purple_glazed_terracotta", purpleGlazedTerracottaBlock);

    // Size: 0xA8u
    Block* blueGlazedTerracottaBlock
        = (new GlazedTerracottaBlock(DyeColor::BLUE))
              ->setIconName(L"glazed_terracotta_blue")
              ->setNameAndDescriptionId(StringIDs::BlueGlazedTerracotta,
                                        StringIDs::ADecorativeBlockCreatedByBakingBlueTerracotta);
    Block::registerBlock(246, L"blue_glazed_terracotta", blueGlazedTerracottaBlock);

    // Size: 0xA8u
    Block* brownGlazedTerracottaBlock
        = (new GlazedTerracottaBlock(DyeColor::BROWN))
              ->setIconName(L"glazed_terracotta_brown")
              ->setNameAndDescriptionId(StringIDs::BrownGlazedTerracotta,
                                        StringIDs::ADecorativeBlockCreatedByBakingBrownTerracotta);
    Block::registerBlock(247, L"brown_glazed_terracotta", brownGlazedTerracottaBlock);

    // Size: 0xA8u
    Block* greenGlazedTerracottaBlock
        = (new GlazedTerracottaBlock(DyeColor::GREEN))
              ->setIconName(L"glazed_terracotta_green")
              ->setNameAndDescriptionId(0x80fc468, StringIDs::ADecorativeBlockCreatedByBakingGreenTerracotta);
    Block::registerBlock(248, L"green_glazed_terracotta", greenGlazedTerracottaBlock);

    // Size: 0xA8u
    Block* redGlazedTerracottaBlock
        = (new GlazedTerracottaBlock(DyeColor::RED))
              ->setIconName(L"glazed_terracotta_red")
              ->setNameAndDescriptionId(StringIDs::RedGlazedTerracotta,
                                        StringIDs::ADecorativeBlockCreatedByBakingRedTerracotta);
    Block::registerBlock(249, L"red_glazed_terracotta", redGlazedTerracottaBlock);

    // Size: 0xA8u
    Block* blackGlazedTerracottaBlock
        = (new GlazedTerracottaBlock(DyeColor::BLACK))
              ->setIconName(L"glazed_terracotta_black")
              ->setNameAndDescriptionId(StringIDs::BlackGlazedTerracotta,
                                        StringIDs::ADecorativeBlockCreatedByBakingBlackTerracotta);
    Block::registerBlock(250, L"black_glazed_terracotta", blackGlazedTerracottaBlock);

    // Size: 0x128u
    Block* concreteBlock
        = (new ColoredBlock(Material::STONE))
              ->setDestroyTime(1.8)
              ->setSoundType(SoundType::STONE)
              ->setIconName(L"concrete")
              ->setNameAndDescriptionId(StringIDs::BlackConcrete, StringIDs::CanBeMinedWithAPickaxeOrCreated);
    Block::registerBlock(251, L"concrete", concreteBlock);

    // Size: 0x128u
    Block* concretePowderBlock
        = (new ConcretePowderBlock())
              ->setDestroyTime(0.5)
              ->setSoundType(SoundType::SAND)
              ->setIconName(L"concrete_powder")
              ->setNameAndDescriptionId(StringIDs::BlackConcretePowder,
                                        StringIDs::TurnsIntoConcreteAfterComingIntoContactWith)
              ->setBaseItemTypeAndMaterial(57, 69);
    Block::registerBlock(252, L"concrete_powder", concretePowderBlock);

    // Size: 0xA8u
    Block* structureBlock = (new StructureBlock())
                                ->setIconName(L"structure_block")
                                ->setIndestructible()
                                ->setExplodeable(6000000.0)
                                ->setNameAndDescriptionId(0xFFFFFFFF, 0xFFFFFFFF);
    Block::registerBlock(255, L"structure_block", structureBlock);

    // TODO: nullsub
    // TODO: registry stuff
    // TODO: I think this is for partial height blocks (e.g farmland, slabs, grass path), but it does some
    // dynamic cast bullshit that I don't want to touch
}
