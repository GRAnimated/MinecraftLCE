#include "net/minecraft/world/level/block/Block.h"

#include "net/minecraft/client/resources/IdMapper.h"
#include "net/minecraft/core/Direction.h"
#include "net/minecraft/stats/Stats.h"
#include "net/minecraft/world/ArrayWithLength.h"

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
#include "net/minecraft/world/level/block/state/DirectionProperty.h"
#include "net/minecraft/world/level/dimension/Dimension.h"
#include "net/minecraft/world/level/gamemode/GameMode.h"
#include "net/minecraft/world/level/material/Material.h"
#include "net/minecraft/world/phys/AABB.h"
#include "net/minecraft/world/phys/HitResult.h"

#include <cfloat>
#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>

const AABB* Block::defaultBlockShape = AABB::newPermanent(0.0, 0.0, 0.0, 1.0, 1.0, 1.0);

Block::Block(Material* material) {
    init(material, material->getColor());
}

Block::Block(Material* material, const MaterialColor* color) {
    init(material, color);
}

Block::~Block() {}

const BlockState* Block::defaultBlockState() {
    return m_blockState;
}

void Block::registerDefaultState(const BlockState* state) {
    m_blockState = state;
}

void Block::init(Material* material, const MaterialColor* color) {
    m_fieldA0 = 0;
    m_explosionResistance = 0.0f;
    m_collectStatistics = true;

    m_soundType = SoundType::STONE;

    m_destroyTime = 0.0f;
    m_ticking = false;
    m_silkTouchable = false;
    m_field60 = 1.0f;
    m_friction = 0.6f;
    m_material = material;
    m_mapColor = color;
    m_lightEmission = 0;

    bool isEnableLight = material->blocksLight();

    m_mipmapEnabled = true;
    m_semiTransparent = false;
    m_field3C = false;
    m_materialType = 0;
    m_baseItemType = 0;

    m_isBlocksLight = !isEnableLight;

    m_texture = nullptr;
    m_isInited = false;
    m_field8 = 0;
    m_fieldC = false;
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
    int blockId = data.m_itemInstance->getItem()->getId();
    // int returnValue = 0xFFFFFFFF;
    switch (blockId) {
    case 0:
    case 126:
        if (data.m_interactionResult != InteractionResult::FAIL && data.m_belowBuildHeight)
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
        if (data.m_interactionResult != InteractionResult::FAIL)
            return StringIDs::Plant;
        if (!data.m_belowBuildHeight)
            return 0xFFFFFFFF;
        return StringIDs::Plant;
    case 62:
    case 130:
        if (data.m_interactionResult != InteractionResult::SUCCESS)
            return StringIDs::Hang;
        return 0xFFFFFFFF;
    case 66:
        return 0xFFFFFFFF;
    case 67:
    case 68:
        if (!data.m_interactionResult && data.m_belowBuildHeight)
            return StringIDs::Empty;
        return 0xFFFFFFFF;
    case 92:
        if (data.m_interactionResult != InteractionResult::FAIL
            && DyeColor::byItemData(data.m_itemInstance->getAuxValue())->getBlockData() == 12)
            return StringIDs::Plant;
        return 0xFFFFFFFF;
    case 142:
        if (data.m_interactionResult != InteractionResult::FAIL && data.m_belowBuildHeight)
            return StringIDs::Launch;
        return 0xFFFFFFFF;
    case 161:
        if (!data.m_interactionResult && data.m_belowBuildHeight) {
            if (LeadItem::bindPlayerMobsTest((std::shared_ptr<Player>)data.m_player, (Level*)data.m_level,
                                             BlockPos((std::shared_ptr<Entity>)data.m_player))) {
                return StringIDs::Attach;
            }
        }
        return 0xFFFFFFFF;
    default:
        if (!data.m_interactionResult && data.m_belowBuildHeight)
            return StringIDs::Place;
        return 0xFFFFFFFF;
    }
}

int Block::GetHitTooltip(const BlockTooltipDataHolder& data) {
    if (!data.m_playerAllowedToMine)
        return 0xFFFFFFFF;

    if (data.m_blockState->getBlock()->getId() == 7
        && (!data.m_player->GetGameMode()->isCreative()
            || !data.m_level->m_dimension->inPlayerConstraints(data.m_pos))) {
        return 0xFFFFFFFF;
    }

    return StringIDs::Mine_1;
}

const MaterialColor* Block::getMapColor(const BlockState* state, LevelSource* levelSource,
                                        const BlockPos& pos) {
    return this->m_mapColor;
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
    m_isInited = true;

    m_blockStateDefinition = createBlockStateDefinition();
    registerDefaultState(m_blockStateDefinition->any());

    bool isSolidRender = defaultBlockState()->isSolidRender();
    m_field28 = isSolidRender;
    m_lightBlock = isSolidRender ? 255 : 0;
}

Block* Block::sendBlockData(uchar sendBlockData) {
    this->m_sendBlockData = sendBlockData;
    return this;
}

Block* Block::setSoundType(const SoundType* soundType) {
    this->m_soundType = soundType;
    return this;
}

Block* Block::setLightBlock(int light) {
    this->m_lightBlock = light;
    return this;
}

Block* Block::setLightEmission(float emission) {
    this->m_lightEmission = emission * 15.0f;
    return this;
}

Block* Block::setExplodeable(float explodePower) {
    this->m_explosionResistance = explodePower * 3.0f;
    return this;
}

bool Block::isSolidBlockingCube(const BlockState* state) {
    return this->m_material->blocksMotion() && state->isCubeShaped();
}

bool Block::isSolidBlockingCubeAndNotSignalSource(const BlockState* state) {
    return this->m_material->isSolidBlocking() && state->isCubeShaped() && !state->isSignalSource();
}

bool Block::isViewBlocking(const BlockState* state) {
    return this->m_material->blocksMotion() && this->defaultBlockState()->isCubeShaped();
}

bool Block::isCubeShaped(const BlockState* state) {
    return true;
}

bool Block::hasCustomBreakingProgress(const BlockState* state) {
    return false;
}

bool Block::isPathfindable(LevelSource* levelSource, const BlockPos& pos) {
    return !this->m_material->blocksMotion();
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
    this->m_destroyTime = time;
    if (this->m_explosionResistance < time * 5.0f)
        this->m_explosionResistance = time * 5.0f;
    return this;
}

Block* Block::setIndestructible() {
    this->setDestroyTime(FLT_MAX);
    return this;
}

bool Block::isIndestructible() {
    return this->m_destroyTime == FLT_MAX;
}

float Block::getDestroySpeed(const BlockState* state, Level* level, const BlockPos& pos) {
    return this->m_destroyTime;
}

void Block::setTicking(bool ticking) {
    this->m_ticking = ticking;
}

Block* Block::disableMipmap() {
    this->m_mipmapEnabled = false;
    return this;
}

Block* Block::setSemiTransparent() {
    this->m_semiTransparent = true;
    return this;
}

bool Block::isTicking() {
    return this->m_ticking;
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
    threadStorage->m_aabBs[0] = this->getShape(state, levelSource, pos);
    threadStorage->m_aabBs[1] = nullptr;
    threadStorage->m_aabBs[2] = nullptr;
    return &threadStorage->m_aabBs;
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
    if (!level->m_isLocal) {
        int resourceCount = this->getResourceCountForLootBonus(fortuneLevel, level->m_random);
        for (int i = 0; i < resourceCount; i++) {
            if (level->m_random->nextFloat() > chance)
                continue;

            if (Item* item = this->getResource(state, level->m_random, fortuneLevel); item != Items::AIR) {
                Block::popResource(level, pos,
                                   new ItemInstance(item, 1, this->getSpawnResourcesAuxValue(state)));
            }
        }
    }
}

