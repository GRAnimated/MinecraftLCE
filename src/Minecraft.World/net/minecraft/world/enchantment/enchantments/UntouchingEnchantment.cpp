#include "net/minecraft/world/enchantment/enchantments/UntouchingEnchantment.h"

#include "net/minecraft/client/ui/StringIDs.h"
#include "net/minecraft/world/enchantment/categories/DiggerCategory.h"
#include "net/minecraft/world/item/enchantment/Enchantment.h"
#include "net/minecraft/world/item/enchantment/Enchantments.h"

UntouchingEnchantment::UntouchingEnchantment(const Rarity* rarity,
                                             arrayWithLength<const EquipmentSlot*> equipmentSlots)
    : Enchantment(rarity, DiggerCategory::sDiggerCategory, equipmentSlots) {
    this->setDescriptionId(StringIDs::SilkTouch);
}

int UntouchingEnchantment::getMaxLevel() {
    return 1;
}

int UntouchingEnchantment::getMinCost(int a2) {
    return 15;
}

int UntouchingEnchantment::getMaxCost(int a2) {
    return Enchantment::getMinCost(a2) + 50;
}

bool UntouchingEnchantment::checkCompatibility(const Enchantment* other) {
    return Enchantment::checkCompatibility(other) && Enchantments::FORTUNE != other;
}
