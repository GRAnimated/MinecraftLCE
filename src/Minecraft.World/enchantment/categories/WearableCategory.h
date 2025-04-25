#include "Minecraft.World/enchantment/EnchantmentCategory.h"

class WearableCategory : public EnchantmentCategory {
public:
    static const WearableCategory* sWearableCategory;
    bool canEnchant(Item* item) const;
};