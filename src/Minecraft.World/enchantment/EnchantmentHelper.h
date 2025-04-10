#pragma once

#include "types.h"

class ItemInstance;
class Enchantment;

class EnchantmentHelper{
public:
    static int getItemEnchantmentLevel(const Enchantment*, not_null_ptr<ItemInstance> const&);
};