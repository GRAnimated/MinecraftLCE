#include "net/minecraft/world/enchantment/enchantments/ArrowFireEnchantment.h"

#include "net/minecraft/world/enchantment/categories/BowCategory.h"
#include "net/minecraft/world/item/enchantment/Enchantment.h"

ArrowFireEnchantment::ArrowFireEnchantment(const Rarity* rarity,
                                           arrayWithLength<const EquipmentSlot*> equipmentSlots)
    : Enchantment(rarity, BowCategory::sBowCategory, equipmentSlots) {
    Enchantment::setDescriptionId(0xEA75E04);
}

int ArrowFireEnchantment::getMaxLevel() {
    return 1;
}

int ArrowFireEnchantment::getMinCost(int a2) {
    return 20;
}

int ArrowFireEnchantment::getMaxCost(int a2) {
    return 50;
}
