#include "Minecraft.World/enchantment/Enchantment.h"
class DiggingEnchantment : public Enchantment {
public:
    DiggingEnchantment(const Rarity*, arrayWithLength<const EquipmentSlot*>);

    int getMaxLevel() override;
    int getMinCost(int) override;
    int getMaxCost(int) override;
    bool canEnchant(const not_null_ptr<ItemInstance>&) override;
};