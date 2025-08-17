#include "net/minecraft/world/enchantment/enchantments/MendingEnchantment.h"

#include "net/minecraft/client/ui/StringIDs.h"
#include "net/minecraft/world/enchantment/categories/BreakableCategory.h"

MendingEnchantment::MendingEnchantment(const Rarity* rarity,
                                       arrayWithLength<const EquipmentSlot*> equipmentSlots)
    : Enchantment(rarity, BreakableCategory::sBreakableCategory, equipmentSlots) {
    this->setDescriptionId(StringIDs::Mending);
}

int MendingEnchantment::getMaxLevel() {
    return 1;
}

int MendingEnchantment::getMinCost(int a2) {
    return 25 * a2;
}

int MendingEnchantment::getMaxCost(int a2) {
    return this->getMinCost(a2) + 50;
}

bool MendingEnchantment::isTreasureOnly() {
    return true;
}
