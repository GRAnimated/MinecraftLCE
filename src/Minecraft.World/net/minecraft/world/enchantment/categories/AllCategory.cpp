#include "Minecraft.World/enchantment/categories/AllCategory.h"

const AllCategory* AllCategory::sAllCategory = new AllCategory();

// NON_MATCHING: you need to store all categories in array
bool AllCategory::canEnchant(Item* item) const {
    return false;
}