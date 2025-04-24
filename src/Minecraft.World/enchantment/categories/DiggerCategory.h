#include "Minecraft.World/enchantment/EnchantmentCategory.h"

class DiggerCategory : public EnchantmentCategory {
public:
    static const DiggerCategory* sDiggerCategory;

    bool canEnchant(Item* item) const;
};