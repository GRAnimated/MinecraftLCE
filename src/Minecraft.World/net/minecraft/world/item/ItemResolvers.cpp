#include "net/minecraft/world/item/ItemResolvers.h"

#include "net/minecraft/client/ui/StringIDs.h"
#include "net/minecraft/world/item/DyeColor.h"
#include "net/minecraft/world/item/ItemInstance.h"
#include "net/minecraft/world/level/block/Blocks.h"
#include "net/minecraft/world/level/block/DirtBlock.h"
#include "net/minecraft/world/level/block/DoublePlantBlock.h"
#include "net/minecraft/world/level/block/FlowerBlock.h"
#include "net/minecraft/world/level/block/MonsterEggBlock.h"
#include "net/minecraft/world/level/block/NewLogBlock.h"
#include "net/minecraft/world/level/block/OldLogBlock.h"
#include "net/minecraft/world/level/block/PlanksBlock.h"
#include "net/minecraft/world/level/block/PrismarineBlock.h"
#include "net/minecraft/world/level/block/RedSandStoneBlock.h"
#include "net/minecraft/world/level/block/SandBlock.h"
#include "net/minecraft/world/level/block/SandStoneBlock.h"
#include "net/minecraft/world/level/block/SpongeBlock.h"
#include "net/minecraft/world/level/block/StoneBlock.h"
#include "net/minecraft/world/level/block/StoneBrickBlock.h"
#include "net/minecraft/world/level/block/WallBlock.h"
#include "net/minecraft/world/level/block/state/BlockState.h"
#include "net/minecraft/world/level/block/state/BooleanProperty.h"

BooleanProperty* SpongeBlock::WET;  // name guessed

namespace ItemResolvers {
extern const unsigned int LOG_NAMES[6] = {
    StringIDs::OakWood,    StringIDs::SpruceWood, StringIDs::BirchWood,
    StringIDs::JungleWood, StringIDs::AcaciaWood, StringIDs::DarkOakWood,
};

const unsigned int ANVIL_NAMES[3] = {
    StringIDs::BlockOfQuartz,
    StringIDs::ChiseledQuartzBlock,
    StringIDs::PillarQuartzBlock,
};

const unsigned int WOOL_NAMES[16] = {
    StringIDs::BlackWool,     StringIDs::RedWool,     StringIDs::GreenWool,  StringIDs::BrownWool,
    StringIDs::BlueWool,      StringIDs::PurpleWool,  StringIDs::CyanWool,   StringIDs::LightGrayWool,
    StringIDs::GrayWool,      StringIDs::PinkWool,    StringIDs::LimeWool,   StringIDs::YellowWool,
    StringIDs::LightBlueWool, StringIDs::MagentaWool, StringIDs::OrangeWool, StringIDs::WhiteWool,
};

const unsigned int STAINEDCLAY_NAMES[16] = {
    StringIDs::BlackTerracotta,     StringIDs::RedTerracotta,       StringIDs::GreenTerracotta,
    StringIDs::BrownTerracotta,     StringIDs::BlueTerracotta,      StringIDs::PurpleTerracotta,
    StringIDs::CyanTerracotta,      StringIDs::LightGrayTerracotta, StringIDs::GrayTerracotta,
    StringIDs::PinkTerracotta,      StringIDs::LimeTerracotta,      StringIDs::YellowTerracotta,
    StringIDs::LightBlueTerracotta, StringIDs::MagentaTerracotta,   StringIDs::OrangeTerracotta,
    StringIDs::WhiteTerracotta,
};

const unsigned int STAINEDGLASSPANE_NAMES[16] = {
    StringIDs::BlackCarpet,     StringIDs::RedCarpet,     StringIDs::GreenCarpet,  StringIDs::BrownCarpet,
    StringIDs::BlueCarpet,      StringIDs::PurpleCarpet,  StringIDs::CyanCarpet,   StringIDs::LightGrayCarpet,
    StringIDs::GrayCarpet,      StringIDs::PinkCarpet,    StringIDs::LimeCarpet,   StringIDs::YellowCarpet,
    StringIDs::LightBlueCarpet, StringIDs::MagentaCarpet, StringIDs::OrangeCarpet, StringIDs::WhiteCarpet,
};

const unsigned int CARPET_NAMES[16] = {
    StringIDs::BlackStainedGlass,     StringIDs::RedStainedGlass,       StringIDs::GreenStainedGlass,
    StringIDs::BrownStainedGlass,     StringIDs::BlueStainedGlass,      StringIDs::PurpleStainedGlass,
    StringIDs::CyanStainedGlass,      StringIDs::LightGrayStainedGlass, StringIDs::GrayStainedGlass,
    StringIDs::PinkStainedGlass,      StringIDs::LimeStainedGlass,      StringIDs::YellowStainedGlass,
    StringIDs::LightBlueStainedGlass, StringIDs::MagentaStainedGlass,   StringIDs::OrangeStainedGlass,
    StringIDs::WhiteStainedGlass,
};

const unsigned int STAINEDGLASS_NAMES[16] = {
    StringIDs::BlackStainedGlassPane,     StringIDs::RedStainedGlassPane,
    StringIDs::GreenStainedGlassPane,     StringIDs::BrownStainedGlassPane,
    StringIDs::BlueStainedGlassPane,      StringIDs::PurpleStainedGlassPane,
    StringIDs::CyanStainedGlassPane,      StringIDs::LightGrayStainedGlassPane,
    StringIDs::GrayStainedGlassPane,      StringIDs::PinkStainedGlassPane,
    StringIDs::LimeStainedGlassPane,      StringIDs::YellowStainedGlassPane,
    StringIDs::LightBlueStainedGlassPane, StringIDs::MagentaStainedGlassPane,
    StringIDs::OrangeStainedGlassPane,    StringIDs::WhiteStainedGlassPane,
};

const unsigned int CONCRETE_NAMES[16] = {
    StringIDs::BlackConcrete,     StringIDs::RedConcrete,       StringIDs::GreenConcrete,
    StringIDs::BrownConcrete,     StringIDs::BlueConcrete,      StringIDs::PurpleConcrete,
    StringIDs::CyanConcrete,      StringIDs::LightGrayConcrete, StringIDs::GrayConcrete,
    StringIDs::PinkConcrete,      StringIDs::LimeConcrete,      StringIDs::YellowConcrete,
    StringIDs::LightBlueConcrete, StringIDs::MagentaConcrete,   StringIDs::OrangeConcrete,
    StringIDs::WhiteConcrete,
};

const unsigned int CONCRETEPOWDER_NAMES[16] = {
    StringIDs::BlackConcretePowder,     StringIDs::RedConcretePowder,       StringIDs::GreenConcretePowder,
    StringIDs::BrownConcretePowder,     StringIDs::BlueConcretePowder,      StringIDs::PurpleConcretePowder,
    StringIDs::CyanConcretePowder,      StringIDs::LightGrayConcretePowder, StringIDs::GrayConcretePowder,
    StringIDs::PinkConcretePowder,      StringIDs::LimeConcretePowder,      StringIDs::YellowConcretePowder,
    StringIDs::LightBlueConcretePowder, StringIDs::MagentaConcretePowder,   StringIDs::OrangeConcretePowder,
    StringIDs::WhiteConcretePowder,
};

}  // namespace ItemResolvers

