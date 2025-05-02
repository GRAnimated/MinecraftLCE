#include "Minecraft.World/item/DyeColor.h"
#include "Minecraft.World/item/Item.h"
#include "Minecraft.World/item/ItemInstance.h"
#include "Minecraft.World/item/Items.h"
#include "Minecraft.World/level/Level.h"
#include "Minecraft.World/level/block/Block.h"
#include "Minecraft.World/level/block/Blocks.h"
#include "Minecraft.World/level/block/OreBlock.h"
#include "Minecraft.World/level/block/state/BlockStateDefinition.h"
#include "Minecraft.World/level/material/Material.h"
#include "Minecraft.Util/Mth.h"

OreBlock::OreBlock() : Block(Material::STONE) {
    this->DerivedInit();
}
OreBlock::OreBlock(const MaterialColor* color) : Block(Material::STONE, color) {
    this->DerivedInit();
}

OreBlock::~OreBlock() {}

int OreBlock::getResourceCount(Random* random) {
    return this == Blocks::LAPIS_ORE ? random->nextInt(5) + 4 : 1;
}

Item* OreBlock::getResource(const BlockState* blockState, Random*, int) {
    if (this == Blocks::COAL_ORE)
        return Items::COAL;
    if (this == Blocks::DIAMOND_ORE)
        return Items::DIAMOND;
    if (this == Blocks::LAPIS_ORE)
        return Items::DYE;
    if (this == Blocks::EMERALD_ORE)
        return Items::EMERALD;
    if (this == Blocks::QUARTZ_ORE)
        return Items::QUARTZ;
    return Item::byBlock(this);
}
void OreBlock::spawnResources(Level* level, const BlockPos& pos, const BlockState* blockState, float chance,
                              int fortuneLevel) {
    Block::spawnResources(level, pos, blockState, chance, fortuneLevel);
    if (this->getResource(blockState, level->mRandom, fortuneLevel) != Item::byBlock(this)) {
        int v13 = 0;
        if (this == Blocks::COAL_ORE) {
            v13 = Mth::nextInt(level->mRandom, 0, 2);
        } else if (this == Blocks::DIAMOND_ORE) {
            v13 = Mth::nextInt(level->mRandom, 3, 7);
        } else if (this == Blocks::EMERALD_ORE) {
            v13 = Mth::nextInt(level->mRandom, 3, 7);
        } else if (this == Blocks::LAPIS_ORE) {
            v13 = Mth::nextInt(level->mRandom, 2, 5);
        } else if (this == Blocks::QUARTZ_ORE) {
            v13 = Mth::nextInt(level->mRandom, 2, 5);
        }

        this->popExperience(level, pos, v13);
    }
}

// NON_MATCHING: figure out what BlockStateDefintion::getPossibleBlockStates() returns
int OreBlock::getResourceCountForLootBonus(int fortuneLevel, Random* random) {
    if (fortuneLevel > 0
        && Item::byBlock(this)
               != this->getResource(this->getBlockStateDefinition()->getPossibleBlockStates(), random,
                                    fortuneLevel)) {
        int i = random->nextInt(fortuneLevel + 2) - 1;
        if (i < 0) {
            i = 0;
        }

        return this->getResourceCount(random) * (i + 1);
    } else {
        return this->getResourceCount(random);
    }
}
not_null_ptr<ItemInstance> OreBlock::getCloneItemInstance(Level* level, const BlockPos& pos,
                                                          const BlockState* blockState) {
    return new ItemInstance(this);
}
int OreBlock::getSpawnResourcesAuxValue(const BlockState* blockState) {
    return this == Blocks::LAPIS_ORE ? DyeColor::BLUE->getItemData() : 0;
}