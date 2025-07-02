#pragma once

#include "net/minecraft/world/item/enchantment/EnchantmentCategory.h"

class DiggerCategory : public EnchantmentCategory {
public:
    static const DiggerCategory* sDiggerCategory;

    bool canEnchant(Item* item) const;
};