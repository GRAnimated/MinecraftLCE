#include "Minecraft.World/enchantment/EnchantmentCategory.h"

class AllCategory : public EnchantmentCategory {
public:
    static const AllCategory* sAllCategory;

    bool canEnchant(Item* item) const;
};