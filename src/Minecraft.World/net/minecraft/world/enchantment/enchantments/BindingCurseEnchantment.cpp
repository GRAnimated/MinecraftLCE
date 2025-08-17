#include "net/minecraft/world/enchantment/enchantments/BindingCurseEnchantment.h"

#include "net/minecraft/client/ui/StringIDs.h"
#include "net/minecraft/world/enchantment/categories/WearableCategory.h"
#include "net/minecraft/world/item/enchantment/Enchantment.h"

BindingCurseEnchantment::BindingCurseEnchantment(const Rarity* rarity,
                                                 arrayWithLength<const EquipmentSlot*> equipmentSlots)
    : Enchantment(rarity, WearableCategory::sWearableCategory, equipmentSlots) {
    this->setDescriptionId(StringIDs::CurseOfBinding);
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
