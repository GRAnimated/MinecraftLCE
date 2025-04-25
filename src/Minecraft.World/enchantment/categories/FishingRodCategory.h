#include "Minecraft.World/enchantment/EnchantmentCategory.h"

class FishingRodCategory : public EnchantmentCategory {
public:
    static const FishingRodCategory* sFishingRodCategory;

    bool canEnchant(Item* item) const;
};