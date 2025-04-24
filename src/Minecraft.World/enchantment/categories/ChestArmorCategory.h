#include "Minecraft.World/enchantment/EnchantmentCategory.h"

class ChestArmorCategory : public EnchantmentCategory {
public:
    static const ChestArmorCategory* sChestArmorCategory;

    bool canEnchant(Item* item) const;
};