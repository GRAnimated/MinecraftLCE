#include "Minecraft.World/enchantment/Enchantment.h"
#include "Minecraft.World/enchantment/EnchantmentCategory.h"
#include "Minecraft.World/enchantment/enchantments/FishingSpeedEnchantment.h"

FishingSpeedEnchantment::FishingSpeedEnchantment(const Rarity* rarity, const EnchantmentCategory* category,
                                                 arrayWithLength<const EquipmentSlot*> equipmentSlots)
    : Enchantment(rarity, category, equipmentSlots) {
    Enchantment::setDescriptionId(0xFC584B8E);
}

int FishingSpeedEnchantment::getMaxLevel() {
    return 3;
}

int FishingSpeedEnchantment::getMinCost(int a2) {
    return 9 * a2 + 6;
}

int FishingSpeedEnchantment::getMaxCost(int a2) {
    return Enchantment::getMinCost(a2) + 50;
}