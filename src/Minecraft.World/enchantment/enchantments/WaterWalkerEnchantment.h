#include "Minecraft.World/enchantment/Enchantment.h"
class WaterWalkerEnchantment : public Enchantment {
public:
    WaterWalkerEnchantment(const Rarity*, arrayWithLength<const EquipmentSlot*>);

    int getMaxLevel() override;
    int getMinCost(int) override;
    int getMaxCost(int) override;
    bool checkCompatibility(Enchantment const*) override;
};