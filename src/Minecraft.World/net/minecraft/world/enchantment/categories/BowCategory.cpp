#include "net/minecraft/world/enchantment/categories/BowCategory.h"
#include "net/minecraft/world/item/BowItem.h"

const BowCategory* BowCategory::sBowCategory = new BowCategory();

bool BowCategory::canEnchant(Item* item) const {
    return dynamic_cast<BowItem*>(item);
}
