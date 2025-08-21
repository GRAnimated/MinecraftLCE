#include "net/minecraft/world/enchantment/enchantments/WaterWalkerEnchantment.h"

#include "net/minecraft/client/ui/StringIDs.h"
#include "net/minecraft/world/enchantment/categories/FeetArmorCategory.h"
#include "net/minecraft/world/item/enchantment/Enchantment.h"
#include "net/minecraft/world/item/enchantment/Enchantments.h"

WaterWalkerEnchantment::WaterWalkerEnchantment(const Rarity* rarity,
                                               arrayWithLength<const EquipmentSlot*> equipmentSlots)
    : Enchantment(rarity, FeetArmorCategory::sFeetArmorCategory, equipmentSlots) {
    this->setDescriptionId(StringIDs::DepthStrider);
}

int WaterWalkerEnchantment::getMaxLevel() {
    return 3;
}

int WaterWalkerEnchantment::getMinCost(int a2) {
    return 10 * a2;
}

int WaterWalkerEnchantment::getMaxCost(int a2) {
    return Enchantment::getMinCost(a2) + 15;
}

bool WaterWalkerEnchantment::checkCompatibility(const Enchantment* other) {
    return Enchantment::checkCompatibility(other) && Enchantments::FROST_WALKER != other;
}
