#pragma once

#include "Minecraft.World/enchantment/Enchantment.h"
class ArrowInfiniteEnchantment : public Enchantment {
public:
    ArrowInfiniteEnchantment(const Rarity*, arrayWithLength<const EquipmentSlot*>);

    int getMaxLevel() override;
    int getMinCost(int) override;
    int getMaxCost(int) override;
    bool checkCompatibility(Enchantment const*) override;
};