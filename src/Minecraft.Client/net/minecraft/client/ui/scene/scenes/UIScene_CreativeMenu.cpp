#include "net/minecraft/client/ui/scene/scenes/UIScene_CreativeMenu.h"

#include "net/minecraft/client/gui/MenuBuilder.h"

#include "net/minecraft/world/item/Items.h"
#include "net/minecraft/world/level/block/Blocks.h"

#include "net/minecraft/world/level/block/PlanksBlock.h"
#include "net/minecraft/world/level/block/QuartzBlock.h"
#include "net/minecraft/world/level/block/RedSandStoneBlock.h"
#include "net/minecraft/world/level/block/SandBlock.h"
#include "net/minecraft/world/level/block/SandStoneBlock.h"
#include "net/minecraft/world/level/block/StoneBlock.h"

void UIScene_CreativeMenu::staticCtor() {
    nullsub_728();
    MenuBuilder builder;

    // Category: Structures

    builder.setCategory(Structures);
    builder.ITEM_BLOCK(Blocks::STONE);
    builder.ITEM_BLOCK(Blocks::GRASS);
    builder.ITEM_BLOCK(Blocks::GRASS_PATH);
    builder.ITEM_BLOCK(Blocks::DIRT);
    builder.ITEM_BLOCK(Blocks::COBBLESTONE);
    builder.ITEM_BLOCK(Blocks::SAND);
    builder.ITEM_BLOCK(Blocks::SANDSTONE);
    builder.ITEM_AUX(Blocks::SANDSTONE, SandStoneBlock::TYPE, SandStoneBlock::Variant::SMOOTH);
    builder.ITEM_AUX(Blocks::SANDSTONE, SandStoneBlock::TYPE, SandStoneBlock::Variant::CHISELED);
    builder.ITEM_AUX(Blocks::SAND, SandBlock::VARIANT, SandBlock::Variant::RED);
    builder.ITEM_BLOCK(Blocks::RED_SANDSTONE);
    builder.ITEM_AUX(Blocks::RED_SANDSTONE, RedSandStoneBlock::TYPE, RedSandStoneBlock::Variant::SMOOTH);
    builder.ITEM_AUX(Blocks::RED_SANDSTONE, RedSandStoneBlock::TYPE, RedSandStoneBlock::Variant::CHISELED);
    builder.ITEM_AUX(Blocks::STONE, StoneBlock::VARIANT, StoneBlock::Variant::GRANITE);
    builder.ITEM_AUX(Blocks::STONE, StoneBlock::VARIANT, StoneBlock::Variant::SMOOTH_GRANITE);
    builder.ITEM_AUX(Blocks::STONE, StoneBlock::VARIANT, StoneBlock::Variant::ANDESITE);
    builder.ITEM_AUX(Blocks::STONE, StoneBlock::VARIANT, StoneBlock::Variant::SMOOTH_ANDESITE);
    builder.ITEM_AUX(Blocks::STONE, StoneBlock::VARIANT, StoneBlock::Variant::DIORITE);
    builder.ITEM_AUX(Blocks::STONE, StoneBlock::VARIANT, StoneBlock::Variant::SMOOTH_DIORITE);
    builder.ITEM_BLOCK(Blocks::COAL_BLOCK);
    builder.ITEM_BLOCK(Blocks::GOLD_BLOCK);
    builder.ITEM_BLOCK(Blocks::IRON_BLOCK);
    builder.ITEM_BLOCK(Blocks::LAPIS_BLOCK);
    builder.ITEM_BLOCK(Blocks::DIAMOND_BLOCK);
    builder.ITEM_BLOCK(Blocks::EMERALD_BLOCK);
    builder.ITEM_AUX(Blocks::QUARTZ_BLOCK, QuartzBlock::VARIANT, QuartzBlock::Variant::DEFAULT);
    builder.ITEM_BLOCK(Blocks::COAL_ORE);
    builder.ITEM_BLOCK(Blocks::LAPIS_ORE);
    builder.ITEM_BLOCK(Blocks::DIAMOND_ORE);
    builder.ITEM_BLOCK(Blocks::REDSTONE_ORE);
    builder.ITEM_BLOCK(Blocks::IRON_ORE);
    builder.ITEM_BLOCK(Blocks::GOLD_ORE);
    builder.ITEM_BLOCK(Blocks::EMERALD_ORE);
    builder.ITEM_BLOCK(Blocks::QUARTZ_ORE);
    builder.ITEM_BLOCK(Blocks::NETHER_WART_BLOCK);
    builder.ITEM_BLOCK(Blocks::BEDROCK);
    builder.ITEM_AUX(Blocks::PLANKS, PlanksBlock::VARIANT, PlanksBlock::Variant::OAK);
    builder.ITEM_AUX(Blocks::PLANKS, PlanksBlock::VARIANT, PlanksBlock::Variant::SPRUCE);
    builder.ITEM_AUX(Blocks::PLANKS, PlanksBlock::VARIANT, PlanksBlock::Variant::BIRCH);
    builder.ITEM_AUX(Blocks::PLANKS, PlanksBlock::VARIANT, PlanksBlock::Variant::JUNGLE);
    builder.ITEM_AUX(Blocks::PLANKS, PlanksBlock::VARIANT, PlanksBlock::Variant::ACACIA);
    builder.ITEM_AUX(Blocks::PLANKS, PlanksBlock::VARIANT, PlanksBlock::Variant::DARK_OAK);
    // builder.ITEM_AUX(Blocks::LOG, qword_710178CB88, PlanksBlock::Variant::OAK);
    // builder.ITEM_AUX(Blocks::LOG, qword_710178CB88, PlanksBlock::Variant::SPRUCE);
    // builder.ITEM_AUX(Blocks::LOG, qword_710178CB88, PlanksBlock::Variant::BIRCH);
    // builder.ITEM_AUX(Blocks::LOG, qword_710178CB88, PlanksBlock::Variant::JUNGLE);
    // builder.ITEM_AUX(Blocks::LOG2, qword_710178CFC8, PlanksBlock::Variant::ACACIA);
    // builder.ITEM_AUX(Blocks::LOG2, qword_710178CFC8, PlanksBlock::Variant::DARK_OAK);
    builder.ITEM_BLOCK(Blocks::GRAVEL);
    builder.ITEM_BLOCK(Blocks::BRICK_BLOCK);
    builder.ITEM_BLOCK(Blocks::MOSSY_COBBLESTONE);
    builder.ITEM_BLOCK(Blocks::OBSIDIAN);
    builder.ITEM_BLOCK(Blocks::CLAY);
    builder.ITEM_BLOCK(Blocks::ICE);
    builder.ITEM_BLOCK(Blocks::PACKED_ICE);
    builder.ITEM_BLOCK(Blocks::SNOW);
    builder.ITEM_BLOCK(Blocks::NETHERRACK);
    builder.ITEM_BLOCK(Blocks::SOUL_SAND);
    builder.ITEM_BLOCK(Blocks::GLOWSTONE);
    builder.ITEM_BLOCK(Blocks::MAGMA);
    builder.ITEM_BLOCK(Blocks::SEA_LANTERN);
    // sub_710057C804(&builder, Blocks::PRISMARINE, qword_71017A1E70, qword_71017A1E98);
    // sub_710057C804(&builder, Blocks::PRISMARINE, qword_71017A1E70, qword_71017A1EA8);
    // sub_710057C804(&builder, Blocks::PRISMARINE, qword_71017A1E70, qword_71017A1EA0);
    builder.ITEM_BLOCK(Blocks::SLIME);
    builder.ITEM_BLOCK(Blocks::FENCE);
    builder.ITEM_BLOCK(Blocks::SPRUCE_FENCE);
    builder.ITEM_BLOCK(Blocks::BIRCH_FENCE);
    builder.ITEM_BLOCK(Blocks::JUNGLE_FENCE);
    builder.ITEM_BLOCK(Blocks::ACACIA_FENCE);
    builder.ITEM_BLOCK(Blocks::DARK_OAK_FENCE);
    builder.ITEM_BLOCK(Blocks::NETHER_BRICK_FENCE);
    builder.ITEM_BLOCK(Blocks::IRON_BARS);
    // sub_710057C84C(&builder, Blocks::STONEBRICK, qword_71017A4B40, qword_71017A4BD0);
    // sub_710057C84C(&builder, Blocks::STONEBRICK, qword_71017A4B40, qword_71017A4BD8);
    // sub_710057C84C(&builder, Blocks::STONEBRICK, qword_71017A4B40, qword_71017A4BE0);
    // sub_710057C84C(&builder, Blocks::STONEBRICK, qword_71017A4B40, qword_71017A4BE8);
    // sub_710057C894(&builder, Blocks::MONSTER_EGG, qword_710178CE68, qword_710178CEA8);
    // sub_710057C894(&builder, Blocks::MONSTER_EGG, qword_710178CE68, qword_710178CEB0);
    // sub_710057C894(&builder, Blocks::MONSTER_EGG, qword_710178CE68, qword_710178CEB8);
    // sub_710057C894(&builder, Blocks::MONSTER_EGG, qword_710178CE68, qword_710178CEC0);
    // sub_710057C894(&builder, Blocks::MONSTER_EGG, qword_710178CE68, qword_710178CEC8);
    // sub_710057C894(&builder, Blocks::MONSTER_EGG, qword_710178CE68, qword_710178CED0);
    builder.ITEM_BLOCK(Blocks::MYCELIUM);
    // sub_710057C8DC(&builder, Blocks::DIRT, qword_71017891F0, qword_7101789208);
    // sub_710057C8DC(&builder, Blocks::DIRT, qword_71017891F0, qword_7101789210);
    builder.ITEM_BLOCK(Blocks::NETHER_BRICK);
    builder.ITEM_BLOCK(Blocks::RED_NETHER_BRICK);
    builder.ITEM_BLOCK(Blocks::END_STONE);
    builder.ITEM_BLOCK(Blocks::END_BRICKS);
    builder.ITEM_AUX(Blocks::QUARTZ_BLOCK, QuartzBlock::VARIANT, QuartzBlock::Variant::CHISELED);
    builder.ITEM_AUX(Blocks::QUARTZ_BLOCK, QuartzBlock::VARIANT, QuartzBlock::Variant::LINES_Y);
    builder.ITEM_BLOCK(Blocks::PURPUR_BLOCK);
    builder.ITEM_BLOCK(Blocks::PURPUR_PILLAR);
    builder.ITEM_BLOCK(Blocks::TRAPDOOR);
    builder.ITEM_BLOCK(Blocks::IRON_TRAPDOOR);
    builder.ITEM_BLOCK(Blocks::FENCE_GATE);
    builder.ITEM_BLOCK(Blocks::SPRUCE_FENCE_GATE);
    builder.ITEM_BLOCK(Blocks::BIRCH_FENCE_GATE);
    builder.ITEM_BLOCK(Blocks::JUNGLE_FENCE_GATE);
    builder.ITEM_BLOCK(Blocks::ACACIA_FENCE_GATE);
    builder.ITEM_BLOCK(Blocks::DARK_OAK_FENCE_GATE);
    builder.ITEM(Items::WOODEN_DOOR);
    builder.ITEM(Items::IRON_DOOR);
    builder.ITEM(Items::SPRUCE_DOOR);
    builder.ITEM(Items::BIRCH_DOOR);
    builder.ITEM(Items::JUNGLE_DOOR);
    builder.ITEM(Items::ACACIA_DOOR);
    builder.ITEM(Items::DARK_OAK_DOOR);
    // sub_710057C92C(&builder, Blocks::STONE_SLAB, qword_71017A4BF8, qword_71017A4C00);
    // sub_710057C92C(&builder, Blocks::STONE_SLAB, qword_71017A4BF8, qword_71017A4C08);
    // sub_710057C974(&builder, Blocks::STONE_SLAB2, qword_710178CFD8, qword_710178CFE0);
    // builder.ITEM_AUX(Blocks::WOODEN_SLAB, qword_71017A5CD8, qword_71017A1930);
    // builder.ITEM_AUX(Blocks::WOODEN_SLAB, qword_71017A5CD8, qword_71017A16F0);
    // builder.ITEM_AUX(Blocks::WOODEN_SLAB, qword_71017A5CD8, qword_71017A1938);
    // builder.ITEM_AUX(Blocks::WOODEN_SLAB, qword_71017A5CD8, qword_71017A1940);
    // builder.ITEM_AUX(Blocks::WOODEN_SLAB, qword_71017A5CD8, qword_71017A1948);
    // builder.ITEM_AUX(Blocks::WOODEN_SLAB, qword_71017A5CD8, qword_71017A1950);
    // sub_710057C92C(&builder, Blocks::STONE_SLAB, qword_71017A4BF8, qword_71017A4C18);
    // sub_710057C92C(&builder, Blocks::STONE_SLAB, qword_71017A4BF8, qword_71017A4C20);
    // sub_710057C92C(&builder, Blocks::STONE_SLAB, qword_71017A4BF8, qword_71017A4C28);
    // sub_710057C92C(&builder, Blocks::STONE_SLAB, qword_71017A4BF8, qword_71017A4C30);
    // sub_710057C92C(&builder, Blocks::STONE_SLAB, qword_71017A4BF8, qword_71017A4C38);
    builder.ITEM_BLOCK(Blocks::PURPUR_SLAB);
    builder.ITEM_BLOCK(Blocks::OAK_STAIRS, 2);
    builder.ITEM_BLOCK(Blocks::SPRUCE_STAIRS, 2);
    builder.ITEM_BLOCK(Blocks::BIRCH_STAIRS, 2);
    builder.ITEM_BLOCK(Blocks::JUNGLE_STAIRS, 2);
    builder.ITEM_BLOCK(Blocks::ACACIA_STAIRS, 2);
    builder.ITEM_BLOCK(Blocks::DARK_OAK_STAIRS, 2);
    builder.ITEM_BLOCK(Blocks::STONE_STAIRS, 2);
    builder.ITEM_BLOCK(Blocks::BRICK_STAIRS, 2);
    builder.ITEM_BLOCK(Blocks::STONE_BRICK_STAIRS, 2);
    builder.ITEM_BLOCK(Blocks::NETHER_BRICK_STAIRS, 2);
    builder.ITEM_BLOCK(Blocks::SANDSTONE_STAIRS, 2);
    builder.ITEM_BLOCK(Blocks::RED_SANDSTONE_STAIRS, 2);
    builder.ITEM_BLOCK(Blocks::QUARTZ_STAIRS, 2);
    builder.ITEM_BLOCK(Blocks::PURPUR_STAIRS, 2);
    builder.ITEM_BLOCK(Blocks::HARDENED_CLAY);
    builder.ITEM_BLOCK(Blocks::STAINED_HARDENED_CLAY, 15);
    builder.ITEM_BLOCK(Blocks::STAINED_HARDENED_CLAY, 11);
    builder.ITEM_BLOCK(Blocks::STAINED_HARDENED_CLAY, 3);
    builder.ITEM_BLOCK(Blocks::STAINED_HARDENED_CLAY, 9);
    builder.ITEM_BLOCK(Blocks::STAINED_HARDENED_CLAY, 13);
    builder.ITEM_BLOCK(Blocks::STAINED_HARDENED_CLAY, 5);
    builder.ITEM_BLOCK(Blocks::STAINED_HARDENED_CLAY, 6);
    builder.ITEM_BLOCK(Blocks::STAINED_HARDENED_CLAY, 2);
    builder.ITEM_BLOCK(Blocks::STAINED_HARDENED_CLAY, 10);
    builder.ITEM_BLOCK(Blocks::STAINED_HARDENED_CLAY, 14);
    builder.ITEM_BLOCK(Blocks::STAINED_HARDENED_CLAY, 12);
    builder.ITEM_BLOCK(Blocks::STAINED_HARDENED_CLAY, 1);
    builder.ITEM_BLOCK(Blocks::STAINED_HARDENED_CLAY, 4);
    builder.ITEM_BLOCK(Blocks::STAINED_HARDENED_CLAY, 0);
    builder.ITEM_BLOCK(Blocks::STAINED_HARDENED_CLAY, 8);
    builder.ITEM_BLOCK(Blocks::STAINED_HARDENED_CLAY, 7);

    // Category: Decoration

    builder.setCategory(Decoration);
}