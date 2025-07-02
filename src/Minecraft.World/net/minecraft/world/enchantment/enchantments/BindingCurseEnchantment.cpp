#include "Minecraft.World/enchantment/Enchantment.h"
#include "Minecraft.World/enchantment/categories/WearableCategory.h"
#include "Minecraft.World/enchantment/enchantments/BindingCurseEnchantment.h"

BindingCurseEnchantment::BindingCurseEnchantment(const Rarity* rarity,
                                                 arrayWithLength<const EquipmentSlot*> equipmentSlots)
    : Enchantment(rarity, WearableCategory::sWearableCategory, equipmentSlots) {
    this->setDescriptionId(0x7B5DBCD8);
}

int BindingCurseEnchantment::getMaxLevel() {
    return 1;
}

int BindingCurseEnchantment::getMinCost(int a2) {
    return 25;
}

int BindingCurseEnchantment::getMaxCost(int a2) {
    return 50;
}

bool BindingCurseEnchantment::isTreasureOnly() {
    return true;
}

bool BindingCurseEnchantment::isCurse() {
    return true;
}