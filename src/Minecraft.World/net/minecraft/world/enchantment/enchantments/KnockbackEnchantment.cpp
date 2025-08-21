#include "net/minecraft/world/enchantment/enchantments/KnockbackEnchantment.h"

#include "net/minecraft/client/ui/StringIDs.h"
#include "net/minecraft/world/enchantment/categories/WeaponCategory.h"

KnockbackEnchantment::KnockbackEnchantment(const Rarity* rarity,
                                           arrayWithLength<const EquipmentSlot*> equipmentSlots)
    : Enchantment(rarity, WeaponCategory::sWeaponCategory, equipmentSlots) {
    this->setDescriptionId(StringIDs::Knockback);
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