unsigned int Item::StoneBlockNameResolver(not_null_ptr<ItemInstance> item) {
    return StoneBlock::Variant::byData(item->getAuxValue())->getNameId();
}

unsigned int Item::StoneBlockDescResolver(not_null_ptr<ItemInstance> item) {
    return StoneBlock::Variant::byData(item->getAuxValue())->getDescriptionId();
}

// name guessed
unsigned int ItemResolvers::DirtBlockName(not_null_ptr<ItemInstance> item) {
    return DirtBlock::Variant::byData(item->getAuxValue())->getNameId();
}

// name guessed
unsigned int ItemResolvers::DirtBlockDesc(not_null_ptr<ItemInstance> item) {
    return DirtBlock::Variant::byData(item->getAuxValue())->getDescriptionId();
}

// name guessed
unsigned int ItemResolvers::PlanksBlockName(not_null_ptr<ItemInstance> item) {
    return PlanksBlock::Variant::byData(item->getAuxValue())->getNameId();
}

// name guessed
unsigned int ItemResolvers::SandBlockName(not_null_ptr<ItemInstance> item) {
    return SandBlock::Variant::byData(item->getAuxValue())->getNameId();
}

// name guessed
unsigned int ItemResolvers::SandBlockDesc(not_null_ptr<ItemInstance> item) {
    return SandBlock::Variant::byData(item->getAuxValue())->getDescriptionId();
}

// name guessed
unsigned int ItemResolvers::SandStoneBlockName(not_null_ptr<ItemInstance> item) {
    return SandStoneBlock::Variant::byData(item->getAuxValue())->getNameId();
}

// name guessed
unsigned int ItemResolvers::MonsterEggBlockName(not_null_ptr<ItemInstance> item) {
    return MonsterEggBlock::Variant::byData(item->getAuxValue())->getTranslationKey();
}

// name guessed
unsigned int ItemResolvers::StoneBrickBlockName(not_null_ptr<ItemInstance> item) {
    return StoneBrickBlock::Variant::byData(item->getAuxValue())->getTranslationKey();
}

// name guessed
unsigned int ItemResolvers::WallBlockName(not_null_ptr<ItemInstance> item) {
    return WallBlock::Variant::byData(item->getAuxValue())->getNameId();
}

// name guessed
unsigned int ItemResolvers::DoublePlantBlockName(not_null_ptr<ItemInstance> item) {
    return DoublePlantBlock::Variant::byData(item->getAuxValue())->getNameId();
}

// name guessed
unsigned int ItemResolvers::DoublePlantBlockDesc(not_null_ptr<ItemInstance> item) {
    return DoublePlantBlock::Variant::byData(item->getAuxValue())->getDescriptionId();
}

