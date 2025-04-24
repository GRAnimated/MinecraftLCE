#include "Minecraft.World/enchantment/EnchantmentCategory.h"

class HeadArmorCategory : public EnchantmentCategory {
public:
    static const HeadArmorCategory* sHeadArmorCategory;
    bool canEnchant(Item* item) const;
};