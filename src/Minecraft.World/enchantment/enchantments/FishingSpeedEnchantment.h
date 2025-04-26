#include "Minecraft.World/enchantment/Enchantment.h"
class FishingSpeedEnchantment : public Enchantment {
public:
    FishingSpeedEnchantment(const Rarity*, const EnchantmentCategory*, arrayWithLength<const EquipmentSlot*>);

    int getMaxLevel() override;
    int getMinCost(int) override;
    int getMaxCost(int) override;
};