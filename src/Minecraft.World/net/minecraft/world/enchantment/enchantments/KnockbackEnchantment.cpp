#include "Minecraft.World/enchantment/categories/WeaponCategory.h"
#include "Minecraft.World/enchantment/enchantments/KnockbackEnchantment.h"

KnockbackEnchantment::KnockbackEnchantment(const Rarity* rarity,
                                           arrayWithLength<const EquipmentSlot*> equipmentSlots)
    : Enchantment(rarity, WeaponCategory::sWeaponCategory, equipmentSlots) {
    this->setDescriptionId(0xC3755A5B);
}

int KnockbackEnchantment::getMaxLevel() {
    return 2;
}

int KnockbackEnchantment::getMinCost(int a2) {
    return 20 * a2 - 15;
}

int KnockbackEnchantment::getMaxCost(int a2) {
    return Enchantment::getMinCost(a2) + 50;
}