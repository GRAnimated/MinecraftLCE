#include "Minecraft.World/enchantment/categories/ArmorCategory.h"
#include "Minecraft.World/item/ArmorItem.h"

const ArmorCategory* ArmorCategory::sArmorCategory = new ArmorCategory();

bool ArmorCategory::canEnchant(Item* item) const {
    return dynamic_cast<ArmorItem*>(item);
}