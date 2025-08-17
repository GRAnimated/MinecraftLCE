#include "net/minecraft/world/enchantment/enchantments/FireAspectEnchantment.h"

#include "net/minecraft/client/ui/StringIDs.h"
#include "net/minecraft/world/enchantment/categories/WeaponCategory.h"

FireAspectEnchantment::FireAspectEnchantment(const Rarity* rarity,
                                             arrayWithLength<const EquipmentSlot*> equipmentSlots)
    : Enchantment(rarity, WeaponCategory::sWeaponCategory, equipmentSlots) {
    this->setDescriptionId(StringIDs::FireAspect);
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
