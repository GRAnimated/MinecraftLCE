#include "net/minecraft/world/enchantment/categories/ChestArmorCategory.h"
#include "net/minecraft/world/entity/EquipmentSlot.h"
#include "net/minecraft/world/item/ArmorItem.h"

const ChestArmorCategory* ChestArmorCategory::sChestArmorCategory = new ChestArmorCategory();

bool ChestArmorCategory::canEnchant(Item* item) const {
    ArmorItem* armorItem = dynamic_cast<ArmorItem*>(item);
    return armorItem && armorItem->m_equipmentSlot == EquipmentSlot::CHEST;
}
