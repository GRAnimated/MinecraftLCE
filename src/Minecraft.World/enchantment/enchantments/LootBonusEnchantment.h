#include "Minecraft.World/enchantment/Enchantment.h"

class LootBonusEnchantment : public Enchantment {
public:
    LootBonusEnchantment(const Rarity*, const EnchantmentCategory*, arrayWithLength<const EquipmentSlot*>);

    int getMaxLevel() override;
    int getMinCost(int) override;
    int getMaxCost(int) override;
    bool checkCompatibility(Enchantment const*) override;
};