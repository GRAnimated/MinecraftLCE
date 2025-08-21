#include "net/minecraft/world/enchantment/enchantments/FishingSpeedEnchantment.h"

#include "net/minecraft/client/ui/StringIDs.h"
#include "net/minecraft/world/item/enchantment/Enchantment.h"
#include "net/minecraft/world/item/enchantment/EnchantmentCategory.h"

FishingSpeedEnchantment::FishingSpeedEnchantment(const Rarity* rarity, const EnchantmentCategory* category,
                                                 arrayWithLength<const EquipmentSlot*> equipmentSlots)
    : Enchantment(rarity, category, equipmentSlots) {
    Enchantment::setDescriptionId(StringIDs::Lure);
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
