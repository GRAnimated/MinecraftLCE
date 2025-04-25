#include "Minecraft.World/enchantment/categories/WeaponCategory.h"
#include "Minecraft.World/item/SwordItem.h"

const WeaponCategory* WeaponCategory::sWeaponCategory = new WeaponCategory();

bool WeaponCategory::canEnchant(Item* item) const {
    return dynamic_cast<SwordItem*>(item);
}