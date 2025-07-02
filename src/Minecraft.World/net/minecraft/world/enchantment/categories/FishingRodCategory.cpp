#include "Minecraft.World/enchantment/categories/FishingRodCategory.h"
#include "Minecraft.World/item/FishingRodItem.h"

const FishingRodCategory* FishingRodCategory::sFishingRodCategory = new FishingRodCategory();

bool FishingRodCategory::canEnchant(Item* item) const {
    return dynamic_cast<FishingRodItem*>(item);
}