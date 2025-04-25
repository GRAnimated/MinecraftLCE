#include "Minecraft.World/enchantment/Enchantment.h"
class ArrowDamageEnchantment : public Enchantment {
public:
    ArrowDamageEnchantment(const Rarity*, arrayWithLength<const EquipmentSlot*>);

    int getMaxLevel() override;
    int getMinCost(int) override;
    int getMaxCost(int) override;
};