#include "Minecraft.World/enchantment/EnchantmentCategory.h"

class BowCategory : public EnchantmentCategory {
public:
    static const BowCategory* sBowCategory;

    bool canEnchant(Item* item) const;
};