#include "Minecraft.World/enchantment/categories/HeadArmorCategory.h"
#include "Minecraft.World/inventory/EquipmentSlot.h"
#include "Minecraft.World/item/ArmorItem.h"

const HeadArmorCategory* HeadArmorCategory::sHeadArmorCategory = new HeadArmorCategory();

bool HeadArmorCategory::canEnchant(Item* item) const {
    ArmorItem* armorItem = dynamic_cast<ArmorItem*>(item);
    return armorItem && armorItem->mEquipmentSlot == EquipmentSlot::HEAD;
}