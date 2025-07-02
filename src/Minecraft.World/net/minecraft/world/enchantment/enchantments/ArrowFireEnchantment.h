#pragma once

#include "net/minecraft/world/item/enchantment/Enchantment.h"
class ArrowFireEnchantment : public Enchantment {
public:
    ArrowFireEnchantment(const Rarity*, arrayWithLength<const EquipmentSlot*>);

    int getMaxLevel() override;
    int getMinCost(int) override;
    int getMaxCost(int) override;
};