void Block::popExperience(Level* level, const BlockPos& pos, int amount) {
    if (!level->m_isLocal && level->getGameRules()->getBoolean(5)) {
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
    return this->m_explosionResistance / 5.0;
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

    HitResult* finalResult = new HitResult(tempResult->m_hitVector->add(pos.getX(), pos.getY(), pos.getZ()),
                                           tempResult->m_direction, pos);
    delete tempResult;
    return finalResult;
}

void Block::wasExploded(Level* level, const BlockPos& pos, Explosion* explosion) {
    if (!level->m_isLocal) {
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
    return level->getBlockState(pos)->getBlock()->m_material->isReplaceable();
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
    return this->defaultBlockState()->isCubeShaped() && !this->m_silkTouchable;
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
    this->m_descriptionId = name;
    this->m_useDescriptionId = desc;
    return this;
}

bool Block::isPossibleToRespawnInThis() {
    return !this->m_material->isSolid() && !this->m_material->isLiquid();
}

std::wstring Block::getName() {
    return L"";
}

unsigned int Block::getDescriptionId(int) {
    return this->m_descriptionId;
}

unsigned int Block::getUseDescriptionId() {
    return this->m_useDescriptionId;
}

bool Block::triggerEvent(const BlockState* state, Level* level, const BlockPos& pos, int, int) {
    return false;
}

bool Block::isCollectStatistics() {
    return this->m_collectStatistics;
}

bool Block::shouldBlockTick(Level* level, const BlockPos& pos, const BlockState* state) {
    return true;
}

Block* Block::setNotCollectStatistics() {
    this->m_collectStatistics = false;
    return this;
}

int Block::getPistonPushReaction(const BlockState* state) {
    return this->m_material->getPushReaction();
}

float Block::getShadeBrightness(const BlockState* state) {
    return state->isSolidBlockingCube() ? 0.2f : 1.0f;
}

void Block::fallOn(Level* level, const BlockPos& pos, std::shared_ptr<Entity> faller, float distance) {
    faller->causeFallDamage(distance, 1.0f);
}

void Block::updateEntityAfterFallOn(Level* level, std::shared_ptr<Entity> faller) {
    faller->m_deltaMovementY = 0.0f;
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
    this->m_iconName = icon;
    return this;
}

std::wstring Block::getIconName() {
    return this->m_iconName.empty() ? L"MISSING_ICON_TILE_" + std::to_wstring(this->getId()) + L"_"
                                          + std::to_wstring(this->m_descriptionId) :
                                      this->m_iconName;
}

void Block::registerIcons(IconRegister* iconReg) {
    this->m_texture = iconReg->registerIcon(this->getIconName());
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
    return this->m_texture;
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
    return this->m_blockStateDefinition;
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
    return this->m_soundType;
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

// NON_MATCHING | Score: 333111 (lower is better)
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
    DEFAULT_FACING = DirectionProperty::create(L"facing");
    HORIZONTAL_FACING = DirectionProperty::create(L"facing", Direction::Plane::HORIZONTAL);

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

    ResourceLocation* ee = Blocks::AIR_RSRC;
    Block* airBlock = (new AirBlock())->setNameAndDescriptionId(0xFFFFFFFF, 0xFFFFFFFF);
    Block::registerBlock(0, *ee, airBlock);

    Block::registerBlock(
        1, L"stone",
        (new StoneBlock())
            ->setDestroyTime(1.5)
            ->setExplodeable(10.0)
            ->setSoundType(SoundType::STONE)
            ->setIconName(L"stone")
            ->setNameAndDescriptionId(StringIDs::Stone, StringIDs::CanBeMinedWithAPickaxeToCollectCobblestone)
            ->setBaseItemTypeAndMaterial(14, 2));

    // Size: 0xC8u
    Block::registerBlock(
        2, L"grass",
        (new GrassBlock())
            ->setDestroyTime(0.6)
            ->setSoundType(SoundType::GRASS)
            ->setIconName(L"grass")
            ->setNameAndDescriptionId(StringIDs::GrassBlock, StringIDs::ABlockOfDirtWithGrassGrowingOn)
            ->setBaseItemTypeAndMaterial(13, 58));

    // Size: 0xA8u
    Block::registerBlock(
        3, L"dirt",
        (new DirtBlock())
            ->setDestroyTime(0.5)
            ->setSoundType(SoundType::DIRT)
            ->setIconName(L"dirt")
            ->setNameAndDescriptionId(StringIDs::Dirt, StringIDs::CollectedUsingAShovelCanBeUsedFor)
            ->setBaseItemTypeAndMaterial(13, 58));

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

    Block::registerBlock(7, L"bedrock",
                         (new BlockImpl(Material::STONE))
                             ->setIndestructible()
                             ->setExplodeable(6000000.0)
                             ->setSoundType(SoundType::STONE)
                             ->setIconName(L"bedrock")
                             ->setNotCollectStatistics()
                             ->setNameAndDescriptionId(StringIDs::Bedrock, 0xab4b374));

    // Size: 0xF0u
    Block::registerBlock(
        8, L"flowing_water",
        (new DynamicLiquidBlock(Material::WATER))
            ->setDestroyTime(100.0)
            ->setLightBlock(3)
            ->setIconName(L"water_flow")
            ->setNotCollectStatistics()
            ->sendBlockData(15)
            ->setNameAndDescriptionId(StringIDs::Water, StringIDs::ExtinguishesFireAndHelpsCropsGrowCanBe));

    // Size: 0xB8u
    Block::registerBlock(
        9, L"water",
        (new StaticLiquidBlock(Material::WATER))
            ->setDestroyTime(100.0)
            ->setLightBlock(3)
            ->setIconName(L"water_still")
            ->setNotCollectStatistics()
            ->sendBlockData(15)
            ->setNameAndDescriptionId(StringIDs::Water, StringIDs::ExtinguishesFireAndHelpsCropsGrowCanBe));

    // Size: 0xF0u
    Block::registerBlock(
        10, L"flowing_lava",
        (new DynamicLiquidBlock(Material::LAVA))
            ->setDestroyTime(100.0)
            ->setLightEmission(1.0)
            ->setIconName(L"lava_flow")
            ->setLightBlock(14)
            ->setNotCollectStatistics()
            ->sendBlockData(15)
            ->setNameAndDescriptionId(StringIDs::Lava, StringIDs::SetsFireToAnythingThatTouchesItCan));

    // Size: 0xB8u
    Block::registerBlock(
        11, L"lava",
        (new StaticLiquidBlock(Material::LAVA))
            ->setDestroyTime(100.0)
            ->setLightEmission(1.0)
            ->setIconName(L"lava_still")
            ->setLightBlock(14)
            ->setNotCollectStatistics()
            ->sendBlockData(15)
            ->setNameAndDescriptionId(StringIDs::Lava, StringIDs::SetsFireToAnythingThatTouchesItCan));

    // Size: 0xB8u
    Block::registerBlock(
        12, L"sand",
        (new SandBlock())
            ->setDestroyTime(0.5)
            ->setSoundType(SoundType::SAND)
            ->setIconName(L"sand")
            ->setNameAndDescriptionId(StringIDs::Sand, StringIDs::CollectedUsingAShovelCanBeSmeltedInto)
            ->setBaseItemTypeAndMaterial(13, 13));

    // Size: 0xA8u
    Block::registerBlock(
        13, L"gravel",
        (new GravelBlock())
            ->setDestroyTime(0.6)
            ->setSoundType(SoundType::DIRT)
            ->setIconName(L"gravel")
            ->setNameAndDescriptionId(StringIDs::Gravel,
                                      StringIDs::CollectedUsingAShovelSometimesProducesFlintWhen));

    // Size: 0xA8u
    Block::registerBlock(
        14, L"gold_ore",
        (new OreBlock())
            ->setDestroyTime(3.0)
            ->setExplodeable(5.0)
            ->setSoundType(SoundType::STONE)
            ->setIconName(L"gold_ore")
            ->setNameAndDescriptionId(0x53aa5c8, StringIDs::CanBeMinedWithAnIronPickaxeOrIronNSmeltedInA));

    // Size: 0xA8u
    Block::registerBlock(
        15, L"iron_ore",
        (new OreBlock())
            ->setDestroyTime(3.0)
            ->setExplodeable(5.0)
            ->setSoundType(SoundType::STONE)
            ->setIconName(L"iron_ore")
            ->setNameAndDescriptionId(StringIDs::IronOre, StringIDs::CanBeMinedWithAStonePickaxeOr));

    // Size: 0xA8u
    Block::registerBlock(
        16, L"coal_ore",
        (new OreBlock())
            ->setDestroyTime(3.0)
            ->setExplodeable(5.0)
            ->setSoundType(SoundType::STONE)
            ->setIconName(L"coal_ore")
            ->setNameAndDescriptionId(StringIDs::CoalOre, StringIDs::CanBeMinedWithAPickaxeToCollectCoal));

    // Size: 0x110u
    Block::registerBlock(
        17, L"log",
        (new OldLogBlock())
            ->setIconName(L"log")
            ->sendBlockData(15)
            ->setNameAndDescriptionId(StringIDs::Wood, StringIDs::ChoppedUsingAnAxeAndCanBeCrafted));

    // Size: 0x110u
    Block::registerBlock(18, L"leaves",
                         (new OldLeafBlock())
                             ->setIconName(L"leaves")
                             ->sendBlockData(3)
                             ->setNameAndDescriptionId(StringIDs::Leaves,
                                                       StringIDs::WhenBrokenSometimesDropsASaplingWhichCan));

    // Size: 0xB0u
    Block::registerBlock(
        19, L"sponge",
        (new SpongeBlock())
            ->setDestroyTime(0.6)
            ->setSoundType(SoundType::GRASS)
            ->setIconName(L"sponge")
            ->setNameAndDescriptionId(StringIDs::Sponge, StringIDs::CanAbsorbWaterNearbyTurningIntoAWet));

    // Size: 0xC0u
    Block::registerBlock(
        20, L"glass",
        (new GlassBlock(Material::GLASS, false))
            ->setDestroyTime(0.3)
            ->setSoundType(SoundType::GLASS)
            ->setIconName(L"glass")
            ->setNameAndDescriptionId(StringIDs::Glass, StringIDs::CreatedInAFurnaceBySmeltingSandCan)
            ->setBaseItemTypeAndMaterial(42, 34));

    // Size: 0xA8u
    Block::registerBlock(
        21, L"lapis_ore",
        (new OreBlock())
            ->setDestroyTime(3.0)
            ->setExplodeable(5.0)
            ->setSoundType(SoundType::STONE)
            ->setIconName(L"lapis_ore")
            ->setNameAndDescriptionId(StringIDs::LapisLazuliOre,
                                      StringIDs::CanBeMinedWithAStonePickaxeOrCollectLapisLazuli));

    // Size: 0xA8u
    Block::registerBlock(
        22, L"lapis_block",
        (new BlockImpl(Material::METAL))
            ->setDestroyTime(3.0)
            ->setExplodeable(5.0)
            ->setSoundType(SoundType::STONE)
            ->setIconName(L"lapis_block")
            ->setNameAndDescriptionId(StringIDs::LapisLazuliBlock, StringIDs::ACompactWayOfStoringLapisLazuli)
            ->setBaseItemTypeAndMaterial(32, 10));

    // Size: 0xE0u
    Block::registerBlock(
        23, L"dispenser",
        (new DispenserBlock())
            ->setDestroyTime(3.5)
            ->setSoundType(SoundType::STONE)
            ->setIconName(L"dispenser")
            ->sendBlockData(15)
            ->setNameAndDescriptionId(StringIDs::Dispenser_2, StringIDs::UsedToHoldAndShootOutItemsIn)
            ->setBaseItemTypeAndMaterial(51, 2));

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
    Block::registerBlock(25, L"noteblock",
                         (new NoteBlock())
                             ->setSoundType(SoundType::WOOD)
                             ->setDestroyTime(0.8)
                             ->setIconName(L"noteblock")
                             ->sendBlockData(15)
                             ->setBaseItemTypeAndMaterial(56, 0)
                             ->setNameAndDescriptionId(StringIDs::NoteBlock, 0xef9d20b));

    // Size: 0xE0u
    Block::registerBlock(
        26, L"bed",
        (new BedBlock())
            ->setSoundType(SoundType::WOOD)
            ->setDestroyTime(0.2)
            ->setIconName(L"bed")
            ->setNotCollectStatistics()
            ->sendBlockData(15)
            ->setNameAndDescriptionId(StringIDs::Bed_1, StringIDs::UsedToForwardTimeFromAnyTimeAt));

    // Size: 0xB0u
    Block::registerBlock(
        27, L"golden_rail",
        (new PoweredRailBlock())
            ->setDestroyTime(0.7)
            ->setSoundType(SoundType::METAL)
            ->setIconName(L"rail_golden")
            ->sendBlockData(15)
            ->setNameAndDescriptionId(StringIDs::PoweredRail,
                                      StringIDs::WhenPoweredAcceleratesMinecartsThatPassOverIt)
            ->setBaseItemTypeAndMaterial(12, 9)
            ->disableMipmap());

    // Size: 0xB8u
    Block::registerBlock(28, L"detector_rail",
                         (new DetectorRailBlock())
                             ->setDestroyTime(0.7)
                             ->setSoundType(SoundType::METAL)
                             ->setIconName(L"rail_detector")
                             ->sendBlockData(15)
                             ->setNameAndDescriptionId(StringIDs::DetectorRail,
                                                       StringIDs::FunctionsLikeAPressurePlateSendsARedstone)
                             ->disableMipmap()
                             ->setBaseItemTypeAndMaterial(12, 8));

    // Size: 0xC0u
    Block::registerBlock(
        29, L"sticky_piston",
        (new PistonBaseBlock(true))
            ->sendBlockData(15)
            ->setNameAndDescriptionId(StringIDs::StickyPiston,
                                      StringIDs::WhenPoweredUsingAButtonALeverARetractsPullsBackBlockTouching)
            ->setBaseItemTypeAndMaterial(27, 28)
            ->setIconName(L"pistonStickyBase"));

    // Size: 0xA8u
    Block::registerBlock(
        30, L"web",
        (new WebBlock())
            ->setLightBlock(1)
            ->setDestroyTime(4.0)
            ->setIconName(L"web")
            ->setNameAndDescriptionId(StringIDs::Cobweb, StringIDs::SlowsMovementWhenWalkingThroughItCanBe)
            ->disableMipmap());

    // Size: 0xC8u
    Block::registerBlock(
        31, L"tallgrass",
        (new TallGrassBlock())
            ->setDestroyTime(0.0)
            ->setSoundType(SoundType::GRASS)
            ->setIconName(L"tallgrass")
            ->setNameAndDescriptionId(StringIDs::TallGrass, StringIDs::SometimesProducesWheatSeedsWhenBroken)
            ->disableMipmap());

    // Size: 0xA8u
    Block::registerBlock(32, L"deadbush",
                         (new DeadBushBlock())
                             ->setDestroyTime(0.0)
                             ->setSoundType(SoundType::GRASS)
                             ->setIconName(L"deadbush")
                             ->setNameAndDescriptionId(StringIDs::DeadBush, StringIDs::CanBeUsedAsDecoration)
                             ->disableMipmap());

    // Size: 0xC0u
    Block::registerBlock(
        33, L"piston",
        (new PistonBaseBlock(false))
            ->sendBlockData(15)
            ->setNameAndDescriptionId(StringIDs::Piston, StringIDs::WhenPoweredUsingAButtonALeverA)
            ->setBaseItemTypeAndMaterial(27, 28)
            ->setIconName(L"pistonBase"));

    // Size: 0xB0u
    Block::registerBlock(
        34, L"piston_head",
        (new PistonHeadBlock())
            ->setNameAndDescriptionId(StringIDs::Piston, StringIDs::WhenPoweredUsingAButtonALeverA)
            ->sendBlockData(15));

    // Size: 0x128u
    Block::registerBlock(35, L"wool",
                         (new ColoredBlock(Material::WOOL))
                             ->setDestroyTime(0.8)
                             ->setSoundType(SoundType::WOOL)
                             ->setIconName(L"wool_colored")
                             ->sendBlockData(15)
                             ->setNameAndDescriptionId(StringIDs::Wool, 0x9c006f1)
                             ->setBaseItemTypeAndMaterial(49, 55));

    // Size: 0xB0u
    Block::registerBlock(36, L"piston_extension",
                         (new PistonMagicBlock())
                             ->setIconName(L"pistonBase")
                             ->setNameAndDescriptionId(StringIDs::Piston, 0xFFFFFFFF));

    // Size: 0xB8u
    Block::registerBlock(37, L"yellow_flower",
                         (new YellowFlowerBlock())
                             ->setDestroyTime(0.0)
                             ->setSoundType(SoundType::GRASS)
                             ->setIconName(L"flower_dandelion")
                             ->setNameAndDescriptionId(StringIDs::Flower, StringIDs::CanBeCraftedIntoADye)
                             ->disableMipmap());

    // Size: 0xB8u
    Block::registerBlock(38, L"red_flower",
                         (new RedFlowerBlock())
                             ->setDestroyTime(0.0)
                             ->setSoundType(SoundType::GRASS)
                             ->setIconName(L"flower_rose")
                             ->setNameAndDescriptionId(StringIDs::Poppy, StringIDs::CanBeCraftedIntoADye)
                             ->disableMipmap());

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
    Block::registerBlock(
        41, L"gold_block",
        (new BlockImpl(Material::METAL, MaterialColor::GOLD))
            ->setDestroyTime(3.0)
            ->setExplodeable(10.0)
            ->setSoundType(SoundType::METAL)
            ->setIconName(L"gold_block")
            ->setNameAndDescriptionId(StringIDs::BlockOfGold, StringIDs::ACompactWayOfStoringGold)
            ->setBaseItemTypeAndMaterial(32, 4));

    // Size: 0xA8u
    Block::registerBlock(
        42, L"iron_block",
        (new BlockImpl(Material::METAL, MaterialColor::METAL))
            ->setDestroyTime(5.0)
            ->setExplodeable(10.0)
            ->setSoundType(SoundType::METAL)
            ->setIconName(L"iron_block")
            ->setNameAndDescriptionId(StringIDs::BlockOfIron, StringIDs::ACompactWayOfStoringIron)
            ->setBaseItemTypeAndMaterial(32, 3));

    // Size: 0xB0u
    Block::registerBlock(43, L"double_stone_slab",
                         (new FullStoneSlabBlock())
                             ->setDestroyTime(2.0)
                             ->setExplodeable(10.0)
                             ->setSoundType(SoundType::STONE)
                             ->setIconName(L"stoneSlab")
                             ->setNameAndDescriptionId(StringIDs::StoneSlab,
                                                       StringIDs::UsedForMakingLongStaircasesTwoSlabsPlaced_2)
                             ->setBaseItemTypeAndMaterial(21, 2));

    // Size: 0xB0u
    Block::registerBlock(44, L"stone_slab",
                         (new HalfStoneSlabBlock())
                             ->setDestroyTime(2.0)
                             ->setExplodeable(10.0)
                             ->setSoundType(SoundType::STONE)
                             ->setIconName(L"stoneSlab")
                             ->setNameAndDescriptionId(StringIDs::StoneSlab,
                                                       StringIDs::UsedForMakingLongStaircasesTwoSlabsPlaced)
                             ->setBaseItemTypeAndMaterial(22, 2));

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
    Block::registerBlock(46, L"tnt",
                         (new TntBlock())
                             ->setDestroyTime(0.0)
                             ->setSoundType(SoundType::GRASS)
                             ->setIconName(L"tnt")
                             ->setNameAndDescriptionId(
                                 StringIDs::Tnt_2, StringIDs::UsedToCauseExplosionsActivatedAfterPlacingBy)
                             ->setBaseItemTypeAndMaterial(28, 0));

    // Size: 0xA8u
    Block::registerBlock(
        47, L"bookshelf",
        (new BookshelfBlock())
            ->setDestroyTime(1.5)
            ->setSoundType(SoundType::WOOD)
            ->setIconName(L"bookshelf")
            ->setIconName(L"bookshelf")
            ->setNameAndDescriptionId(StringIDs::Bookshelf,
                                      StringIDs::AllowsCreationOfMorePowerfulEnchantmentsWhenPlaced)
            ->setBaseItemTypeAndMaterial(46, 52));

    // Size: 0xA8u
    Block::registerBlock(48, L"mossy_cobblestone",
                         (new BlockImpl(Material::STONE))
                             ->setIconName(L"cobblestone_mossy")
                             ->setDestroyTime(2.0)
                             ->setExplodeable(10.0)
                             ->setSoundType(SoundType::STONE)
                             ->setNameAndDescriptionId(StringIDs::MossStone,
                                                       StringIDs::FoundInDungeonsCanBeUsedForConstruction)
                             ->setBaseItemTypeAndMaterial(14, 2));

    // Size: 0xA8u
    Block::registerBlock(
        49, L"obsidian",
        (new ObsidianBlock())
            ->setDestroyTime(50.0)
            ->setExplodeable(2000.0)
            ->setSoundType(SoundType::STONE)
            ->setIconName(L"obsidian")
            ->setNameAndDescriptionId(0x47cbe1a, StringIDs::CanOnlyBeMinedWithADiamondPickaxe)
            ->setBaseItemTypeAndMaterial(13, 2));

    // Size: 0xA8u
    Block::registerBlock(
        50, L"torch",
        (new TorchBlock())
            ->setDestroyTime(0.0)
            ->setLightEmission(0.9375)
            ->setSoundType(SoundType::WOOD)
            ->setIconName(L"torch_on")
            ->setNameAndDescriptionId(StringIDs::Torch, StringIDs::UsedToCreateLightTorchesAlsoMeltSnow)
            ->disableMipmap()
            ->setBaseItemTypeAndMaterial(23, 1));

    // Size: 0x108u
    Block::registerBlock(51, L"fire",
                         (new FireBlock())
                             ->setDestroyTime(0.0)
                             ->setLightEmission(1.0)
                             ->setSoundType(SoundType::WOOL)
                             ->setIconName(L"fire")
                             ->setNotCollectStatistics()
                             ->setNameAndDescriptionId(StringIDs::Fire, 0xFFFFFFFF)
                             ->disableMipmap());

    // Size: 0xB0u
    Block::registerBlock(52, L"mob_spawner",
                         (new MobSpawnerBlock())
                             ->setDestroyTime(5.0)
                             ->setSoundType(SoundType::METAL)
                             ->setIconName(L"mob_spawner")
                             ->setNotCollectStatistics()
                             ->setNameAndDescriptionId(StringIDs::MonsterSpawner, 0x4330c9));

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
    Block::registerBlock(
        54, L"chest",
        (new ChestBlock(0))
            ->setDestroyTime(2.5)
            ->setSoundType(SoundType::WOOD)
            ->setIconName(L"chest")
            ->sendBlockData(15)
            ->setNameAndDescriptionId(StringIDs::Chest_1, StringIDs::StoresBlocksAndItemsInsidePlaceTwoChests)
            ->setBaseItemTypeAndMaterial(36, 1));

    // Size: 0xF8u
    Block::registerBlock(
        55, L"redstone_wire",
        (new RedStoneWireBlock())
            ->setDestroyTime(0.0)
            ->setSoundType(SoundType::STONE)
            ->setIconName(L"redstone_dust")
            ->setNotCollectStatistics()
            ->sendBlockData(15)
            ->setNameAndDescriptionId(StringIDs::RedstoneDust, StringIDs::CanBePlacedOnGroundToCarryAn)
            ->disableMipmap());

    // Size: 0xA8u
    Block::registerBlock(56, L"diamond_ore",
                         (new OreBlock())
                             ->setDestroyTime(3.0)
                             ->setExplodeable(5.0)
                             ->setSoundType(SoundType::STONE)
                             ->setIconName(L"diamond_ore")
                             ->setNameAndDescriptionId(StringIDs::DiamondOre,
                                                       StringIDs::CanBeMinedWithAnIronPickaxeOrIronDiamonds));

    // Size: 0xA8u
    Block::registerBlock(
        57, L"diamond_block",
        (new BlockImpl(Material::METAL, MaterialColor::DIAMOND))
            ->setDestroyTime(5.0)
            ->setExplodeable(10.0)
            ->setSoundType(SoundType::METAL)
            ->setIconName(L"diamond_block")
            ->setNameAndDescriptionId(StringIDs::BlockOfDiamond, StringIDs::ACompactWayOfStoringDiamonds)
            ->setBaseItemTypeAndMaterial(32, 5));

    // Size: 0xB8u
    Block::registerBlock(58, L"crafting_table",
                         (new CraftingTableBlock())
                             ->setDestroyTime(2.5)
                             ->setSoundType(SoundType::WOOD)
                             ->setIconName(L"crafting_table")
                             ->setNameAndDescriptionId(StringIDs::CraftingTable,
                                                       StringIDs::AllowsYouToCraftAMoreVariedSelection)
                             ->setBaseItemTypeAndMaterial(30, 1));

    // Size: 0xF0u
    Block::registerBlock(
        59, L"wheat",
        (new CropBlock(false))
            ->setIconName(L"wheat")
            ->setNotCollectStatistics()
            ->sendBlockData(15)
            ->setNameAndDescriptionId(StringIDs::Crops, StringIDs::WhenFullyGrownCropsCanBeHarvestedTo)
            ->disableMipmap());

    // Size: 0xB8u
    Block* farmBlock = (new FarmBlock())
                           ->setDestroyTime(0.6)
                           ->setSoundType(SoundType::DIRT)
                           ->setIconName(L"farmland")
                           ->sendBlockData(15)
                           ->setNameAndDescriptionId(StringIDs::Farmland,
                                                     StringIDs::GroundThatHasBeenPreparedReadyToPlant);
    Block::registerBlock(60, L"farmland", farmBlock);

    // Size: 0xC8u
    Block::registerBlock(
        61, L"furnace",
        (new FurnaceBlock(false))
            ->setDestroyTime(3.5)
            ->setSoundType(SoundType::STONE)
            ->setIconName(L"furnace")
            ->sendBlockData(15)
            ->setNameAndDescriptionId(StringIDs::Furnace_2, StringIDs::AllowsYouToSmeltOreCreateCharcoalAnd)
            ->setBaseItemTypeAndMaterial(30, 2));

    // Size: 0xC8u
    Block::registerBlock(
        62, L"lit_furnace",
        (new FurnaceBlock(true))
            ->setDestroyTime(3.5)
            ->setSoundType(SoundType::STONE)
            ->setIconName(L"furnace")
            ->setLightEmission(0.875)
            ->sendBlockData(15)
            ->setNameAndDescriptionId(StringIDs::Furnace_2, StringIDs::AllowsYouToSmeltOreCreateCharcoalAnd));

    // Size: 0xB0u
    Block::registerBlock(
        63, L"standing_sign",
        (new StandingSignBlock())
            ->setDestroyTime(1.0)
            ->setSoundType(SoundType::WOOD)
            ->setIconName(L"sign")
            ->setNotCollectStatistics()
            ->sendBlockData(15)
            ->setNameAndDescriptionId(StringIDs::Sign_1, StringIDs::ShowsTextEnteredByYouOrOtherPlayers));

    // Size: 0xC8u
    Block::registerBlock(64, L"wooden_door",
                         (new DoorBlock(Material::WOOD))
                             ->setDestroyTime(3.0)
                             ->setSoundType(SoundType::WOOD)
                             ->setIconName(L"door_wood")
                             ->setNotCollectStatistics()
                             ->sendBlockData(15)
                             ->setNameAndDescriptionId(StringIDs::OakDoor_1,
                                                       StringIDs::WoodenDoorsAreActivatedByUsingHittingmOr));

    // Size: 0xA8u
    Block::registerBlock(65, L"ladder",
                         (new LadderBlock())
                             ->setDestroyTime(0.4)
                             ->setSoundType(SoundType::LADDER)
                             ->setIconName(L"ladder")
                             ->sendBlockData(15)
                             ->setNameAndDescriptionId(StringIDs::Ladder, StringIDs::UsedToClimbVertically)
                             ->disableMipmap()
                             ->setBaseItemTypeAndMaterial(48, 1));

    // Size: 0xB0u
    Block::registerBlock(66, L"rail",
                         (new RailBlock())
                             ->setDestroyTime(0.7)
                             ->setSoundType(SoundType::METAL)
                             ->setIconName(L"rail_normal")
                             ->sendBlockData(15)
                             ->setNameAndDescriptionId(StringIDs::Rail, 0xc6204ec)
                             ->setBaseItemTypeAndMaterial(12, 9)
                             ->disableMipmap());

    // Size: 0xC0u
    Block::registerBlock(
        67, L"stone_stairs",
        (new StairBlock(cobblestoneBlock->defaultBlockState()))
            ->setIconName(L"stairsStone")
            ->sendBlockData(15)
            ->setNameAndDescriptionId(StringIDs::CobblestoneStairs, StringIDs::UsedForCompactStaircases_1)
            ->setBaseItemTypeAndMaterial(16, 2));

    // Size: 0xB0u
    Block::registerBlock(
        68, L"wall_sign",
        (new WallSignBlock())
            ->setDestroyTime(1.0)
            ->setSoundType(SoundType::WOOD)
            ->setIconName(L"sign")
            ->setNotCollectStatistics()
            ->sendBlockData(15)
            ->setNameAndDescriptionId(StringIDs::Sign_1, StringIDs::ShowsTextEnteredByYouOrOtherPlayers));

    // Size: 0xA8u
    Block::registerBlock(
        69, L"lever",
        (new LeverBlock())
            ->setDestroyTime(0.5)
            ->setSoundType(SoundType::WOOD)
            ->setIconName(L"lever")
            ->sendBlockData(15)
            ->setNameAndDescriptionId(StringIDs::Lever,
                                      StringIDs::UsedToSendAnElectricalChargeByBeingTurnedOnOrInOn)
            ->setBaseItemTypeAndMaterial(45, 1));

    // Size: 0xC8u
    Block::registerBlock(
        70, L"stone_pressure_plate",
        (new PressurePlateBlock(L"stone", Material::STONE, PressurePlateBlock::Sensitivity::STONE))
            ->setDestroyTime(0.5)
            ->setSoundType(SoundType::STONE)
            ->sendBlockData(15)
            ->setNameAndDescriptionId(StringIDs::StonePressurePlate,
                                      StringIDs::APressureSensitivePadThatWillActivateWhen)
            ->setBaseItemTypeAndMaterial(15, 2));

    // Size: 0xC8u
    Block::registerBlock(
        71, L"iron_door",
        (new DoorBlock(Material::METAL))
            ->setIconName(L"door_iron")
            ->setDestroyTime(5.0)
            ->setSoundType(SoundType::METAL)
            ->setNotCollectStatistics()
            ->sendBlockData(15)
            ->setNameAndDescriptionId(StringIDs::IronDoor_1, StringIDs::IronDoorsCanOnlyBeOpenedByRedstone));

    // Size: 0xC8u
    Block::registerBlock(
        72, L"wooden_pressure_plate",
        (new PressurePlateBlock(L"planks_oak", Material::WOOD, PressurePlateBlock::Sensitivity::WOOD))
            ->setDestroyTime(0.5)
            ->setSoundType(SoundType::WOOD)
            ->sendBlockData(15)
            ->setNameAndDescriptionId(0x3827f5, StringIDs::AMoreSensitivePressurePlateThatCanBe)
            ->setBaseItemTypeAndMaterial(15, 1));

    // Size: 0xA8u
    Block::registerBlock(
        73, L"redstone_ore",
        (new RedStoneOreBlock(false))
            ->setIconName(L"redstone_ore")
            ->setDestroyTime(3.0)
            ->setExplodeable(5.0)
            ->setSoundType(SoundType::STONE)
            ->sendBlockData(15)
            ->setNameAndDescriptionId(StringIDs::RedstoneOre,
                                      StringIDs::CanBeMinedWithAnIronPickaxeOrIronRedstoneDust));

    // Size: 0xA8u
    Block::registerBlock(
        74, L"lit_redstone_ore",
        (new RedStoneOreBlock(true))
            ->setIconName(L"redstone_ore")
            ->setLightEmission(0.625)
            ->setDestroyTime(3.0)
            ->setExplodeable(5.0)
            ->setSoundType(SoundType::STONE)
            ->sendBlockData(15)
            ->setNameAndDescriptionId(StringIDs::RedstoneOre,
                                      StringIDs::CanBeMinedWithAnIronPickaxeOrIronRedstoneDust));

    // Size: 0xA8u
    Block::registerBlock(75, L"unlit_redstone_torch",
                         (new RedstoneTorchBlock(false))
                             ->setIconName(L"redstone_torch_off")
                             ->setDestroyTime(0.0)
                             ->setSoundType(SoundType::WOOD)
                             ->sendBlockData(15)
                             ->setNameAndDescriptionId(StringIDs::RedstoneTorch,
                                                       StringIDs::ConstantlySendsAnElectricalChargeOrCanBe)
                             ->disableMipmap());

    // Size: 0xA8u
    Block::registerBlock(76, L"redstone_torch",
                         (new RedstoneTorchBlock(true))
                             ->setIconName(L"redstone_torch_on")
                             ->setDestroyTime(0.0)
                             ->setLightEmission(0.5)
                             ->setSoundType(SoundType::WOOD)
                             ->sendBlockData(15)
                             ->setNameAndDescriptionId(StringIDs::RedstoneTorch,
                                                       StringIDs::ConstantlySendsAnElectricalChargeOrCanBe)
                             ->disableMipmap());

    // Size: 0xA8u
    Block::registerBlock(
        77, L"stone_button",
        (new StoneButtonBlock())
            ->setIconName(L"button")
            ->setDestroyTime(0.5)
            ->setSoundType(SoundType::STONE)
            ->sendBlockData(15)
            ->setNameAndDescriptionId(StringIDs::ButtonButton, StringIDs::UsedToSendAnElectricalChargeByBeing)
            ->setBaseItemTypeAndMaterial(35, 2));

    // Size: 0xA8u
    Block::registerBlock(
        78, L"snow_layer",
        (new SnowLayerBlock())
            ->setIconName(L"snow")
            ->setDestroyTime(0.1)
            ->setSoundType(SoundType::SNOW)
            ->sendBlockData(15)
            ->setLightBlock(0)
            ->setNameAndDescriptionId(StringIDs::Snow, StringIDs::CanBeDugWithAShovelToCreateSnowballs)
            ->setBaseItemTypeAndMaterial(13, 16));

    // Size: 0xC0u
    Block::registerBlock(
        79, L"ice",
        (new IceBlock(false))
            ->setIconName(L"ice")
            ->setDestroyTime(0.5)
            ->setLightBlock(3)
            ->setSoundType(SoundType::GLASS)
            ->setSemiTransparent()
            ->setNameAndDescriptionId(StringIDs::Ice, StringIDs::SlipperyWhenWalkedOnTurnsIntoWaterIf));

    // Size: 0xA8u
    Block::registerBlock(
        80, L"snow",
        (new SnowBlock())
            ->setIconName(L"snow")
            ->setDestroyTime(0.2)
            ->setSoundType(SoundType::WOOL)
            ->setNameAndDescriptionId(StringIDs::Snow, StringIDs::ACompactWayToStoreSnowballs)
            ->setBaseItemTypeAndMaterial(13, 16));

    // Size: 0xB8u
    Block::registerBlock(
        81, L"cactus",
        (new CactusBlock())
            ->setIconName(L"cactus")
            ->setDestroyTime(0.4)
            ->setSoundType(SoundType::WOOL)
            ->setNameAndDescriptionId(StringIDs::Cactus, StringIDs::CanBeCookedInAFurnaceToCreateAGreenDye)
            ->disableMipmap());

    // Size: 0xA8u
    Block::registerBlock(
        82, L"clay",
        (new ClayBlock())
            ->setIconName(L"clay")
            ->setDestroyTime(0.6)
            ->setSoundType(SoundType::DIRT)
            ->setNameAndDescriptionId(StringIDs::Clay_1, StringIDs::WhenBrokenDropsClayBallsWhichCanBe)
            ->setBaseItemTypeAndMaterial(13, 15));

    // Size: 0xB0u
    Block::registerBlock(
        83, L"reeds",
        (new ReedsBlock())
            ->setIconName(L"reeds")
            ->setDestroyTime(0.0)
            ->setSoundType(SoundType::GRASS)
            ->setNotCollectStatistics()
            ->setNameAndDescriptionId(StringIDs::SugarCane, StringIDs::CanBeCraftedToCreateSugar)
            ->disableMipmap());

    // Size: 0xB8u
    Block::registerBlock(84, L"jukebox",
                         (new JukeboxBlock())
                             ->setIconName(L"jukebox")
                             ->setDestroyTime(2.0)
                             ->setExplodeable(10.0)
                             ->setSoundType(SoundType::STONE)
                             ->sendBlockData(15)
                             ->setNameAndDescriptionId(StringIDs::Jukebox, StringIDs::PlaysMusicDiscs)
                             ->setBaseItemTypeAndMaterial(53, 0));

    // Size: 0xC0u
    Block::registerBlock(
        85, L"fence",
        (new FenceBlock(L"planks_oak", Material::WOOD, PlanksBlock::Variant::OAK->getMaterialColor()))
            ->setDestroyTime(2.0)
            ->setExplodeable(5.0)
            ->setSoundType(SoundType::WOOD)
            ->setNameAndDescriptionId(StringIDs::OakFence, StringIDs::UsedAsABarrierThatCannotBeJumped)
            ->setBaseItemTypeAndMaterial(29, 1));

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
    Block::registerBlock(
        87, L"netherrack",
        (new NetherrackBlock())
            ->setIconName(L"netherrack")
            ->setDestroyTime(0.4)
            ->setSoundType(SoundType::STONE)
            ->setNameAndDescriptionId(StringIDs::Netherrack, StringIDs::BurnsForeverIfSetAlight));

    // Size: 0xA8u
    Block::registerBlock(
        88, L"soul_sand",
        (new SoulSandBlock())
            ->setIconName(L"soul_sand")
            ->setDestroyTime(0.5)
            ->setSoundType(SoundType::SAND)
            ->setNameAndDescriptionId(StringIDs::SoulSand, StringIDs::SlowsMovementOfAnythingWalkingOverIt));

    // Size: 0xA8u
    Block::registerBlock(89, L"glowstone",
                         (new Glowstoneblock(Material::GLASS))  // they forgot to capitalize block it seems
                             ->setIconName(L"glowstone")
                             ->setDestroyTime(0.3)
                             ->setSoundType(SoundType::GLASS)
                             ->setLightEmission(1.0)
                             ->setNameAndDescriptionId(StringIDs::Glowstone,
                                                       StringIDs::UsedToCreateBrighterLightThanTorchesMelts)
                             ->setBaseItemTypeAndMaterial(23, 23));

    // Size: 0xC0u
    Block::registerBlock(
        90, L"portal",
        (new PortalBlock())
            ->setDestroyTime(-1.0)
            ->setIconName(L"portal")
            ->setSoundType(SoundType::GLASS)
            ->setLightEmission(0.75)
            ->setNameAndDescriptionId(StringIDs::Portal, StringIDs::StandingInPortalAllowsYouToPassBetween));

    // Size: 0xD8u
    Block::registerBlock(91, L"lit_pumpkin",
                         (new PumpkinBlock())
                             ->setIconName(L"pumpkin")
                             ->setDestroyTime(1.0)
                             ->setSoundType(SoundType::WOOD)
                             ->setLightEmission(1.0)
                             ->sendBlockData(15)
                             ->setNameAndDescriptionId(StringIDs::JackOLantern, 0xc9d5fb8)
                             ->setBaseItemTypeAndMaterial(23, 22));

    // Size: 0xC0u
    Block::registerBlock(
        92, L"cake",
        (new CakeBlock())
            ->setIconName(L"cake")
            ->setDestroyTime(0.5)
            ->setSoundType(SoundType::WOOL)
            ->setNotCollectStatistics()
            ->sendBlockData(15)
            ->setNameAndDescriptionId(StringIDs::Cake_1, StringIDs::Restores1IconShank01CanBeUsed7Times));

    // Size: 0xA8u
    Block::registerBlock(93, L"unpowered_repeater",
                         (new RepeaterBlock(false))
                             ->setIconName(L"repeater_off")
                             ->setDestroyTime(0.0)
                             ->setSoundType(SoundType::WOOD)
                             ->setNotCollectStatistics()
                             ->sendBlockData(15)
                             ->setNameAndDescriptionId(StringIDs::RedstoneRepeater,
                                                       StringIDs::UsedInRedstoneCircuitsAsARepeaterA)
                             ->disableMipmap()
                             ->setBaseItemTypeAndMaterial(59, 0));

    // Size: 0xA8u
    Block::registerBlock(94, L"powered_repeater",
                         (new RepeaterBlock(true))
                             ->setIconName(L"repeater_on")
                             ->setDestroyTime(0.0)
                             ->setSoundType(SoundType::WOOD)
                             ->setNotCollectStatistics()
                             ->sendBlockData(15)
                             ->setNameAndDescriptionId(StringIDs::RedstoneRepeater,
                                                       StringIDs::UsedInRedstoneCircuitsAsARepeaterA)
                             ->disableMipmap()
                             ->setBaseItemTypeAndMaterial(59, 0));

    // Size: 0xC0u
    Block::registerBlock(
        95, L"stained_glass",
        (new StainedGlassBlock(Material::GLASS))
            ->setIconName(L"glass")
            ->setDestroyTime(0.3)
            ->setSoundType(SoundType::GLASS)
            ->setNameAndDescriptionId(StringIDs::StainedGlass, StringIDs::CraftedFromGlassAndADye)
            ->setSemiTransparent()
            ->setBaseItemTypeAndMaterial(42, 34));

    // Size: 0xA8u
    Block::registerBlock(96, L"trapdoor",
                         (new TrapDoorBlock(Material::WOOD))
                             ->setIconName(L"trapdoor")
                             ->setDestroyTime(3.0)
                             ->setSoundType(SoundType::WOOD)
                             ->setNotCollectStatistics()
                             ->sendBlockData(15)
                             ->setNameAndDescriptionId(StringIDs::WoodenTrapdoor,
                                                       StringIDs::ActivatedByUsingHittingmOrWithRedstoneThey)
                             ->setBaseItemTypeAndMaterial(6, 25));

    // Size: 0xA8u
    Block::registerBlock(
        97, L"monster_egg",
        (new MonsterEggBlock())
            ->setIconName(L"monsterStoneEgg")
            ->setDestroyTime(0.75)
            ->setNameAndDescriptionId(StringIDs::SilverfishStone,
                                      StringIDs::SpawnsASilverfishWhenDestroyedMayAlsoSpawn));

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
    Block::registerBlock(
        99, L"brown_mushroom_block",
        (new HugeMushroomBlock(Material::WOOD, MaterialColor::DIRT, brownMushroomBlock))
            ->setIconName(L"mushroom_block")
            ->setDestroyTime(0.2)
            ->setSoundType(SoundType::WOOD)
            ->setNameAndDescriptionId(StringIDs::Mushroom, StringIDs::CanBeUsedAsDecoration_1)
            ->sendBlockData(15));

    // Size: 0xD8u
    Block::registerBlock(
        100, L"red_mushroom_block",
        (new HugeMushroomBlock(Material::WOOD, MaterialColor::COLOR_RED, redMushroomBlock))
            ->setIconName(L"mushroom_block")
            ->setDestroyTime(0.2)
            ->setSoundType(SoundType::WOOD)
            ->setNameAndDescriptionId(StringIDs::Mushroom_1, StringIDs::CanBeUsedAsDecoration_1)
            ->sendBlockData(15));

    // Size: 0xE0u
    Block::registerBlock(
        101, L"iron_bars",
        (new ThinFenceBlock(L"iron_bars", L"iron_bars", Material::METAL, true))
            ->setDestroyTime(5.0)
            ->setExplodeable(10.0)
            ->setSoundType(SoundType::METAL)
            ->setNameAndDescriptionId(StringIDs::IronBars, StringIDs::UsedAsABarrierSimilarToFences)
            ->setBaseItemTypeAndMaterial(29, 3));

    // Size: 0xE0u
    Block::registerBlock(
        102, L"glass_pane",
        (new ThinFenceBlock(L"glass", L"glass_pane_top", Material::GLASS, false))
            ->setDestroyTime(0.3)
            ->setSoundType(SoundType::GLASS)
            ->setNameAndDescriptionId(StringIDs::GlassPane, StringIDs::TransparentBlocksThatCanBeUsedAsAn)
            ->setBaseItemTypeAndMaterial(42, 34));

    // Size: 0xB0u
    Block* melonBlock
        = (new MelonBlock())
              ->setIconName(L"melon")
              ->setDestroyTime(1.0)
              ->setSoundType(SoundType::WOOD)
              ->setNameAndDescriptionId(StringIDs::Melon, StringIDs::CanBeCraftedFromMelonSlices);
    Block::registerBlock(103, L"melon_block", melonBlock);

    // Size: 0xC0u
    Block::registerBlock(104, L"pumpkin_stem",
                         (new StemBlock(pumpkinBlock))
                             ->setIconName(L"pumpkin_stem")
                             ->setDestroyTime(0.0)
                             ->setSoundType(SoundType::WOOD)
                             ->sendBlockData(15)
                             ->setNameAndDescriptionId(StringIDs::PumpkinStem, 0xFFFFFFFF)
                             ->disableMipmap());

    // Size: 0xC0u
    Block::registerBlock(105, L"melon_stem",
                         (new StemBlock(melonBlock))
                             ->setIconName(L"melon_stem")
                             ->setDestroyTime(0.0)
                             ->setSoundType(SoundType::WOOD)
                             ->sendBlockData(15)
                             ->setNameAndDescriptionId(StringIDs::MelonStem, 0xFFFFFFFF)
                             ->disableMipmap());

    // Size: 0xA8u
    Block::registerBlock(
        106, L"vine",
        (new VineBlock())
            ->setIconName(L"vine")
            ->setDestroyTime(0.2)
            ->setSoundType(SoundType::GRASS)
            ->sendBlockData(15)
            ->setNameAndDescriptionId(StringIDs::Vines, StringIDs::GrowsOverTimeWhenPlacedCanBeCollected)
            ->disableMipmap());

    // Size: 0xC0u
    Block::registerBlock(107, L"fence_gate",
                         (new FenceGateBlock(L"planks_oak", PlanksBlock::Variant::OAK))
                             ->setIconName(L"fenceGate")
                             ->setDestroyTime(2.0)
                             ->setExplodeable(5.0)
                             ->setSoundType(SoundType::WOOD)
                             ->sendBlockData(15)
                             ->setNameAndDescriptionId(StringIDs::OakFenceGate,
                                                       StringIDs::SimilarToADoorButUsedPrimarilyWithFences)
                             ->setBaseItemTypeAndMaterial(47, 1));

    // Size: 0xC0u
    Block::registerBlock(
        108, L"brick_stairs",
        (new StairBlock(brickBlock->defaultBlockState()))
            ->setIconName(L"stairsBrick")
            ->sendBlockData(15)
            ->setNameAndDescriptionId(StringIDs::BrickStairs, StringIDs::UsedForCompactStaircases_1)
            ->setBaseItemTypeAndMaterial(16, 14));

    // Size: 0xC0u
    const BlockState* stoneBrickStairBlockVariant
        = stoneBrickBlock->defaultBlockState()->setValue<StoneBrickBlock::Variant*>(
            StoneBrickBlock::VARIANT, StoneBrickBlock::Variant::DEFAULT);
    Block::registerBlock(
        109, L"stone_brick_stairs",
        (new StairBlock(stoneBrickStairBlockVariant))
            ->setIconName(L"stairsStoneBrickSmooth")
            ->sendBlockData(15)
            ->setNameAndDescriptionId(StringIDs::StoneBrickStairs, StringIDs::UsedForCompactStaircases_1)
            ->setBaseItemTypeAndMaterial(16, 31));

    // Size: 0xB8u
    Block::registerBlock(
        110, L"mycelium",
        (new MyceliumBlock())
            ->setIconName(L"mycelium")
            ->setDestroyTime(0.6)
            ->setSoundType(SoundType::GRASS)
            ->setNameAndDescriptionId(StringIDs::Mycelium, StringIDs::SimilarToGrassBlocksButVeryGoodFor));

    // Size: 0xA8u
    Block::registerBlock(
        111, L"waterlily",
        (new WaterlilyBlock())
            ->setIconName(L"waterlily")
            ->setDestroyTime(0.0)
            ->setSoundType(SoundType::GRASS)
            ->setNameAndDescriptionId(StringIDs::LilyPad, StringIDs::FloatsOnWaterAndCanBeWalkedOn)
            ->disableMipmap());

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
    Block::registerBlock(
        113, L"nether_brick_fence",
        (new FenceBlock(L"nether_brick", Material::STONE, MaterialColor::NETHER))
            ->setDestroyTime(2.0)
            ->setExplodeable(10.0)
            ->setSoundType(SoundType::STONE)
            ->setNameAndDescriptionId(StringIDs::NetherBrickFence, StringIDs::UsedInNetherFortresses)
            ->setBaseItemTypeAndMaterial(29, 32));

    // Size: 0xC0u
    Block::registerBlock(
        114, L"nether_brick_stairs",
        (new StairBlock(netherBrickBlock->defaultBlockState()))
            ->setIconName(L"stairsNetherBrick")
            ->sendBlockData(15)
            ->setNameAndDescriptionId(StringIDs::NetherBrickStairs, StringIDs::UsedForCompactStaircases_1)
            ->setBaseItemTypeAndMaterial(16, 32));

    // Size: 0xC0u
    Block::registerBlock(115, L"nether_wart",
                         (new NetherWartBlock())
                             ->setIconName(L"nether_wart")
                             ->sendBlockData(15)
                             ->setNameAndDescriptionId(StringIDs::NetherWart_1,
                                                       StringIDs::FoundInNetherFortressesWillDropNetherWart)
                             ->disableMipmap());

    // Size: 0xC0u
    Block::registerBlock(
        116, L"enchanting_table",
        (new EnchantmentTableBlock())
            ->setIconName(L"enchanting_table")
            ->setDestroyTime(5.0)
            ->setExplodeable(2000.0)
            ->setNameAndDescriptionId(StringIDs::EnchantmentTable,
                                      StringIDs::ThisAllowsPlayersToEnchantSwordsPickaxesAxes)
            ->setBaseItemTypeAndMaterial(30, 36));

    // Size: 0xB8u
    Block::registerBlock(117, L"brewing_stand",
                         (new BrewingStandBlock())
                             ->setIconName(L"brewing_stand")
                             ->setDestroyTime(0.5)
                             ->setLightEmission(0.125)
                             ->sendBlockData(15)
                             ->setNameAndDescriptionId(StringIDs::BrewingStand_2,
                                                       StringIDs::UsedForMakingPotionsAndSplashPotions)
                             ->setBaseItemTypeAndMaterial(30, 35));

    // Size: 0xD0u
    Block::registerBlock(
        118, L"cauldron",
        (new CauldronBlock())
            ->setIconName(L"cauldron")
            ->setDestroyTime(2.0)
            ->sendBlockData(15)
            ->setNameAndDescriptionId(StringIDs::Cauldron_1, StringIDs::UsedToMixDyesAndDyeArmorOr));

    // Size: 0xB0u
    Block::registerBlock(
        119, L"end_portal",
        (new EndPortalBlock(Material::PORTAL))
            ->setDestroyTime(3.4028e38)
            ->setExplodeable(6000000.0)
            ->setNameAndDescriptionId(StringIDs::EndPortal, StringIDs::ThisCanBeActivatedUsingTwelveEyeOf));

    // Size: 0xB8u
    Block::registerBlock(
        120, L"end_portal_frame",
        (new EndPortalFrameBlock())
            ->setIconName(L"endframe")
            ->setSoundType(SoundType::GLASS)
            ->setLightEmission(0.125)
            ->setDestroyTime(3.4028e38)
            ->sendBlockData(15)
            ->setExplodeable(6000000.0)
            ->setNameAndDescriptionId(StringIDs::EndPortalFrame, StringIDs::UsedToFormAnEndPortal));

    // Size: 0xA8u
    Block::registerBlock(
        121, L"end_stone",
        (new BlockImpl(Material::STONE, MaterialColor::SAND))
            ->setIconName(L"end_stone")
            ->setDestroyTime(3.0)
            ->setExplodeable(15.0)
            ->setSoundType(SoundType::STONE)
            ->setNameAndDescriptionId(StringIDs::EndStone, StringIDs::ABlockTypeFoundInTheEndIt));

    // Size: 0xA8u
    Block::registerBlock(
        122, L"dragon_egg",
        (new DragonEggBlock())
            ->setDestroyTime(3.0)
            ->setIconName(L"dragon_egg")
            ->setExplodeable(15.0)
            ->setSoundType(SoundType::STONE)
            ->setLightEmission(0.125)
            ->setNameAndDescriptionId(StringIDs::DragonEgg, StringIDs::ThisBlockIsCreatedByDefeatOfDragon));

    // Size: 0xA8u
    Block::registerBlock(
        123, L"redstone_lamp",
        (new RedstoneLampBlock(false))
            ->setIconName(L"redstone_lamp_off")
            ->setDestroyTime(0.3)
            ->setSoundType(SoundType::GLASS)
            ->setBaseItemTypeAndMaterial(56, 0)
            ->setNameAndDescriptionId(StringIDs::RedstoneLamp, StringIDs::EmitsLightWhenPowered));

    // Size: 0xA8u
    Block::registerBlock(
        124, L"lit_redstone_lamp",
        (new RedstoneLampBlock(true))
            ->setIconName(L"redstone_lamp_on")
            ->setDestroyTime(0.3)
            ->setSoundType(SoundType::GLASS)
            ->setBaseItemTypeAndMaterial(56, 0)
            ->setNameAndDescriptionId(StringIDs::RedstoneLamp, StringIDs::EmitsLightWhenPowered));

    // Size: 0xA8u
    Block::registerBlock(125, L"double_wooden_slab",
                         (new FullWoodSlabBlock())
                             ->setIconName(L"woodSlab")
                             ->setDestroyTime(2.0)
                             ->setExplodeable(5.0)
                             ->setSoundType(SoundType::WOOD)
                             ->setNameAndDescriptionId(StringIDs::UsedForMakingLongStaircasesTwoSlabsPlaced_5,
                                                       StringIDs::UsedForMakingLongStaircasesTwoSlabsPlaced_5)
                             ->setBaseItemTypeAndMaterial(21, 1));

    // Size: 0xA8u
    Block::registerBlock(126, L"wooden_slab",
                         (new HalfWoodSlabBlock())
                             ->setIconName(L"woodSlab")
                             ->setDestroyTime(2.0)
                             ->setExplodeable(5.0)
                             ->setSoundType(SoundType::WOOD)
                             ->setNameAndDescriptionId(StringIDs::UsedForMakingLongStaircasesTwoSlabsPlaced_5,
                                                       StringIDs::UsedForMakingLongStaircasesTwoSlabsPlaced_5)
                             ->setBaseItemTypeAndMaterial(22, 1));

    // Size: 0xC8u
    Block::registerBlock(
        127, L"cocoa",
        (new CocoaBlock())
            ->setIconName(L"cocoa")
            ->setDestroyTime(0.2)
            ->setExplodeable(5.0)
            ->setSoundType(SoundType::WOOD)
            ->sendBlockData(15)
            ->setNameAndDescriptionId(StringIDs::Cocoa, StringIDs::CanBeFarmedToCollectCocoaBeans));

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
    Block::registerBlock(
        129, L"emerald_ore",
        (new OreBlock())
            ->setIconName(L"emerald_ore")
            ->setDestroyTime(3.0)
            ->setExplodeable(5.0)
            ->setSoundType(SoundType::STONE)
            ->setNameAndDescriptionId(StringIDs::EmeraldOre, StringIDs::CanBeMinedWithAnIronPickaxeOr));

    // Size: 0xB0u
    Block::registerBlock(
        130, L"ender_chest",
        (new EnderChestBlock())
            ->setDestroyTime(22.5)
            ->setIconName(L"enderChest")
            ->setExplodeable(1000.0)
            ->setSoundType(SoundType::STONE)
            ->sendBlockData(15)
            ->setLightEmission(0.5)
            ->setNameAndDescriptionId(StringIDs::EnderChest, StringIDs::SimilarToAChestExceptThatItemsPlaced)
            ->setBaseItemTypeAndMaterial(36, 33));

    // Size: 0xA8u
    Block::registerBlock(131, L"tripwire_hook",
                         (new TripWireHookBlock())
                             ->setIconName(L"trip_wire_source")
                             ->sendBlockData(15)
                             ->setNameAndDescriptionId(StringIDs::TripwireHook,
                                                       StringIDs::IsActivatedWhenAnEntityPassesThroughA)
                             ->setBaseItemTypeAndMaterial(45, 0));

    // Size: 0xA8u
    Block::registerBlock(
        132, L"tripwire",
        (new TripWireBlock())
            ->setIconName(L"trip_wire")
            ->sendBlockData(15)
            ->setNameAndDescriptionId(0x36c80c9, StringIDs::ActivatesAConnectedTripwireHookWhenAnEntity)
            ->disableMipmap());

    // Size: 0xA8u
    Block::registerBlock(
        133, L"emerald_block",
        (new BlockImpl(Material::METAL, MaterialColor::EMERALD))
            ->setIconName(L"emerald_block")
            ->setDestroyTime(5.0)
            ->setExplodeable(10.0)
            ->setSoundType(SoundType::METAL)
            ->setNameAndDescriptionId(StringIDs::BlockOfEmerald, StringIDs::ACompactWayOfStoringEmeralds)
            ->setBaseItemTypeAndMaterial(32, 44));

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
    Block::registerBlock(
        138, L"beacon",
        (new BeaconBlock())
            ->setIconName(L"beacon")
            ->setLightEmission(1.0)
            ->setSoundType(SoundType::GLASS)
            ->setNameAndDescriptionId(StringIDs::Beacon_1, StringIDs::ProjectsABeamOfLightIntoSkyAnd));

    // Size: 0xA8u
    Block::registerBlock(
        139, L"cobblestone_wall",
        (new WallBlock(cobblestoneBlock))
            ->setIconName(L"cobbleWall")
            ->setNameAndDescriptionId(StringIDs::CobblestoneWall, StringIDs::AWallMadeOfCobblestone)
            ->setBaseItemTypeAndMaterial(29, 2));

    // Size: 0xB0u
    Block::registerBlock(140, L"flower_pot",
                         (new FlowerPotBlock())
                             ->setDestroyTime(0.0)
                             ->setIconName(L"flower_pot")
                             ->setSoundType(SoundType::STONE)
                             ->setNameAndDescriptionId(StringIDs::FlowerPot_1,
                                                       StringIDs::UsedAsADecorationFlowersSaplingsCactiAnd));

    // Size: 0x110u
    Block::registerBlock(
        141, L"carrots",
        (new CarrotBlock())
            ->setIconName(L"carrots")
            ->setNameAndDescriptionId(StringIDs::Carrots, StringIDs::Restores15IconShank01AndCan)
            ->disableMipmap());

    // Size: 0x110u
    Block::registerBlock(
        142, L"potatoes",
        (new PotatoBlock())
            ->setIconName(L"potatoes")
            ->setNameAndDescriptionId(StringIDs::Potatoes, StringIDs::Restores05IconShank01OrCan)
            ->disableMipmap());

    // Size: 0xA8u
    Block::registerBlock(143, L"wooden_button",
                         (new WoodButtonBlock())
                             ->setIconName(L"button")
                             ->setBaseItemTypeAndMaterial(35, 1)
                             ->setDestroyTime(0.5)
                             ->setSoundType(SoundType::WOOD)
                             ->sendBlockData(15)
                             ->setNameAndDescriptionId(StringIDs::ButtonButton,
                                                       StringIDs::UsedToSendAnElectricalChargeByBeing));

    // Size: 0xC0u
    Block::registerBlock(
        144, L"skull",
        (new SkullBlock())
            ->setIconName(L"")
            ->setDestroyTime(1.0)
            ->setSoundType(SoundType::STONE)
            ->setNameAndDescriptionId(StringIDs::Skull_1, StringIDs::MobHeadsCanBePlacedAsADecoration));

    // Size: 0xC0u
    Block::registerBlock(
        145, L"anvil",
        (new AnvilBlock())
            ->setIconName(L"anvil")
            ->setBaseItemTypeAndMaterial(30, 3)
            ->setDestroyTime(5.0)
            ->setSoundType(SoundType::ANVIL)
            ->setExplodeable(2000.0)
            ->sendBlockData(15)
            ->setNameAndDescriptionId(StringIDs::Anvil_1, StringIDs::CanBeUsedToRepairWeaponsToolsAndArmor));

    // Size: 0xB8u
    Block::registerBlock(
        146, L"trapped_chest",
        (new ChestBlock(true))
            ->setBaseItemTypeAndMaterial(36, 25)
            ->setDestroyTime(2.5)
            ->setSoundType(SoundType::WOOD)
            ->setNameAndDescriptionId(
                StringIDs::TrappedChest,
                StringIDs::StoresBlocksAndItemsInsidePlaceTwoChestsATrappedAlsoCreatesRedstone));

    // Size: 0xC8u
    Block::registerBlock(
        147, L"light_weighted_pressure_plate",
        (new WeightedPressurePlateBlock(L"gold_block", Material::METAL, 15, MaterialColor::GOLD))
            ->setBaseItemTypeAndMaterial(15, 4)
            ->setDestroyTime(0.5)
            ->setSoundType(SoundType::WOOD)
            ->setNameAndDescriptionId(StringIDs::WeightedPressurePlateLight,
                                      StringIDs::ProvidesARedstoneChargeTheChargeWillBe_1));

    // Size: 0xC8u
    Block::registerBlock(148, L"heavy_weighted_pressure_plate",
                         (new WeightedPressurePlateBlock(L"iron_block", Material::METAL, 150, 0))
                             ->setBaseItemTypeAndMaterial(15, 3)
                             ->setDestroyTime(0.5)
                             ->setSoundType(SoundType::WOOD)
                             ->setNameAndDescriptionId(StringIDs::WeightedPressurePlateHeavy,
                                                       StringIDs::ProvidesARedstoneChargeTheChargeWillBe));

    // Size: 0xB0u
    Block::registerBlock(149, L"unpowered_comparator",
                         (new ComparatorBlock(false))
                             ->setIconName(L"comparator_off")
                             ->setDestroyTime(0.0)
                             ->setSoundType(SoundType::WOOD)
                             ->setNameAndDescriptionId(StringIDs::RedstoneComparator_1,
                                                       StringIDs::UsedInRedstoneCircuitsToMaintainCompareOr)
                             ->disableMipmap()
                             ->setBaseItemTypeAndMaterial(59, 0));

    // Size: 0xB0u
    Block::registerBlock(150, L"powered_comparator",
                         (new ComparatorBlock(true))
                             ->setIconName(L"comparator_on")
                             ->setDestroyTime(0.0)
                             ->setLightEmission(0.625)
                             ->setSoundType(SoundType::WOOD)
                             ->setNameAndDescriptionId(StringIDs::RedstoneComparator_1,
                                                       StringIDs::UsedInRedstoneCircuitsToMaintainCompareOr)
                             ->disableMipmap()
                             ->setBaseItemTypeAndMaterial(59, 0));

    // Size: 0xD0u
    Block::registerBlock(151, L"daylight_detector",
                         (new DaylightDetectorBlock(false))
                             ->setIconName(L"daylight_detector")
                             ->setNameAndDescriptionId(StringIDs::DaylightSensor,
                                                       StringIDs::ABlockThatOutputsARedstoneSignalBased));

    // Size: 0xA8u
    Block::registerBlock(
        152, L"redstone_block",
        (new PoweredBlock(Material::METAL, MaterialColor::FIRE))
            ->setIconName(L"redstone_block")
            ->setDestroyTime(5.0)
            ->setExplodeable(10.0)
            ->setSoundType(SoundType::METAL)
            ->setNameAndDescriptionId(StringIDs::BlockOfRedstone, StringIDs::UsedAsARedstonePowerSourceCanBe)
            ->setBaseItemTypeAndMaterial(32, 48));

    // Size: 0xA8u
    Block::registerBlock(153, L"quartz_ore",
                         (new OreBlock(MaterialColor::NETHER))
                             ->setIconName(L"quartz_ore")
                             ->setDestroyTime(3.0)
                             ->setExplodeable(5.0)
                             ->setSoundType(SoundType::STONE)
                             ->setNameAndDescriptionId(StringIDs::NetherQuartzOre,
                                                       StringIDs::CanBeMinedWithAPickaxeToCollect));

    // Size: 0xC8u
    Block::registerBlock(
        154, L"hopper",
        (new HopperBlock())
            ->setIconName(L"hopper")
            ->setDestroyTime(3.0)
            ->setExplodeable(8.0)
            ->setSoundType(SoundType::METAL)
            ->setNameAndDescriptionId(StringIDs::Hopper_1, StringIDs::UsedToCatchItemsOrToTransferItems)
            ->setBaseItemTypeAndMaterial(51, 0));

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
    Block::registerBlock(157, L"activator_rail",
                         (new PoweredRailBlock())
                             ->setIconName(L"rail_activator")
                             ->setDestroyTime(0.7)
                             ->setSoundType(SoundType::METAL)
                             ->setNameAndDescriptionId(StringIDs::ActivatorRail, 0xe397c8a)
                             ->setBaseItemTypeAndMaterial(12, 9));

    // Size: 0xE8u
    Block::registerBlock(
        158, L"dropper",
        (new DropperBlock())
            ->setIconName(L"dropper")
            ->setDestroyTime(3.5)
            ->setSoundType(SoundType::STONE)
            ->setNameAndDescriptionId(StringIDs::Dropper_1, StringIDs::UsedToHoldAndDropItemsOrPush)
            ->setBaseItemTypeAndMaterial(51, 0));

    // Size: 0x128u
    Block::registerBlock(159, L"stained_hardened_clay",
                         (new StainedHardenedClayBlock())
                             ->setIconName(L"hardened_clay_stained")
                             ->setDestroyTime(1.25)
                             ->setExplodeable(7.0)
                             ->setSoundType(SoundType::STONE)
                             ->setNameAndDescriptionId(StringIDs::StainedTerracotta,
                                                       StringIDs::ColorfulBlocksCraftedByDyeingTerracotta)
                             ->setBaseItemTypeAndMaterial(41, 15));

    // Size: 0xE0u
    Block::registerBlock(
        160, L"stained_glass_pane",
        (new StainedGlassPaneBlock())
            ->setIconName(L"glass")
            ->setDestroyTime(0.3)
            ->setSoundType(SoundType::GLASS)
            ->setSemiTransparent()
            ->setNameAndDescriptionId(StringIDs::StainedGlassPane, StringIDs::CraftedFromStainedGlass)
            ->setBaseItemTypeAndMaterial(42, 34));

    // Size: 0x110u
    Block::registerBlock(161, L"leaves2",
                         (new NewLeafBlock())
                             ->setIconName(L"leaves")
                             ->sendBlockData(3)
                             ->setNameAndDescriptionId(StringIDs::Leaves,
                                                       StringIDs::WhenBrokenSometimesDropsASaplingWhichCan));

    // Size: 0x110u
    Block::registerBlock(
        162, L"log2",
        (new NewLogBlock())
            ->setIconName(L"log")
            ->sendBlockData(15)
            ->setNameAndDescriptionId(StringIDs::Wood, StringIDs::ChoppedUsingAnAxeAndCanBeCrafted));

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
    Block::registerBlock(165, L"slime",
                         (new SlimeBlock())
                             ->setSoundType(SoundType::SLIME_BLOCK)
                             ->setNameAndDescriptionId(StringIDs::SlimeBlock, 0xc6ece52)
                             ->setBaseItemTypeAndMaterial(32, 57)
                             ->setSemiTransparent());

    // Size: 0xA8u
    Block::registerBlock(166, L"barrier",
                         (new BarrierBlock())
                             ->setIconName(L"barrier")
                             ->setNameAndDescriptionId(0x435e342, StringIDs::AnInvisibleButSolidBlock));

    // Size: 0xA8u
    Block::registerBlock(167, L"iron_trapdoor",
                         (new TrapDoorBlock(Material::METAL))
                             ->setIconName(L"iron_trapdoor")
                             ->setDestroyTime(5.0)
                             ->setSoundType(SoundType::METAL)
                             ->setNotCollectStatistics()
                             ->sendBlockData(15)
                             ->setNameAndDescriptionId(StringIDs::IronTrapdoor,
                                                       StringIDs::IronTrapdoorsCanOnlyBeOpenedByRedstone)
                             ->setBaseItemTypeAndMaterial(6, 25));

    // Size: 0xA8u
    Block::registerBlock(
        168, L"prismarine",
        (new PrismarineBlock())
            ->setIconName(L"prismarine_rough")
            ->setDestroyTime(1.5)
            ->setExplodeable(10.0)
            ->setSoundType(SoundType::STONE)
            ->setNameAndDescriptionId(StringIDs::Prismarine, StringIDs::RareDecorativeStoneThatCanBeFoundIn)
            ->setBaseItemTypeAndMaterial(13, 13));

    // Size: 0xA8u
    Block::registerBlock(169, L"sea_lantern",
                         (new SeaLanternBlock(Material::GLASS))
                             ->setIconName(L"sea_lantern")
                             ->setDestroyTime(0.3)
                             ->setSoundType(SoundType::GLASS)
                             ->setLightEmission(1.0)
                             ->setNameAndDescriptionId(StringIDs::SeaLantern,
                                                       StringIDs::UnderwaterLightSourcesThatCanBeFoundIn)
                             ->setBaseItemTypeAndMaterial(23, 54));

    // Size: 0xB0u
    Block::registerBlock(
        170, L"hay_block",
        (new HayBlock())
            ->setDestroyTime(0.5)
            ->setIconName(L"hay_block")
            ->setSoundType(SoundType::GRASS)
            ->setNameAndDescriptionId(StringIDs::HayBale, StringIDs::CanBeFedToHorsesDonkeysMulesAnd)
            ->setBaseItemTypeAndMaterial(32, 53));

    // Size: 0xA8u
    Block::registerBlock(171, L"carpet",
                         (new WoolCarpetBlock())
                             ->setIconName(L"woolCarpet")
                             ->setDestroyTime(0.1)
                             ->setSoundType(SoundType::WOOL)
                             ->setLightBlock(0)
                             ->setNameAndDescriptionId(StringIDs::Carpet, 0x1c5501b)
                             ->setBaseItemTypeAndMaterial(40, 6));

    // Size: 0xA8u
    Block::registerBlock(
        172, L"hardened_clay",
        (new HardenedClayBlock())
            ->setIconName(L"hardened_clay")
            ->setDestroyTime(1.25)
            ->setExplodeable(7.0)
            ->setSoundType(SoundType::STONE)
            ->setNameAndDescriptionId(StringIDs::Terracotta, StringIDs::CreatedBySmeltingClayInAFurnace)
            ->setBaseItemTypeAndMaterial(41, 15));

    // Size: 0xA8u
    Block::registerBlock(
        173, L"coal_block",
        (new BlockImpl(Material::STONE, MaterialColor::COLOR_BLACK))
            ->setIconName(L"coal_block")
            ->setDestroyTime(5.0)
            ->setExplodeable(10.0)
            ->setSoundType(SoundType::STONE)
            ->setNameAndDescriptionId(StringIDs::BlockOfCoal, StringIDs::ACompactWayOfStoringCoalCanBe)
            ->setBaseItemTypeAndMaterial(32, 49));

    // Size: 0xA8u
    Block::registerBlock(
        174, L"packed_ice",
        (new PackedIceBlock())
            ->setIconName(L"ice_packed")
            ->setDestroyTime(0.5)
            ->setSoundType(SoundType::GLASS)
            ->setNameAndDescriptionId(StringIDs::PackedIce, StringIDs::ASolidUnmeltableBlockOfIceThatCan));

    // Size: 0xB0u
    Block::registerBlock(175, L"double_plant",
                         (new DoublePlantBlock())
                             ->setNameAndDescriptionId(StringIDs::DoublePlantBlock, StringIDs::ALargePlant)
                             ->disableMipmap());

    // Size: 0xB0u
    Block::registerBlock(
        176, L"standing_banner",
        (new StandingBannerBlock())
            ->setIconName(L"planks_oak")
            ->setDestroyTime(1.0)
            ->setSoundType(SoundType::WOOD)
            ->setNotCollectStatistics()
            ->setNameAndDescriptionId(StringIDs::StandingBanner,
                                      StringIDs::AHighlyCustomizableFreeStandingDecorationCanBe));

    // Size: 0xB0u
    Block::registerBlock(
        177, L"wall_banner",
        (new WallBannerBlock())
            ->setIconName(L"planks_oak")
            ->setDestroyTime(1.0)
            ->setSoundType(SoundType::WOOD)
            ->setNotCollectStatistics()
            ->setNameAndDescriptionId(StringIDs::HangingBanner,
                                      StringIDs::AHighlyCustomizableDecorationAttachedToABlock));

    // Size: 0xD0u
    Block::registerBlock(178, L"daylight_detector_inverted",
                         (new DaylightDetectorBlock(true))
                             ->setIconName(L"daylight_detector")
                             ->setNameAndDescriptionId(StringIDs::DaylightSensor,
                                                       StringIDs::ABlockThatOutputsARedstoneSignalBased));

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
    Block::registerBlock(181, L"double_stone_slab2",
                         (new FullNewStoneSlabBlock())
                             ->setIconName(L"double_stone_slab2")
                             ->setDestroyTime(2.0)
                             ->setExplodeable(10.0)
                             ->setSoundType(SoundType::STONE)
                             ->setNameAndDescriptionId(StringIDs::RedSandstoneSlab,
                                                       StringIDs::UsedForMakingLongStaircasesTwoSlabsPlaced_4)
                             ->setBaseItemTypeAndMaterial(21, 48));

    // Size: 0xB0u
    Block::registerBlock(182, L"stone_slab2",
                         (new HalfNewStoneSlabBlock())
                             ->setIconName(L"stone_slab2")
                             ->setDestroyTime(2.0)
                             ->setExplodeable(10.0)
                             ->setSoundType(SoundType::STONE)
                             ->setNameAndDescriptionId(StringIDs::RedSandstoneSlab,
                                                       StringIDs::UsedForMakingLongStaircasesTwoSlabsPlaced_4)
                             ->setBaseItemTypeAndMaterial(22, 48));

    // Size: 0xC0u
    Block::registerBlock(183, L"spruce_fence_gate",
                         (new FenceGateBlock(L"planks_spruce", PlanksBlock::Variant::SPRUCE))
                             ->setIconName(L"fenceGate")
                             ->setDestroyTime(2.0)
                             ->setExplodeable(5.0)
                             ->setSoundType(SoundType::WOOD)
                             ->sendBlockData(15)
                             ->setNameAndDescriptionId(StringIDs::SpruceFenceGate,
                                                       StringIDs::SimilarToADoorButUsedPrimarilyWithFences)
                             ->setBaseItemTypeAndMaterial(47, 39));

    // Size: 0xC0u
    Block::registerBlock(184, L"birch_fence_gate",
                         (new FenceGateBlock(L"planks_birch", PlanksBlock::Variant::BIRCH))
                             ->setIconName(L"fenceGate")
                             ->setDestroyTime(2.0)
                             ->setExplodeable(5.0)
                             ->setSoundType(SoundType::WOOD)
                             ->sendBlockData(15)
                             ->setNameAndDescriptionId(StringIDs::BirchFenceGate,
                                                       StringIDs::SimilarToADoorButUsedPrimarilyWithFences)
                             ->setBaseItemTypeAndMaterial(47, 40));

    // Size: 0xC0u
    Block::registerBlock(185, L"jungle_fence_gate",
                         (new FenceGateBlock(L"planks_jungle", PlanksBlock::Variant::JUNGLE))
                             ->setIconName(L"fenceGate")
                             ->setDestroyTime(2.0)
                             ->setExplodeable(5.0)
                             ->setSoundType(SoundType::WOOD)
                             ->sendBlockData(15)
                             ->setNameAndDescriptionId(StringIDs::JungleFenceGate,
                                                       StringIDs::SimilarToADoorButUsedPrimarilyWithFences)
                             ->setBaseItemTypeAndMaterial(47, 41));

    // Size: 0xC0u
    Block::registerBlock(186, L"dark_oak_fence_gate",
                         (new FenceGateBlock(L"planks_big_oak", PlanksBlock::Variant::DARK_OAK))
                             ->setIconName(L"fenceGate")
                             ->setDestroyTime(2.0)
                             ->setExplodeable(5.0)
                             ->setSoundType(SoundType::WOOD)
                             ->sendBlockData(15)
                             ->setNameAndDescriptionId(StringIDs::DarkOakFenceGate,
                                                       StringIDs::SimilarToADoorButUsedPrimarilyWithFences)
                             ->setBaseItemTypeAndMaterial(47, 42));

    // Size: 0xC0u
    Block::registerBlock(187, L"acacia_fence_gate",
                         (new FenceGateBlock(L"planks_acacia", PlanksBlock::Variant::ACACIA))
                             ->setIconName(L"fenceGate")
                             ->setDestroyTime(2.0)
                             ->setExplodeable(5.0)
                             ->setSoundType(SoundType::WOOD)
                             ->sendBlockData(15)
                             ->setNameAndDescriptionId(StringIDs::AcaciaFenceGate,
                                                       StringIDs::SimilarToADoorButUsedPrimarilyWithFences)
                             ->setBaseItemTypeAndMaterial(47, 43));

    // Size: 0xC0u
    Block::registerBlock(
        188, L"spruce_fence",
        (new FenceBlock(L"planks_spruce", Material::WOOD, PlanksBlock::Variant::SPRUCE->getMaterialColor()))
            ->setDestroyTime(2.0)
            ->setExplodeable(5.0)
            ->setSoundType(SoundType::WOOD)
            ->setNameAndDescriptionId(StringIDs::SpruceFence, StringIDs::UsedAsABarrierThatCannotBeJumped)
            ->setBaseItemTypeAndMaterial(29, 39));

    // Size: 0xC0u
    Block::registerBlock(
        189, L"birch_fence",
        (new FenceBlock(L"planks_birch", Material::WOOD, PlanksBlock::Variant::BIRCH->getMaterialColor()))
            ->setDestroyTime(2.0)
            ->setExplodeable(5.0)
            ->setSoundType(SoundType::WOOD)
            ->setNameAndDescriptionId(StringIDs::BirchFence, StringIDs::UsedAsABarrierThatCannotBeJumped)
            ->setBaseItemTypeAndMaterial(29, 40));

    // Size: 0xC0u
    Block::registerBlock(
        190, L"jungle_fence",
        (new FenceBlock(L"planks_jungle", Material::WOOD, PlanksBlock::Variant::JUNGLE->getMaterialColor()))
            ->setDestroyTime(2.0)
            ->setExplodeable(5.0)
            ->setSoundType(SoundType::WOOD)
            ->setNameAndDescriptionId(StringIDs::JungleFence, StringIDs::UsedAsABarrierThatCannotBeJumped)
            ->setBaseItemTypeAndMaterial(29, 41));

    // Size: 0xC0u
    Block::registerBlock(
        191, L"dark_oak_fence",
        (new FenceBlock(L"planks_big_oak", Material::WOOD,
                        PlanksBlock::Variant::DARK_OAK->getMaterialColor()))
            ->setDestroyTime(2.0)
            ->setExplodeable(5.0)
            ->setSoundType(SoundType::WOOD)
            ->setNameAndDescriptionId(StringIDs::DarkOakFence, StringIDs::UsedAsABarrierThatCannotBeJumped)
            ->setBaseItemTypeAndMaterial(29, 42));

    // Size: 0xC0u
    Block::registerBlock(
        192, L"acacia_fence",
        (new FenceBlock(L"planks_acacia", Material::WOOD, PlanksBlock::Variant::ACACIA->getMaterialColor()))
            ->setDestroyTime(2.0)
            ->setExplodeable(5.0)
            ->setSoundType(SoundType::WOOD)
            ->setNameAndDescriptionId(StringIDs::AcaciaFence, StringIDs::UsedAsABarrierThatCannotBeJumped)
            ->setBaseItemTypeAndMaterial(29, 43));

    // Size: 0xC8u
    Block::registerBlock(193, L"spruce_door",
                         (new DoorBlock(Material::WOOD))
                             ->setIconName(L"door_spruce")
                             ->setDestroyTime(3.0)
                             ->setSoundType(SoundType::WOOD)
                             ->setNotCollectStatistics()
                             ->sendBlockData(15)
                             ->setNameAndDescriptionId(StringIDs::SpruceDoor_1,
                                                       StringIDs::WoodenDoorsAreActivatedByUsingHittingmOr));

    // Size: 0xC8u
    Block::registerBlock(194, L"birch_door",
                         (new DoorBlock(Material::WOOD))
                             ->setIconName(L"door_birch")
                             ->setDestroyTime(3.0)
                             ->setSoundType(SoundType::WOOD)
                             ->setNotCollectStatistics()
                             ->sendBlockData(15)
                             ->setNameAndDescriptionId(StringIDs::BirchDoor_1,
                                                       StringIDs::WoodenDoorsAreActivatedByUsingHittingmOr));

    // Size: 0xC8u
    Block::registerBlock(195, L"jungle_door",
                         (new DoorBlock(Material::WOOD))
                             ->setIconName(L"door_jungle")
                             ->setDestroyTime(3.0)
                             ->setSoundType(SoundType::WOOD)
                             ->setNotCollectStatistics()
                             ->sendBlockData(15)
                             ->setNameAndDescriptionId(StringIDs::JungleDoor_1,
                                                       StringIDs::WoodenDoorsAreActivatedByUsingHittingmOr));

    // Size: 0xC8u
    Block::registerBlock(196, L"acacia_door",
                         (new DoorBlock(Material::WOOD))
                             ->setIconName(L"door_acacia")
                             ->setDestroyTime(3.0)
                             ->setSoundType(SoundType::WOOD)
                             ->setNotCollectStatistics()
                             ->sendBlockData(15)
                             ->setNameAndDescriptionId(StringIDs::AcaciaDoor_1,
                                                       StringIDs::WoodenDoorsAreActivatedByUsingHittingmOr));

    // Size: 0xC8u
    Block::registerBlock(197, L"dark_oak_door",
                         (new DoorBlock(Material::WOOD))
                             ->setIconName(L"door_dark_oak")
                             ->setDestroyTime(3.0)
                             ->setSoundType(SoundType::WOOD)
                             ->setNotCollectStatistics()
                             ->sendBlockData(15)
                             ->setNameAndDescriptionId(StringIDs::DarkOakDoor_1,
                                                       StringIDs::WoodenDoorsAreActivatedByUsingHittingmOr));

    // Size: 0xA8u
    Block::registerBlock(
        198, L"end_rod",
        (new EndRodBlock())
            ->setIconName(L"end_rod")
            ->setDestroyTime(0.0)
            ->setLightEmission(0.9375)
            ->setSoundType(SoundType::WOOD)
            ->setNameAndDescriptionId(StringIDs::EndRod, StringIDs::ADecorativeLightSourceFoundInEndCities));

    // Size: 0xA8u
    Block::registerBlock(
        199, L"chorus_plant",
        (new ChorusPlantBlock())
            ->setIconName(L"chorus_flower_plant")
            ->setDestroyTime(0.4)
            ->setSoundType(SoundType::WOOD)
            ->setNameAndDescriptionId(StringIDs::ChorusPlant,
                                      StringIDs::GrowsFromChorusFlowersSometimesDropsChorusFruit));

    // Size: 0xC0u
    Block::registerBlock(
        200, L"chorus_flower",
        (new ChorusFlowerBlock())
            ->setIconName(L"chorus_flower")
            ->setDestroyTime(0.4)
            ->setSoundType(SoundType::WOOD)
            ->setNameAndDescriptionId(StringIDs::ChorusFlower, StringIDs::CanBePlantedOnEndStoneToGrow));

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
    Block::registerBlock(
        202, L"purpur_pillar",
        (new RotatedPillarBlockImpl(Material::STONE, MaterialColor::COLOR_MAGENTA))
            ->setIconTopName(L"purpur_pillar_top")  // TODO
            ->setIconName(L"purpur_pillar")
            ->setDestroyTime(1.5)
            ->setExplodeable(10.0)
            ->setSoundType(SoundType::STONE)
            ->setNameAndDescriptionId(0xa7b0f2a, StringIDs::CanBeMinedWithAPickaxeOrCraftedPurpurSlabs)
            ->setBaseItemTypeAndMaterial(14, 62));

    // Size: 0xC0u
    Block::registerBlock(203, L"purpur_stairs",
                         (new StairBlock(purpurBlock->defaultBlockState()))
                             ->setNameAndDescriptionId(StringIDs::PurpurStairs, 0xdda0c93)
                             ->setBaseItemTypeAndMaterial(16, 62));

    // Size: 0xA8u
    Block::registerBlock(204, L"purpur_double_slab",
                         (new PurpurSlabBlockFull())
                             ->setDestroyTime(2.0)
                             ->setIconName(L"purpur_block")
                             ->setExplodeable(10.0)
                             ->setSoundType(SoundType::STONE)
                             ->setNameAndDescriptionId(StringIDs::PurpurSlab,
                                                       StringIDs::UsedForMakingLongStaircasesTwoSlabsPlaced_1)
                             ->setBaseItemTypeAndMaterial(21, 62));

    // Size: 0xA8u
    Block::registerBlock(205, L"purpur_slab",
                         (new PurpurSlabBlockHalf())
                             ->setDestroyTime(2.0)
                             ->setIconName(L"purpur_block")
                             ->setExplodeable(10.0)
                             ->setSoundType(SoundType::STONE)
                             ->setNameAndDescriptionId(StringIDs::PurpurSlab,
                                                       StringIDs::UsedForMakingLongStaircasesTwoSlabsPlaced_1)
                             ->setBaseItemTypeAndMaterial(22, 62));

    // Size: 0xA8u
    Block::registerBlock(206, L"end_bricks",
                         (new BlockImpl(Material::STONE, MaterialColor::SAND))
                             ->setSoundType(SoundType::STONE)
                             ->setDestroyTime(0.8)
                             ->setIconName(L"end_bricks")
                             ->setNameAndDescriptionId(StringIDs::EndStoneBricks,
                                                       StringIDs::CraftedFromEndStoneCanBeUsedAsDecoration)
                             ->setBaseItemTypeAndMaterial(14, 33));

    // Size: 0x110u
    Block::registerBlock(
        207, L"beetroots",
        (new BeetrootBlock())
            ->setIconName(L"beetroots")
            ->disableMipmap()
            ->setNameAndDescriptionId(StringIDs::Beetroots,
                                      StringIDs::Restores05IconShank01WhenEatenThisCanPlantedInFarmland));

    // Size: 0xB0u
    Block* grassPathBlock
        = (new GrassPathBlock())
              ->setDestroyTime(0.65)
              ->setSoundType(SoundType::GRASS)
              ->setIconName(L"grass_path")
              ->setNotCollectStatistics()
              ->setNameAndDescriptionId(StringIDs::GrassPath, StringIDs::ADecorativeBlockThatCanBeCreatedBy);
    Block::registerBlock(208, L"grass_path", grassPathBlock);

    // Size: 0xB0u
    Block::registerBlock(
        209, L"end_gateway",
        (new EndGatewayBlock(Material::PORTAL))
            ->setIconName(L"stone")
            ->setDestroyTime(3.4028e38)
            ->setExplodeable(6000000.0)
            ->setNameAndDescriptionId(StringIDs::EndGateway,
                                      StringIDs::GeneratedWhenEnderDragonIsKilledThrowingAn));

    // Size: 0xD8u
    Block::registerBlock(
        212, L"frosted_ice",
        (new FrostedIceBlock())
            ->setDestroyTime(0.5)
            ->setLightBlock(3)
            ->setSoundType(SoundType::GLASS)
            ->setNameAndDescriptionId(StringIDs::FrostedIce, StringIDs::ATypeOfIceThatMeltsQuickly));

    // Size: 0xA8u
    Block::registerBlock(
        213, L"magma",
        (new MagmaBlock())
            ->setDestroyTime(0.5)
            ->setSoundType(SoundType::STONE)
            ->setIconName(L"magma")
            ->setNameAndDescriptionId(StringIDs::MagmaBlock, StringIDs::CausesFireDamageWhenYouStandOnIt)
            ->setBaseItemTypeAndMaterial(32, 61));

    // Size: 0xA8u
    Block::registerBlock(214, L"nether_wart_block",
                         (new BlockImpl(Material::GRASS, MaterialColor::COLOR_RED))
                             ->setDestroyTime(1.0)
                             ->setSoundType(SoundType::WOOD)
                             ->setIconName(L"nether_wart_block")
                             ->setNameAndDescriptionId(StringIDs::NetherWartBlock,
                                                       StringIDs::ADecorativeBlockCraftedFromNetherWart)
                             ->setBaseItemTypeAndMaterial(32, 60));

    // Size: 0xA8u
    Block::registerBlock(215, L"red_nether_brick",
                         (new NetherBrickBlock())
                             ->setDestroyTime(2.0)
                             ->setExplodeable(10.0)
                             ->setSoundType(SoundType::STONE)
                             ->setIconName(L"red_nether_brick")
                             ->setNameAndDescriptionId(StringIDs::RedNetherBrick,
                                                       StringIDs::CraftedFromNetherWartAndNetherBrickCan)
                             ->setBaseItemTypeAndMaterial(14, 32));

    // Size: 0xB0u
    Block::registerBlock(216, L"bone_block",
                         (new BoneBlock())
                             ->setIconName(L"bone_block")
                             ->setNameAndDescriptionId(StringIDs::BoneBlock,
                                                       StringIDs::CraftedFromBoneMealOrFoundUndergroundIn)
                             ->setBaseItemTypeAndMaterial(13, 59));

    // Size: 0xA8u
    Block::registerBlock(217, L"structure_void",
                         (new StructureVoidBlock())
                             ->setIconName(L"structure_block")
                             ->setNameAndDescriptionId(0xFFFFFFFF, 0xFFFFFFFF));

    // Size: 0xD0u
    Block::registerBlock(218, L"observer",
                         (new ObserverBlock())
                             ->setDestroyTime(3.0)
                             ->setNameAndDescriptionId(StringIDs::Observer,
                                                       StringIDs::EmitsARedstoneSignalWhenAdjacentBlocksAre));

    // Size: 0xB8u
    Block::registerBlock(219, L"white_shulker_box",
                         (new ShulkerBoxBlock(DyeColor::WHITE))
                             ->setIconName(L"shulker_top")
                             ->setDestroyTime(2.0)
                             ->setSoundType(SoundType::STONE)
                             ->setNameAndDescriptionId(StringIDs::WhiteShulkerBox,
                                                       StringIDs::ASpecialKindOfChestThatCanContain)
                             ->setBaseItemTypeAndMaterial(36, 70));

    // Size: 0xB8u
    Block::registerBlock(220, L"orange_shulker_box",
                         (new ShulkerBoxBlock(DyeColor::ORANGE))
                             ->setIconName(L"shulker_top")
                             ->setDestroyTime(2.0)
                             ->setSoundType(SoundType::STONE)
                             ->setNameAndDescriptionId(StringIDs::OrangeShulkerBox,
                                                       StringIDs::ASpecialKindOfChestThatCanContain)
                             ->setBaseItemTypeAndMaterial(36, 70));

    // Size: 0xB8u
    Block::registerBlock(221, L"magenta_shulker_box",
                         (new ShulkerBoxBlock(DyeColor::MAGENTA))
                             ->setIconName(L"shulker_top")
                             ->setDestroyTime(2.0)
                             ->setSoundType(SoundType::STONE)
                             ->setNameAndDescriptionId(StringIDs::MagentaShulkerBox,
                                                       StringIDs::ASpecialKindOfChestThatCanContain)
                             ->setBaseItemTypeAndMaterial(36, 70));

    // Size: 0xB8u
    Block::registerBlock(222, L"light_blue_shulker_box",
                         (new ShulkerBoxBlock(DyeColor::LIGHT_BLUE))
                             ->setIconName(L"shulker_top")
                             ->setDestroyTime(2.0)
                             ->setSoundType(SoundType::STONE)
                             ->setNameAndDescriptionId(StringIDs::LightBlueShulkerBox,
                                                       StringIDs::ASpecialKindOfChestThatCanContain)
                             ->setBaseItemTypeAndMaterial(36, 70));

    // Size: 0xB8u
    Block::registerBlock(223, L"yellow_shulker_box",
                         (new ShulkerBoxBlock(DyeColor::YELLOW))
                             ->setIconName(L"shulker_top")
                             ->setDestroyTime(2.0)
                             ->setSoundType(SoundType::STONE)
                             ->setNameAndDescriptionId(StringIDs::YellowShulkerBox,
                                                       StringIDs::ASpecialKindOfChestThatCanContain)
                             ->setBaseItemTypeAndMaterial(36, 70));

    // Size: 0xB8u
    Block::registerBlock(
        224, L"lime_shulker_box",
        (new ShulkerBoxBlock(DyeColor::LIME))
            ->setIconName(L"shulker_top")
            ->setDestroyTime(2.0)
            ->setSoundType(SoundType::STONE)
            ->setNameAndDescriptionId(StringIDs::LimeShulkerBox, StringIDs::ASpecialKindOfChestThatCanContain)
            ->setBaseItemTypeAndMaterial(36, 70));

    // Size: 0xB8u
    Block::registerBlock(
        225, L"pink_shulker_box",
        (new ShulkerBoxBlock(DyeColor::PINK))
            ->setIconName(L"shulker_top")
            ->setDestroyTime(2.0)
            ->setSoundType(SoundType::STONE)
            ->setNameAndDescriptionId(StringIDs::PinkShulkerBox, StringIDs::ASpecialKindOfChestThatCanContain)
            ->setBaseItemTypeAndMaterial(36, 70));

    // Size: 0xB8u
    Block::registerBlock(
        226, L"gray_shulker_box",
        (new ShulkerBoxBlock(DyeColor::GRAY))
            ->setIconName(L"shulker_top")
            ->setDestroyTime(2.0)
            ->setSoundType(SoundType::STONE)
            ->setNameAndDescriptionId(StringIDs::GrayShulkerBox, StringIDs::ASpecialKindOfChestThatCanContain)
            ->setBaseItemTypeAndMaterial(36, 70));

    // Size: 0xB8u
    Block::registerBlock(227, L"silver_shulker_box",
                         (new ShulkerBoxBlock(DyeColor::SILVER))
                             ->setIconName(L"shulker_top")
                             ->setDestroyTime(2.0)
                             ->setSoundType(SoundType::STONE)
                             ->setNameAndDescriptionId(StringIDs::LightGrayShulkerBox,
                                                       StringIDs::ASpecialKindOfChestThatCanContain)
                             ->setBaseItemTypeAndMaterial(36, 70));

    // Size: 0xB8u
    Block::registerBlock(
        228, L"cyan_shulker_box",
        (new ShulkerBoxBlock(DyeColor::CYAN))
            ->setIconName(L"shulker_top")
            ->setDestroyTime(2.0)
            ->setSoundType(SoundType::STONE)
            ->setNameAndDescriptionId(StringIDs::CyanShulkerBox, StringIDs::ASpecialKindOfChestThatCanContain)
            ->setBaseItemTypeAndMaterial(36, 70));

    // Size: 0xB8u
    Block::registerBlock(229, L"purple_shulker_box",
                         (new ShulkerBoxBlock(DyeColor::PURPLE))
                             ->setIconName(L"shulker_top")
                             ->setDestroyTime(2.0)
                             ->setSoundType(SoundType::STONE)
                             ->setNameAndDescriptionId(StringIDs::PurpleShulkerBox,
                                                       StringIDs::ASpecialKindOfChestThatCanContain)
                             ->setBaseItemTypeAndMaterial(36, 70));

    // Size: 0xB8u
    Block::registerBlock(
        230, L"blue_shulker_box",
        (new ShulkerBoxBlock(DyeColor::BLUE))
            ->setIconName(L"shulker_top")
            ->setDestroyTime(2.0)
            ->setSoundType(SoundType::STONE)
            ->setNameAndDescriptionId(StringIDs::BlueShulkerBox, StringIDs::ASpecialKindOfChestThatCanContain)
            ->setBaseItemTypeAndMaterial(36, 70));

    // Size: 0xB8u
    Block::registerBlock(231, L"brown_shulker_box",
                         (new ShulkerBoxBlock(DyeColor::BROWN))
                             ->setIconName(L"shulker_top")
                             ->setDestroyTime(2.0)
                             ->setSoundType(SoundType::STONE)
                             ->setNameAndDescriptionId(StringIDs::BrownShulkerBox,
                                                       StringIDs::ASpecialKindOfChestThatCanContain)
                             ->setBaseItemTypeAndMaterial(36, 70));

    // Size: 0xB8u
    Block::registerBlock(232, L"green_shulker_box",
                         (new ShulkerBoxBlock(DyeColor::GREEN))
                             ->setIconName(L"shulker_top")
                             ->setDestroyTime(2.0)
                             ->setSoundType(SoundType::STONE)
                             ->setNameAndDescriptionId(StringIDs::GreenShulkerBox,
                                                       StringIDs::ASpecialKindOfChestThatCanContain)
                             ->setBaseItemTypeAndMaterial(36, 70));

    // Size: 0xB8u
    Block::registerBlock(
        233, L"red_shulker_box",
        (new ShulkerBoxBlock(DyeColor::RED))
            ->setIconName(L"shulker_top")
            ->setDestroyTime(2.0)
            ->setSoundType(SoundType::STONE)
            ->setNameAndDescriptionId(StringIDs::RedShulkerBox, StringIDs::ASpecialKindOfChestThatCanContain)
            ->setBaseItemTypeAndMaterial(36, 70));

    // Size: 0xB8u
    Block::registerBlock(
        234, L"black_shulker_box",
        (new ShulkerBoxBlock(DyeColor::BLACK))
            ->setIconName(L"shulker_top")
            ->setDestroyTime(2.0)
            ->setSoundType(SoundType::STONE)
            ->setNameAndDescriptionId(0xc17c633, StringIDs::ASpecialKindOfChestThatCanContain)
            ->setBaseItemTypeAndMaterial(36, 70));

    // Size: 0xA8u
    Block::registerBlock(
        235, L"white_glazed_terracotta",
        (new GlazedTerracottaBlock(DyeColor::WHITE))
            ->setIconName(L"glazed_terracotta_white")
            ->setNameAndDescriptionId(StringIDs::WhiteGlazedTerracotta,
                                      StringIDs::ADecorativeBlockCreatedByBakingWhiteTerracotta));

    // Size: 0xA8u
    Block::registerBlock(
        236, L"orange_glazed_terracotta",
        (new GlazedTerracottaBlock(DyeColor::ORANGE))
            ->setIconName(L"glazed_terracotta_orange")
            ->setNameAndDescriptionId(StringIDs::OrangeGlazedTerracotta,
                                      StringIDs::ADecorativeBlockCreatedByBakingOrangeTerracotta));

    // Size: 0xA8u
    Block::registerBlock(237, L"magenta_glazed_terracotta",
                         (new GlazedTerracottaBlock(DyeColor::MAGENTA))
                             ->setIconName(L"glazed_terracotta_magenta")
                             ->setNameAndDescriptionId(StringIDs::MagentaGlazedTerracotta, 0x7b8dd58));

    // Size: 0xA8u
    Block::registerBlock(238, L"light_blue_glazed_terracotta",
                         (new GlazedTerracottaBlock(DyeColor::LIGHT_BLUE))
                             ->setIconName(L"glazed_terracotta_light_blue")
                             ->setNameAndDescriptionId(StringIDs::LightBlueGlazedTerracotta,
                                                       StringIDs::ADecorativeBlockCreatedByBakingLightBlue));

    // Size: 0xA8u
    Block::registerBlock(
        239, L"yellow_glazed_terracotta",
        (new GlazedTerracottaBlock(DyeColor::YELLOW))
            ->setIconName(L"glazed_terracotta_yellow")
            ->setNameAndDescriptionId(StringIDs::YellowGlazedTerracotta,
                                      StringIDs::ADecorativeBlockCreatedByBakingYellowTerracotta));

    // Size: 0xA8u
    Block::registerBlock(
        240, L"lime_glazed_terracotta",
        (new GlazedTerracottaBlock(DyeColor::LIME))
            ->setIconName(L"glazed_terracotta_lime")
            ->setNameAndDescriptionId(StringIDs::LimeGlazedTerracotta,
                                      StringIDs::ADecorativeBlockCreatedByBakingLimeTerracotta));

    // Size: 0xA8u
    Block::registerBlock(
        241, L"pink_glazed_terracotta",
        (new GlazedTerracottaBlock(DyeColor::PINK))
            ->setIconName(L"glazed_terracotta_pink")
            ->setNameAndDescriptionId(StringIDs::PinkGlazedTerracotta,
                                      StringIDs::ADecorativeBlockCreatedByBakingPinkTerracotta));

    // Size: 0xA8u
    Block::registerBlock(
        242, L"gray_glazed_terracotta",
        (new GlazedTerracottaBlock(DyeColor::GRAY))
            ->setIconName(L"glazed_terracotta_gray")
            ->setNameAndDescriptionId(0xa10f3e, StringIDs::ADecorativeBlockCreatedByBakingGrayTerracotta));

    // Size: 0xA8u
    Block::registerBlock(243, L"silver_glazed_terracotta",
                         (new GlazedTerracottaBlock(DyeColor::SILVER))
                             ->setIconName(L"glazed_terracotta_silver")
                             ->setNameAndDescriptionId(StringIDs::LightGrayGlazedTerracotta,
                                                       StringIDs::ADecorativeBlockCreatedByBakingLightGray));

    // Size: 0xA8u
    Block::registerBlock(
        244, L"cyan_glazed_terracotta",
        (new GlazedTerracottaBlock(DyeColor::CYAN))
            ->setIconName(L"glazed_terracotta_cyan")
            ->setNameAndDescriptionId(0x22f7636, StringIDs::ADecorativeBlockCreatedByBakingCyanTerracotta));

    // Size: 0xA8u
    Block::registerBlock(
        245, L"purple_glazed_terracotta",
        (new GlazedTerracottaBlock(DyeColor::PURPLE))
            ->setIconName(L"glazed_terracotta_purple")
            ->setNameAndDescriptionId(StringIDs::PurpleGlazedTerracotta,
                                      StringIDs::ADecorativeBlockCreatedByBakingPurpleTerracotta));

    // Size: 0xA8u
    Block::registerBlock(
        246, L"blue_glazed_terracotta",
        (new GlazedTerracottaBlock(DyeColor::BLUE))
            ->setIconName(L"glazed_terracotta_blue")
            ->setNameAndDescriptionId(StringIDs::BlueGlazedTerracotta,
                                      StringIDs::ADecorativeBlockCreatedByBakingBlueTerracotta));

    // Size: 0xA8u
    Block::registerBlock(
        247, L"brown_glazed_terracotta",
        (new GlazedTerracottaBlock(DyeColor::BROWN))
            ->setIconName(L"glazed_terracotta_brown")
            ->setNameAndDescriptionId(StringIDs::BrownGlazedTerracotta,
                                      StringIDs::ADecorativeBlockCreatedByBakingBrownTerracotta));

    // Size: 0xA8u
    Block::registerBlock(
        248, L"green_glazed_terracotta",
        (new GlazedTerracottaBlock(DyeColor::GREEN))
            ->setIconName(L"glazed_terracotta_green")
            ->setNameAndDescriptionId(0x80fc468, StringIDs::ADecorativeBlockCreatedByBakingGreenTerracotta));

    // Size: 0xA8u
    Block::registerBlock(
        249, L"red_glazed_terracotta",
        (new GlazedTerracottaBlock(DyeColor::RED))
            ->setIconName(L"glazed_terracotta_red")
            ->setNameAndDescriptionId(StringIDs::RedGlazedTerracotta,
                                      StringIDs::ADecorativeBlockCreatedByBakingRedTerracotta));

    // Size: 0xA8u
    Block::registerBlock(
        250, L"black_glazed_terracotta",
        (new GlazedTerracottaBlock(DyeColor::BLACK))
            ->setIconName(L"glazed_terracotta_black")
            ->setNameAndDescriptionId(StringIDs::BlackGlazedTerracotta,
                                      StringIDs::ADecorativeBlockCreatedByBakingBlackTerracotta));

    // Size: 0x128u
    Block::registerBlock(
        251, L"concrete",
        (new ColoredBlock(Material::STONE))
            ->setDestroyTime(1.8)
            ->setSoundType(SoundType::STONE)
            ->setIconName(L"concrete")
            ->setNameAndDescriptionId(StringIDs::BlackConcrete, StringIDs::CanBeMinedWithAPickaxeOrCreated));

    // Size: 0x128u
    Block::registerBlock(252, L"concrete_powder",
                         (new ConcretePowderBlock())
                             ->setDestroyTime(0.5)
                             ->setSoundType(SoundType::SAND)
                             ->setIconName(L"concrete_powder")
                             ->setNameAndDescriptionId(StringIDs::BlackConcretePowder,
                                                       StringIDs::TurnsIntoConcreteAfterComingIntoContactWith)
                             ->setBaseItemTypeAndMaterial(57, 69));

    // Size: 0xA8u
    Block::registerBlock(255, L"structure_block",
                         (new StructureBlock())
                             ->setIconName(L"structure_block")
                             ->setIndestructible()
                             ->setExplodeable(6000000.0)
                             ->setNameAndDescriptionId(0xFFFFFFFF, 0xFFFFFFFF));

    std::unordered_map<ResourceLocation, Block*>* blocks = Blocks::Registry->keySet();
    for (auto& entry : *blocks) {
        Block* block = entry.second;
        if (block->m_material == Material::AIR) {
            block->m_field3C = 0;
        } else {
            StairBlock* s = dynamic_cast<StairBlock*>(block);
            HalfSlabBlock* b = dynamic_cast<HalfSlabBlock*>(block);
            if (block == farmBlock || block == grassPathBlock || !s || b)
                block->m_field3C = block->m_lightEmission == 0 || block->m_isBlocksLight;
            else
                block->m_field3C = 1;

            for (int i = 0; i < 16; i++)
                block->getBlockState(i);
        }
    }

    for (auto& entry : *blocks) {
        Block* block = entry.second;
        arrayWithLength<const BlockState*> blockStates
            = *(block->getBlockStateDefinition()->getPossibleBlockStates());
        for (int i = 0; i < blockStates.m_length; i++) {
            const BlockState* state = blockStates[i];
            if (state) {
                int id = Blocks::Registry->getId(block);
                sBlockStateMapper->addMapping(state, block->convertBlockStateToLegacyData(state) | (16 * id));
            }
        }
    }

    Stats::buildItemStats();
}
