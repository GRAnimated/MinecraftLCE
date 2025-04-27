#include "Minecraft.World/enchantment/Enchantment.h"
#include "Minecraft.World/enchantment/categories/BowCategory.h"
#include "Minecraft.World/enchantment/enchantments/ArrowInfiniteEnchantment.h"
#include "Minecraft.World/enchantment/enchantments/MendingEnchantment.h"

ArrowInfiniteEnchantment::ArrowInfiniteEnchantment(const Rarity* rarity,
                                                   arrayWithLength<const EquipmentSlot*> equipmentSlots)
    : Enchantment(rarity, BowCategory::sBowCategory, equipmentSlots) {
    Enchantment::setDescriptionId(0xD251EC6A);
}

int ArrowInfiniteEnchantment::getMaxLevel() {
    return 1;
}

int ArrowInfiniteEnchantment::getMinCost(int a2) {
    return 20;
}

int ArrowInfiniteEnchantment::getMaxCost(int a2) {
    return 50;
}

bool ArrowInfiniteEnchantment::checkCompatibility(Enchantment const* other) {
    return !dynamic_cast<const MendingEnchantment*>(other) && Enchantment::checkCompatibility(other);
}