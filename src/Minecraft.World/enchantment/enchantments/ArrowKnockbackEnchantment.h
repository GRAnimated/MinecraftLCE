#include "Minecraft.World/enchantment/Enchantment.h"
class ArrowKnockbackEnchantment : public Enchantment {
public:
    ArrowKnockbackEnchantment(const Rarity*, arrayWithLength<const EquipmentSlot*>);

    int getMaxLevel() override;
    int getMinCost(int) override;
    int getMaxCost(int) override;
};