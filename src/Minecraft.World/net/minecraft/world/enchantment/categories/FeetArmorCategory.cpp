#include "net/minecraft/world/enchantment/categories/FeetArmorCategory.h"
#include "net/minecraft/world/entity/EquipmentSlot.h"
#include "net/minecraft/world/item/ArmorItem.h"

const FeetArmorCategory* FeetArmorCategory::sFeetArmorCategory = new FeetArmorCategory();

bool FeetArmorCategory::canEnchant(Item* item) const {
    ArmorItem* armorItem = dynamic_cast<ArmorItem*>(item);
    return armorItem && armorItem->m_equipmentSlot == EquipmentSlot::FEET;
}
