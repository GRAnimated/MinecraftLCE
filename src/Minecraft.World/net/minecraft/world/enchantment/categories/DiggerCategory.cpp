#include "Minecraft.World/enchantment/categories/DiggerCategory.h"
#include "Minecraft.World/item/DiggerItem.h"

const DiggerCategory* DiggerCategory::sDiggerCategory = new DiggerCategory();

bool DiggerCategory::canEnchant(Item* item) const {
    return dynamic_cast<DiggerItem*>(item);
}