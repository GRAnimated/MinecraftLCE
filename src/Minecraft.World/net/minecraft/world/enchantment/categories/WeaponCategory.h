#pragma once

#include "net/minecraft/world/item/enchantment/EnchantmentCategory.h"

class WeaponCategory : public EnchantmentCategory {
public:
    static const WeaponCategory* sWeaponCategory;
    bool canEnchant(Item* item) const;
};
