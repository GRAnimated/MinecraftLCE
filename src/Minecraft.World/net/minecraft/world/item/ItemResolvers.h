#pragma once

#include "net/minecraft/world/item/Item.h"

/** Subtype callbacks referenced by Item::staticCtor. */
// name guessed: callback names describe their returned subtypes.
namespace ItemResolvers {
extern const unsigned int LOG_NAMES[6];
unsigned int DirtBlockName(not_null_ptr<ItemInstance>);
unsigned int DirtBlockDesc(not_null_ptr<ItemInstance>);
unsigned int PlanksBlockName(not_null_ptr<ItemInstance>);
unsigned int SandBlockName(not_null_ptr<ItemInstance>);
unsigned int SandBlockDesc(not_null_ptr<ItemInstance>);
unsigned int SandStoneBlockName(not_null_ptr<ItemInstance>);
unsigned int MonsterEggBlockName(not_null_ptr<ItemInstance>);
unsigned int StoneBrickBlockName(not_null_ptr<ItemInstance>);
unsigned int WallBlockName(not_null_ptr<ItemInstance>);
unsigned int DoublePlantBlockName(not_null_ptr<ItemInstance>);
unsigned int DoublePlantBlockDesc(not_null_ptr<ItemInstance>);
unsigned int PrismarineBlockName(not_null_ptr<ItemInstance>);
unsigned int PrismarineBlockDesc(not_null_ptr<ItemInstance>);
unsigned int RedSandStoneBlockName(not_null_ptr<ItemInstance>);
unsigned int WoolName(not_null_ptr<ItemInstance>);
unsigned int StainedClayName(not_null_ptr<ItemInstance>);
unsigned int StainedGlassPaneName(not_null_ptr<ItemInstance>);
unsigned int CarpetName(not_null_ptr<ItemInstance>);
unsigned int StainedGlassName(not_null_ptr<ItemInstance>);
unsigned int ConcreteName(not_null_ptr<ItemInstance>);
unsigned int ConcretePowderName(not_null_ptr<ItemInstance>);
unsigned int SaplingName(not_null_ptr<ItemInstance>);
unsigned int LogName(not_null_ptr<ItemInstance>);
unsigned int Log2Name(not_null_ptr<ItemInstance>);
unsigned int SpongeName(not_null_ptr<ItemInstance>);
unsigned int SpongeDesc(not_null_ptr<ItemInstance>);
unsigned int FlowerName(not_null_ptr<ItemInstance>);
unsigned int FlowerDesc(not_null_ptr<ItemInstance>);
unsigned int AnvilName(not_null_ptr<ItemInstance>);
}  // namespace ItemResolvers
