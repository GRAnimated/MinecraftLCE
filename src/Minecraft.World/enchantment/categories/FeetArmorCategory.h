#include "Minecraft.World/enchantment/EnchantmentCategory.h"

class FeetArmorCategory : public EnchantmentCategory {
public:
    const static FeetArmorCategory* sFeetArmorCategory;

    bool canEnchant(Item* item) const;
};