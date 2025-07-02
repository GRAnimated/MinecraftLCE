#include "Minecraft.World/enchantment/Enchantment.h"
#include "Minecraft.World/enchantment/Enchantments.h"
#include "Minecraft.World/enchantment/categories/DiggerCategory.h"
#include "Minecraft.World/enchantment/enchantments/UntouchingEnchantment.h"

UntouchingEnchantment::UntouchingEnchantment(const Rarity* rarity,
                                             arrayWithLength<const EquipmentSlot*> equipmentSlots)
    : Enchantment(rarity, DiggerCategory::sDiggerCategory, equipmentSlots) {
    this->setDescriptionId(0x68376DD4);
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