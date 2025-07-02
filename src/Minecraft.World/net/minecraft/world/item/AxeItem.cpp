#include "Minecraft.World/ArrayWithLength.h"
#include "Minecraft.World/item/AxeItem.h"
#include "Minecraft.World/item/DiggerItem.h"
#include "Minecraft.World/level/block/Blocks.h"
#include "Minecraft.World/level/material/Material.h"

arrayWithLength<Block*> AxeItem::DIGGABLES = arrayWithLength<Block*>(11, true);

void AxeItem::staticCtor() {
    DIGGABLES[0] = Blocks::PLANKS;
    DIGGABLES[1] = Blocks::BOOKSHELF;
    DIGGABLES[2] = Blocks::LOG;
    DIGGABLES[3] = Blocks::LOG2;
    DIGGABLES[4] = Blocks::CHEST;
    DIGGABLES[5] = Blocks::PUMPKIN;
    DIGGABLES[6] = Blocks::LIT_PUMPKIN;
    DIGGABLES[7] = Blocks::MELON_BLOCK;
    DIGGABLES[8] = Blocks::LADDER;
    DIGGABLES[9] = Blocks::WOODEN_BUTTON;
    DIGGABLES[10] = Blocks::WOODEN_PRESSURE_PLATE;
}

AxeItem::AxeItem(const Item::Tier* tier) : DiggerItem(tier, DIGGABLES) {
    this->mAttackDamage = tier->getAttackDamageBonus() + 3.0f;
}

AxeItem::~AxeItem() {}

float AxeItem::getDestroySpeed(not_null_ptr<ItemInstance> instance, BlockState* state) {
    Material* material = state->getMaterial();
    return material != Material::WOOD && material != Material::PLANTS && material != Material::MOSS ?
               DiggerItem::getDestroySpeed(instance, state) :
               this->mSpeed;
}