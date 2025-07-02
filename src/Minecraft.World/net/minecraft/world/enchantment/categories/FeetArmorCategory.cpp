#include "Minecraft.World/enchantment/categories/FeetArmorCategory.h"
#include "Minecraft.World/inventory/EquipmentSlot.h"
#include "Minecraft.World/item/ArmorItem.h"

const FeetArmorCategory* FeetArmorCategory::sFeetArmorCategory = new FeetArmorCategory();

bool FeetArmorCategory::canEnchant(Item* item) const {
    ArmorItem* armorItem = dynamic_cast<ArmorItem*>(item);
    return armorItem && armorItem->mEquipmentSlot == EquipmentSlot::FEET;
}