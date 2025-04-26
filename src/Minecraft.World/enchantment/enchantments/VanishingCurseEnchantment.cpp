#include "Minecraft.World/enchantment/categories/AllCategory.h"
#include "Minecraft.World/enchantment/enchantments/VanishingCurseEnchantment.h"

VanishingCurseEnchantment::VanishingCurseEnchantment(const Rarity* rarity,
                                                     arrayWithLength<const EquipmentSlot*> equipmentSlots)
    : Enchantment(rarity, AllCategory::sAllCategory, equipmentSlots) {
    this->setDescriptionId(0xC8D93E3A);
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