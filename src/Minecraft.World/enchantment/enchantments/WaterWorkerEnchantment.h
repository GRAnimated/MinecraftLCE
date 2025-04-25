#include "Minecraft.World/enchantment/Enchantment.h"
class WaterWorkerEnchantment : public Enchantment {
public:
    WaterWorkerEnchantment(const Rarity*, arrayWithLength<const EquipmentSlot*>);

    int getMaxLevel() override;
    int getMinCost(int) override;
    int getMaxCost(int) override;
};