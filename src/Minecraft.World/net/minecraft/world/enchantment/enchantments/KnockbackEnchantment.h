#pragma once

#include "net/minecraft/world/item/enchantment/Enchantment.h"

class KnockbackEnchantment : public Enchantment {
public:
    KnockbackEnchantment(const Rarity*, arrayWithLength<const EquipmentSlot*>);

    int getMaxLevel() override;
    int getMinCost(int) override;
    int getMaxCost(int) override;
};
