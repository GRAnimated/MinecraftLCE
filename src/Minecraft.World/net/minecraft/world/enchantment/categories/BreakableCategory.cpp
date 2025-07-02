#include "Minecraft.World/enchantment/categories/BreakableCategory.h"
#include "Minecraft.World/item/Item.h"

const BreakableCategory* BreakableCategory::sBreakableCategory = new BreakableCategory();

bool BreakableCategory::canEnchant(Item* item) const {
    return item->canBeDepleted();
}