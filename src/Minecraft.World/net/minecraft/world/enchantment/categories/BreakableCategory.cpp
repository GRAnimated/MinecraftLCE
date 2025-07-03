#include "net/minecraft/world/enchantment/categories/BreakableCategory.h"
#include "net/minecraft/world/item/Item.h"

const BreakableCategory* BreakableCategory::sBreakableCategory = new BreakableCategory();

bool BreakableCategory::canEnchant(Item* item) const {
    return item->canBeDepleted();
}
