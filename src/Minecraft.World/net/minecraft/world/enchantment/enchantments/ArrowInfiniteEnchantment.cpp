#include "net/minecraft/world/enchantment/enchantments/ArrowInfiniteEnchantment.h"

#include "net/minecraft/client/ui/StringIDs.h"
#include "net/minecraft/world/enchantment/categories/BowCategory.h"
#include "net/minecraft/world/enchantment/enchantments/MendingEnchantment.h"
#include "net/minecraft/world/item/enchantment/Enchantment.h"

ArrowInfiniteEnchantment::ArrowInfiniteEnchantment(const Rarity* rarity,
                                                   arrayWithLength<const EquipmentSlot*> equipmentSlots)
    : Enchantment(rarity, BowCategory::sBowCategory, equipmentSlots) {
    Enchantment::setDescriptionId(StringIDs::Infinity);
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

bool ArrowInfiniteEnchantment::checkCompatibility(const Enchantment* other) {
    return !dynamic_cast<const MendingEnchantment*>(other) && Enchantment::checkCompatibility(other);
}
