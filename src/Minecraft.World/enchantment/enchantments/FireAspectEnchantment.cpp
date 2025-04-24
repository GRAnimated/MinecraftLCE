#include "Minecraft.World/enchantment/categories/WeaponCategory.h"
#include "Minecraft.World/enchantment/enchantments/FireAspectEnchantment.h"

FireAspectEnchantment::FireAspectEnchantment(const Rarity* rarity,
                                             arrayWithLength<const EquipmentSlot*> equipmentSlots)
    : Enchantment(rarity, WeaponCategory::sWeaponCategory, equipmentSlots) {
    this->setDescriptionId(0x96021422);
}

int FireAspectEnchantment::getMaxLevel() {
    return 2;
}

int FireAspectEnchantment::getMinCost(int a2) {
    return 20 * a2 - 10;
}

int FireAspectEnchantment::getMaxCost(int a2) {
    return Enchantment::getMinCost(a2) + 50;
}