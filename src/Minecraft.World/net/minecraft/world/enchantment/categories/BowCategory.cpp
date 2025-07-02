#include "Minecraft.World/enchantment/categories/BowCategory.h"
#include "Minecraft.World/item/BowItem.h"

const BowCategory* BowCategory::sBowCategory = new BowCategory();

bool BowCategory::canEnchant(Item* item) const {
    return dynamic_cast<BowItem*>(item);
}