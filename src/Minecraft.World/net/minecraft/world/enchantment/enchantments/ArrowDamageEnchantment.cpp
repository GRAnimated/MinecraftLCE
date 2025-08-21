#include "net/minecraft/world/enchantment/enchantments/ArrowDamageEnchantment.h"

#include "net/minecraft/client/ui/StringIDs.h"
#include "net/minecraft/world/enchantment/categories/BowCategory.h"
#include "net/minecraft/world/item/enchantment/Enchantment.h"

ArrowDamageEnchantment::ArrowDamageEnchantment(const Rarity* rarity,
                                               arrayWithLength<const EquipmentSlot*> equipmentSlots)
    : Enchantment(rarity, BowCategory::sBowCategory, equipmentSlots) {
    Enchantment::setDescriptionId(StringIDs::Power);
}

int ArrowDamageEnchantment::getMaxLevel() {
    return 5;
}

int ArrowDamageEnchantment::getMinCost(int a2) {
    return 10 * a2 - 9;
}

int ArrowDamageEnchantment::getMaxCost(int a2) {
    return this->getMinCost(a2) + 15;
}
