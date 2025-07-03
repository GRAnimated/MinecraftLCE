#pragma once

#include "net/minecraft/world/item/enchantment/Enchantment.h"
class ArrowInfiniteEnchantment : public Enchantment {
public:
    ArrowInfiniteEnchantment(const Rarity*, arrayWithLength<const EquipmentSlot*>);

    int getMaxLevel() override;
    int getMinCost(int) override;
    int getMaxCost(int) override;
    bool checkCompatibility(const Enchantment*) override;
};
