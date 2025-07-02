#include "net/minecraft/world/enchantment/categories/HeadArmorCategory.h"
#include "net/minecraft/world/entity/EquipmentSlot.h"
#include "net/minecraft/world/item/ArmorItem.h"

const HeadArmorCategory* HeadArmorCategory::sHeadArmorCategory = new HeadArmorCategory();

bool HeadArmorCategory::canEnchant(Item* item) const {
    ArmorItem* armorItem = dynamic_cast<ArmorItem*>(item);
    return armorItem && armorItem->mEquipmentSlot == EquipmentSlot::HEAD;
}