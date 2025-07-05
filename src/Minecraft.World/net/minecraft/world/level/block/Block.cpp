#include "Minecraft.World/item/Item.h"

#include "Block.h"

#include "Minecraft.World/level/block/SoundType.h"
#include "Minecraft.World/level/block/state/BlockState.h"
#include "Minecraft.World/level/block/state/BlockStateDefinition.h"
#include "Minecraft.World/level/material/Material.h"

#include "AirBlock.h"
#include "AnvilBlock.h"
#include "BannerBlock.h"
#include "BedBlock.h"
#include "Blocks.h"
#include "ButtonBlock.h"
#include "ChestBlock.h"
#include "ColoredBlock.h"
#include "ComparatorBlock.h"
#include "ConcretePowderBlock.h"
#include "DetectorRailBlock.h"
#include "DirectionalBlock.h"
#include "DirtBlock.h"
#include "DispenserBlock.h"
#include "DoorBlock.h"
#include "DoublePlantBlock.h"
#include "EndPortalFrameBlock.h"
#include "EnderChestBlock.h"
#include "FlowerPotBlock.h"
#include "FurnaceBlock.h"
#include "HalfSlabBlock.h"
#include "HopperBlock.h"
#include "HorizontalDirectionalBlock.h"
#include "HugeMushroomBlock.h"
#include "LadderBlock.h"
#include "LeverBlock.h"
#include "LogBlock.h"
#include "MonsterEggBlock.h"
#include "NewLeafBlock.h"
#include "NewLogBlock.h"
#include "NewStoneSlabBlock.h"
#include "NoteBlock.h"
#include "OldLeafBlock.h"
#include "OldLogBlock.h"
#include "PistonBaseBlock.h"
#include "PistonHeadBlock.h"
#include "PistonMagicBlock.h"
#include "PlanksBlock.h"
#include "PortalBlock.h"
#include "PoweredRailBlock.h"
#include "PrismarineBlock.h"
#include "PurpurSlabBlock.h"
#include "QuartzBlock.h"
#include "RailBlock.h"
#include "RedSandStoneBlock.h"
#include "RedStoneWireBlock.h"
#include "RotatedPillarBlock.h"
#include "SandBlock.h"
#include "SandStoneBlock.h"
#include "SaplingBlock.h"
#include "SkullBlock.h"
#include "StainedGlassBlock.h"
#include "StainedGlassPaneBlock.h"
#include "StainedHardenedClayBlock.h"
#include "StairBlock.h"
#include "StemBlock.h"
#include "StoneBlock.h"
#include "StoneBrickBlock.h"
#include "StoneSlabBlock.h"
#include "TallGrassBlock.h"
#include "TorchBlock.h"
#include "TrapDoorBlock.h"
#include "TripWireHookBlock.h"
#include "WallBlock.h"
#include "WallSignBlock.h"
#include "WoodSlabBlock.h"
#include "WoolCarpetBlock.h"

Block::Block(Material* material) {
    init(material, material->getColor());
}

Block::Block(Material* material, const MaterialColor* color) {
    init(material, color);
}

const BlockState* Block::defaultBlockState() {
    return mBlockState;
}

void Block::registerDefaultState(const BlockState* blockState) {
    mBlockState = blockState;
}

void Block::init(Material* material, const MaterialColor* color) {
    field_A0 = 0;
    mExplosionResistance = 0.0f;
    mIsCollectStatistics = true;

    mSoundType = SoundType::STONE;

    mDestroyTime = 0.0f;
    mIsTicking = false;
    mIsSilkTouchable = false;
    field_60 = 1.0f;
    mFriction = 0.6f;
    mMaterial = material;
    mMapColor = color;
    mLightEmission = 0;

    bool isEnableLight = material->blocksLight();

    isDisableMipmap = true;
    isSemiTransparent = false;
    field_3C = false;
    mMaterialType = 0;
    mBaseItemType = 0;

    isBlocksLight = !isEnableLight;

    mTexture = nullptr;
    isInited = false;
    field_8 = 0;
    field_C = false;
}

void Block::DerivedInit() {
    isInited = true;

    mBlockStateDefinition = createBlockStateDefinition();
    registerDefaultState(mBlockStateDefinition->any());

    bool isSolidRender = defaultBlockState()->isSolidRender();
    field_28 = isSolidRender;
    lightEmission = isSolidRender ? 255 : 0;
}

Item* Block::getResource(const BlockState* blockState, Random*, int) {
    return Item::byBlock(this);
}

// does nothing
void Block::tick(Level* level, const BlockPos& pos, const BlockState* blockState, Random*) {}
void Block::animateTick(const BlockState* blockState, Level* level, const BlockPos& pos, Random*) {}
void Block::destroy(Level* level, const BlockPos& pos, const BlockState* blockState) {}
void Block::addLights(Level* level, const BlockPos& pos) {}
void Block::onPlace(Level* level, const BlockPos& pos, const BlockState* blockState) {}
void Block::stepOn(Level* level, const BlockPos& pos, std::shared_ptr<Entity>) {}
void Block::prepareRender(Level* level, const BlockPos& pos) {}
void Block::attack(Level* level, const BlockPos& pos, std::shared_ptr<Player> player) {}
void Block::entityInside(Level* level, const BlockPos& pos, const BlockState* blockState,
                         std::shared_ptr<Entity> const&) {}
void Block::playerWillDestroy(Level* level, const BlockPos& pos, const BlockState* blockState,
                              std::shared_ptr<Player> player) {}
void Block::handleRain(Level* level, const BlockPos& pos) {}
void Block::appendHoverText(not_null_ptr<ItemInstance>, std::shared_ptr<Player> player,
                            std::vector<HtmlString>*, bool) {}

// NON_MATCHING | Score: 1479270 (lower is better)
// This is the second-largest method in the entire executable
// It might be easier than it would seem, since most of it is just block registry
// but the main issue is that IDA does not give a clean enough decomp since every chained method creates a new lvar...
// To be able to see vftable calls, you have to set that lvar's type to Block *... for every single one (there's about 2000 lvars)
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

    Block *airBlock = (new AirBlock())->setNameAndDescriptionId(0xFFFFFFFF, 0xFFFFFFFF);
    registerBlock(0, *Blocks::AIR_RSRC, airBlock);

    Block *stoneBlock = (new StoneBlock())
        ->setDestroyTime(1.5)
        ->setExplodeable(10.0)
        ->setSoundType(SoundType::STONE)
        ->setIconName(L"stone")
        ->setNameAndDescriptionId(0x8BAD4DAC, 0x46782239);

    stoneBlock->setBaseItemTypeAndMaterial(14, 2);
    registerBlock(1, L"stone", stoneBlock);
}