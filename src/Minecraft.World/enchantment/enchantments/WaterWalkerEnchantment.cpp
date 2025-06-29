#include "Minecraft.World/enchantment/Enchantment.h"
#include "Minecraft.World/enchantment/Enchantments.h"
#include "Minecraft.World/enchantment/categories/FeetArmorCategory.h"
#include "Minecraft.World/enchantment/enchantments/WaterWalkerEnchantment.h"

WaterWalkerEnchantment::WaterWalkerEnchantment(const Rarity* rarity,
                                               arrayWithLength<const EquipmentSlot*> equipmentSlots)
    : Enchantment(rarity, FeetArmorCategory::sFeetArmorCategory, equipmentSlots) {
    this->setDescriptionId(0xD41BAEBF);
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