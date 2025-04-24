#include "Minecraft.World/enchantment/Enchantment.h"

class BindingCurseEnchantment : public Enchantment {
public:
    BindingCurseEnchantment(const Rarity*, arrayWithLength<const EquipmentSlot*>);

    int getMaxLevel() override;
    int getMinCost(int) override;
    int getMaxCost(int) override;
    bool isTreasureOnly() override;
    bool isCurse() override;
};