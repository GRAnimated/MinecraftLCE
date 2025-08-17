#include "net/minecraft/world/enchantment/enchantments/VanishingCurseEnchantment.h"

#include "net/minecraft/client/ui/StringIDs.h"
#include "net/minecraft/world/enchantment/categories/AllCategory.h"

VanishingCurseEnchantment::VanishingCurseEnchantment(const Rarity* rarity,
                                                     arrayWithLength<const EquipmentSlot*> equipmentSlots)
    : Enchantment(rarity, AllCategory::sAllCategory, equipmentSlots) {
    this->setDescriptionId(StringIDs::CurseOfVanishing);
}

int VanishingCurseEnchantment::getMaxLevel() {
    return 1;
}

int VanishingCurseEnchantment::getMinCost(int a2) {
    return 25;
}

int VanishingCurseEnchantment::getMaxCost(int a2) {
    return 50;
}

bool VanishingCurseEnchantment::isTreasureOnly() {
    return true;
}

bool VanishingCurseEnchantment::isCurse() {
    return true;
}
