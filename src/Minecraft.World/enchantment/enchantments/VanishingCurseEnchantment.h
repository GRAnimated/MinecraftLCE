#pragma once

#include "Minecraft.World/enchantment/Enchantment.h"
class VanishingCurseEnchantment : public Enchantment {
public:
    VanishingCurseEnchantment(const Rarity*, arrayWithLength<const EquipmentSlot*>);

    int getMaxLevel() override;
    int getMinCost(int) override;
    int getMaxCost(int) override;
    bool isTreasureOnly() override;
    bool isCurse() override;
};