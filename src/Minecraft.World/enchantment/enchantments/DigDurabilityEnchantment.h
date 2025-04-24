#include "Minecraft.World/enchantment/Enchantment.h"
class DigDurabilityEnchantment : public Enchantment {
public:
    DigDurabilityEnchantment(const Rarity*, arrayWithLength<const EquipmentSlot*>);

    int getMaxLevel() override;
    int getMinCost(int) override;
    int getMaxCost(int) override;
    bool canEnchant(const not_null_ptr<ItemInstance>&) override;
};