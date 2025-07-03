#pragma once

#include "net/minecraft/world/item/enchantment/EnchantmentCategory.h"

class WearableCategory : public EnchantmentCategory {
public:
    static const WearableCategory* sWearableCategory;
    bool canEnchant(Item* item) const;
};
