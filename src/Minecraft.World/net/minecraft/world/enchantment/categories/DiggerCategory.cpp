#include "net/minecraft/world/enchantment/categories/DiggerCategory.h"
#include "net/minecraft/world/item/DiggerItem.h"

const DiggerCategory* DiggerCategory::sDiggerCategory = new DiggerCategory();

bool DiggerCategory::canEnchant(Item* item) const {
    return dynamic_cast<DiggerItem*>(item);
}