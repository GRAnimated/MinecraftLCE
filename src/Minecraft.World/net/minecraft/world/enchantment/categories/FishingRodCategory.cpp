#include "net/minecraft/world/enchantment/categories/FishingRodCategory.h"
#include "net/minecraft/world/item/FishingRodItem.h"

const FishingRodCategory* FishingRodCategory::sFishingRodCategory = new FishingRodCategory();

bool FishingRodCategory::canEnchant(Item* item) const {
    return dynamic_cast<FishingRodItem*>(item);
}
