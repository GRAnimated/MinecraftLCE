#include "Minecraft.World/enchantment/Enchantment.h"
#include "Minecraft.World/enchantment/EnchantmentCategory.h"
#include "Minecraft.World/enchantment/enchantments/LootBonusEnchantment.h"

#include "Minecraft.World/enchantment/categories/DiggerCategory.h"
#include "Minecraft.World/enchantment/categories/FishingRodCategory.h"
#include "Minecraft.World/enchantment/categories/WeaponCategory.h"

LootBonusEnchantment::LootBonusEnchantment(const Rarity* rarity, const EnchantmentCategory* category,
                                           arrayWithLength<const EquipmentSlot*> equipmentSlots)
    : Enchantment(rarity, category, equipmentSlots) {
    if (category == DiggerCategory::sDiggerCategory)
        Enchantment::setDescriptionId(0xDA6036A5);
    else if (category == FishingRodCategory::sFishingRodCategory)
        Enchantment::setDescriptionId(0x8E00390D);
    else
        Enchantment::setDescriptionId(0x797D9C28);
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