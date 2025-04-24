#include "Minecraft.World/enchantment/Enchantment.h"
class UntouchingEnchantment : public Enchantment {
public:
    UntouchingEnchantment(const Rarity*, arrayWithLength<const EquipmentSlot*>);

    int getMaxLevel() override;
    int getMinCost(int) override;
    int getMaxCost(int) override;
    bool checkCompatibility(Enchantment const*) override;
};