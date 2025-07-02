#pragma once

#include "net/minecraft/world/item/enchantment/EnchantmentCategory.h"

class ArmorCategory : public EnchantmentCategory {
public:
    static const ArmorCategory* sArmorCategory;

    bool canEnchant(Item* item) const;
};