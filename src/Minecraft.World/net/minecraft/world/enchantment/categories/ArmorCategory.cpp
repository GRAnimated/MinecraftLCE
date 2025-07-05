#include "net/minecraft/world/enchantment/categories/ArmorCategory.h"
#include "net/minecraft/world/item/ArmorItem.h"

const ArmorCategory* ArmorCategory::sArmorCategory = new ArmorCategory();

bool ArmorCategory::canEnchant(Item* item) const {
    return dynamic_cast<ArmorItem*>(item);
}
