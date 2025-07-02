#include "Minecraft.World/enchantment/categories/BowCategory.h"
#include "Minecraft.World/enchantment/enchantments/ArrowKnockbackEnchantment.h"

ArrowKnockbackEnchantment::ArrowKnockbackEnchantment(const Rarity* rarity,
                                                     arrayWithLength<const EquipmentSlot*> equipmentSlots)
    : Enchantment(rarity, BowCategory::sBowCategory, equipmentSlots) {
    this->setDescriptionId(0x86D14A8D);
}

int ArrowKnockbackEnchantment::getMaxLevel() {
    return 2;
}

int ArrowKnockbackEnchantment::getMinCost(int a2) {
    return 20 * a2 - 8;
}

int ArrowKnockbackEnchantment::getMaxCost(int a2) {
    return this->getMinCost(a2) + 25;
}