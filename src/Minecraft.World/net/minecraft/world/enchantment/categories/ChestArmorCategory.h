#pragma once

#include "net/minecraft/world/item/enchantment/EnchantmentCategory.h"

class ChestArmorCategory : public EnchantmentCategory {
public:
    static const ChestArmorCategory* sChestArmorCategory;

    bool canEnchant(Item* item) const;
};
