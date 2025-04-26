#include "Minecraft.World/enchantment/Enchantment.h"

class MendingEnchantment : public Enchantment {
public:
    MendingEnchantment(const Rarity*, arrayWithLength<const EquipmentSlot*>);

    int getMaxLevel() override;
    int getMinCost(int) override;
    int getMaxCost(int) override;
    bool isTreasureOnly() override;
};