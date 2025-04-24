#include "Minecraft.World/enchantment/categories/ChestArmorCategory.h"
#include "Minecraft.World/inventory/EquipmentSlot.h"
#include "Minecraft.World/item/ArmorItem.h"

const ChestArmorCategory* ChestArmorCategory::sChestArmorCategory = new ChestArmorCategory();

bool ChestArmorCategory::canEnchant(Item* item) const {
    ArmorItem* armorItem = dynamic_cast<ArmorItem*>(item);
    return armorItem && armorItem->mEquipmentSlot == EquipmentSlot::CHEST;
}