#include "net/minecraft/world/item/PickaxeItem.h"
#include "net/minecraft/world/level/block/Blocks.h"

arrayWithLength<Block*> PickaxeItem::DIGGABLES = arrayWithLength<Block*>(26, true);

void PickaxeItem::staticCtor() {
    DIGGABLES[0] = Blocks::ACTIVATOR_RAIL;
    DIGGABLES[1] = Blocks::COAL_ORE;
    DIGGABLES[2] = Blocks::COBBLESTONE;
    DIGGABLES[3] = Blocks::DETECTOR_RAIL;
    DIGGABLES[4] = Blocks::DIAMOND_BLOCK;
    DIGGABLES[5] = Blocks::DIAMOND_ORE;
    DIGGABLES[6] = Blocks::DOUBLE_STONE_SLAB;
    DIGGABLES[7] = Blocks::GOLDEN_RAIL;
    DIGGABLES[8] = Blocks::GOLD_BLOCK;
    DIGGABLES[9] = Blocks::GOLD_ORE;
    DIGGABLES[10] = Blocks::ICE;
    DIGGABLES[11] = Blocks::IRON_BLOCK;
    DIGGABLES[12] = Blocks::IRON_ORE;
    DIGGABLES[13] = Blocks::LAPIS_BLOCK;
    DIGGABLES[14] = Blocks::LAPIS_ORE;
    DIGGABLES[15] = Blocks::LIT_REDSTONE_ORE;
    DIGGABLES[16] = Blocks::MOSSY_COBBLESTONE;
    DIGGABLES[17] = Blocks::NETHERRACK;
    DIGGABLES[18] = Blocks::PACKED_ICE;
    DIGGABLES[19] = Blocks::RAIL;
    DIGGABLES[20] = Blocks::REDSTONE_ORE;
    
    // Block states maybe, since they are the same block id
    DIGGABLES[21] = Blocks::SANDSTONE;
    DIGGABLES[21] = Blocks::RED_SANDSTONE;
    DIGGABLES[22] = Blocks::STONE;
    DIGGABLES[23] = Blocks::STONE_SLAB;
    DIGGABLES[24] = Blocks::STONE_BUTTON;
    DIGGABLES[25] = Blocks::STONE_PRESSURE_PLATE;
}
