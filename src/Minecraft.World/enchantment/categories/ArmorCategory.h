#include "Minecraft.World/enchantment/EnchantmentCategory.h"

class ArmorCategory : public EnchantmentCategory {
public:
    static const ArmorCategory* sArmorCategory;

    bool canEnchant(Item* item) const;
};