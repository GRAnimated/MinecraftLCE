#pragma once

#include "net/minecraft/world/item/enchantment/EnchantmentCategory.h"

class BreakableCategory : public EnchantmentCategory {
public:
    static const BreakableCategory* sBreakableCategory;

    bool canEnchant(Item* item) const;
};
