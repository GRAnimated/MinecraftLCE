#include "net/minecraft/world/enchantment/enchantments/LootBonusEnchantment.h"

#include "net/minecraft/client/ui/StringIDs.h"
#include "net/minecraft/world/enchantment/categories/DiggerCategory.h"
#include "net/minecraft/world/enchantment/categories/FishingRodCategory.h"
#include "net/minecraft/world/enchantment/categories/WeaponCategory.h"
#include "net/minecraft/world/item/enchantment/Enchantment.h"
#include "net/minecraft/world/item/enchantment/EnchantmentCategory.h"

LootBonusEnchantment::LootBonusEnchantment(const Rarity* rarity, const EnchantmentCategory* category,
                                           arrayWithLength<const EquipmentSlot*> equipmentSlots)
    : Enchantment(rarity, category, equipmentSlots) {
    if (category == DiggerCategory::sDiggerCategory)
        Enchantment::setDescriptionId(StringIDs::Fortune);
    else if (category == FishingRodCategory::sFishingRodCategory)
        Enchantment::setDescriptionId(StringIDs::LuckOfSea);
    else
        Enchantment::setDescriptionId(StringIDs::Looting);
}

int LootBonusEnchantment::getMaxLevel() {
    return 3;
}

int LootBonusEnchantment::getMinCost(int a2) {
    return 9 * a2 + 6;
}

int LootBonusEnchantment::getMaxCost(int a2) {
    return Enchantment::getMinCost(a2) + 50;
}
