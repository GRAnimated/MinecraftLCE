#pragma once

#include "net/minecraft/world/item/enchantment/EnchantmentCategory.h"

class FishingRodCategory : public EnchantmentCategory {
public:
    static const FishingRodCategory* sFishingRodCategory;

    bool canEnchant(Item* item) const;
};
