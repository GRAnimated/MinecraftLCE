#include "Minecraft.World/enchantment/Enchantment.h"
#include "Minecraft.World/enchantment/categories/HeadArmorCategory.h"
#include "Minecraft.World/enchantment/enchantments/OxygenEnchantment.h"

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