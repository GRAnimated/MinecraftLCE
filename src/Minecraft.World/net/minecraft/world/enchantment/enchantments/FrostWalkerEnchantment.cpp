#include "net/minecraft/world/enchantment/enchantments/FrostWalkerEnchantment.h"

#include "net/minecraft/client/ui/StringIDs.h"
#include "net/minecraft/world/enchantment/categories/FeetArmorCategory.h"
#include "net/minecraft/world/item/enchantment/Enchantment.h"
#include "net/minecraft/world/item/enchantment/Enchantments.h"

FrostWalkerEnchantment::FrostWalkerEnchantment(const Rarity* rarity,
                                               arrayWithLength<const EquipmentSlot*> equipmentSlots)
    : Enchantment(rarity, FeetArmorCategory::sFeetArmorCategory, equipmentSlots) {
    this->setDescriptionId(StringIDs::FrostWalker);
}

int FrostWalkerEnchantment::getMaxLevel() {
    return 2;
}

int FrostWalkerEnchantment::getMinCost(int a2) {
    return 10 * a2;
}

int FrostWalkerEnchantment::getMaxCost(int a2) {
    return this->getMinCost(a2) + 15;
}

bool FrostWalkerEnchantment::isTreasureOnly() {
    return true;
}

bool FrostWalkerEnchantment::checkCompatibility(const Enchantment* other) {
    return Enchantment::checkCompatibility(other) && Enchantments::DEPTH_STRIDER != other;
}
