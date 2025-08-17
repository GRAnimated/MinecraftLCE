#include "net/minecraft/world/enchantment/enchantments/OxygenEnchantment.h"

#include "net/minecraft/world/enchantment/categories/HeadArmorCategory.h"
#include "net/minecraft/world/item/enchantment/Enchantment.h"

OxygenEnchantment::OxygenEnchantment(const Rarity* rarity,
                                     arrayWithLength<const EquipmentSlot*> equipmentSlots)
    : Enchantment(rarity, HeadArmorCategory::sHeadArmorCategory, equipmentSlots) {
    this->setDescriptionId(0x3349D040);
}

int OxygenEnchantment::getMaxLevel() {
    return 3;
}

int OxygenEnchantment::getMinCost(int a2) {
    return a2 * 10;
}

int OxygenEnchantment::getMaxCost(int a2) {
    return this->getMinCost(a2) + 30;
}
