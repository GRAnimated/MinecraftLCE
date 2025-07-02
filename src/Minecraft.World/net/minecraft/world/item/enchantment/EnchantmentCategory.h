#pragma once

class Item;

class EnchantmentCategory {
public:
    EnchantmentCategory();

    virtual bool canEnchant(Item* item) const = 0;
};