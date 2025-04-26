#include "Minecraft.World/enchantment/categories/BreakableCategory.h"
#include "Minecraft.World/enchantment/enchantments/MendingEnchantment.h"

MendingEnchantment::MendingEnchantment(const Rarity* rarity,
                                       arrayWithLength<const EquipmentSlot*> equipmentSlots)
    : Enchantment(rarity, BreakableCategory::sBreakableCategory, equipmentSlots) {
    this->setDescriptionId(0x3BCC2150);
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