// name guessed
unsigned int ItemResolvers::PrismarineBlockName(not_null_ptr<ItemInstance> item) {
    return PrismarineBlock::Variant::byData(item->getAuxValue())->getNameId();
}

// name guessed
unsigned int ItemResolvers::PrismarineBlockDesc(not_null_ptr<ItemInstance> item) {
    return PrismarineBlock::Variant::byData(item->getAuxValue())->getDescriptionId();
}

// name guessed
unsigned int ItemResolvers::RedSandStoneBlockName(not_null_ptr<ItemInstance> item) {
    return RedSandStoneBlock::Variant::byData(item->getAuxValue())->getNameId();
}

// name guessed
unsigned int ItemResolvers::WoolName(not_null_ptr<ItemInstance> item) {
    return WOOL_NAMES[DyeColor::byItemData(item->getAuxValue())->getBlockData()];
}

// name guessed
unsigned int ItemResolvers::StainedClayName(not_null_ptr<ItemInstance> item) {
    return STAINEDCLAY_NAMES[DyeColor::byItemData(item->getAuxValue())->getBlockData()];
}

// name guessed
unsigned int ItemResolvers::StainedGlassPaneName(not_null_ptr<ItemInstance> item) {
    return STAINEDGLASSPANE_NAMES[DyeColor::byItemData(item->getAuxValue())->getBlockData()];
}

// name guessed
unsigned int ItemResolvers::CarpetName(not_null_ptr<ItemInstance> item) {
    return CARPET_NAMES[DyeColor::byItemData(item->getAuxValue())->getBlockData()];
}

// name guessed
unsigned int ItemResolvers::StainedGlassName(not_null_ptr<ItemInstance> item) {
    return STAINEDGLASS_NAMES[DyeColor::byItemData(item->getAuxValue())->getBlockData()];
}

// name guessed
unsigned int ItemResolvers::ConcreteName(not_null_ptr<ItemInstance> item) {
    return CONCRETE_NAMES[DyeColor::byItemData(item->getAuxValue())->getBlockData()];
}

// name guessed
unsigned int ItemResolvers::ConcretePowderName(not_null_ptr<ItemInstance> item) {
    return CONCRETEPOWDER_NAMES[DyeColor::byItemData(item->getAuxValue())->getBlockData()];
}

// name guessed
unsigned int ItemResolvers::SaplingName(not_null_ptr<ItemInstance> item) {
    return Blocks::SAPLING->getDescriptionId(item->getAuxValue());
}

// name guessed
unsigned int ItemResolvers::LogName(not_null_ptr<ItemInstance> item) {
    return LOG_NAMES[Blocks::LOG->getBlockState(item->getAuxValue())
                         ->getValue<PlanksBlock::Variant*>(OldLogBlock::VARIANT)
                         ->getData()];
}

// name guessed
unsigned int ItemResolvers::Log2Name(not_null_ptr<ItemInstance> item) {
    return LOG_NAMES[Blocks::LOG2->getBlockState(item->getAuxValue())
                         ->getValue<PlanksBlock::Variant*>(NewLogBlock::VARIANT)
                         ->getData()];
}

// name guessed
unsigned int ItemResolvers::SpongeName(not_null_ptr<ItemInstance> item) {
    return Blocks::SPONGE->getBlockState(item->getAuxValue())->getValue<bool>(SpongeBlock::WET) ?
               StringIDs::WetSponge :
               StringIDs::Sponge;
}

// name guessed
unsigned int ItemResolvers::SpongeDesc(not_null_ptr<ItemInstance> item) {
    return Blocks::SPONGE->getBlockState(item->getAuxValue())->getValue<bool>(SpongeBlock::WET) ?
               StringIDs::CanBeDriedInAFurnaceAllowingSponge :
               StringIDs::CanAbsorbWaterNearbyTurningIntoAWet;
}

// name guessed
unsigned int ItemResolvers::FlowerName(not_null_ptr<ItemInstance> item) {
    FlowerBlock* block = static_cast<FlowerBlock*>(Block::byId(item->getItem()->getId()));
    return block->getBlockState(item->getAuxValue())
        ->getValue<FlowerBlock::Flower*>(block->m_flowerProperty)
        ->getNameId();
}

// name guessed
unsigned int ItemResolvers::FlowerDesc(not_null_ptr<ItemInstance> item) {
    FlowerBlock* block = static_cast<FlowerBlock*>(Block::byId(item->getItem()->getId()));
    return block->getBlockState(item->getAuxValue())
        ->getValue<FlowerBlock::Flower*>(block->m_flowerProperty)
        ->getDescriptionId();
}

// name guessed
unsigned int ItemResolvers::AnvilName(not_null_ptr<ItemInstance> item) {
    int aux = item->getAuxValue();
    return ANVIL_NAMES[static_cast<unsigned int>(aux) > 2 ? 0 : aux];
}
