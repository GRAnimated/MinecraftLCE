#include "Minecraft.World/enchantment/Enchantment.h"
#include "Minecraft.World/enchantment/categories/BowCategory.h"
#include "Minecraft.World/enchantment/enchantments/ArrowFireEnchantment.h"

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