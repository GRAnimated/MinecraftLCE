#include "Minecraft.World/enchantment/EnchantmentCategory.h"

class BreakableCategory : public EnchantmentCategory {
public:
    static const BreakableCategory* sBreakableCategory;

    bool canEnchant(Item* item) const;
};