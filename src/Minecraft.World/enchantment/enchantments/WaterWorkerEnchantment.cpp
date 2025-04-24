#include "Minecraft.World/enchantment/categories/HeadArmorCategory.h"
#include "Minecraft.World/enchantment/enchantments/WaterWorkerEnchantment.h"

WaterWorkerEnchantment::WaterWorkerEnchantment(const Rarity* rarity,
                                               arrayWithLength<const EquipmentSlot*> equipmentSlots)
    : Enchantment(rarity, HeadArmorCategory::sHeadArmorCategory, equipmentSlots) {
    this->setDescriptionId(0x212CD6AE);
}

int WaterWorkerEnchantment::getMaxLevel() {
    return 1;
}

int WaterWorkerEnchantment::getMinCost(int a2) {
    return 1;
}

int WaterWorkerEnchantment::getMaxCost(int a2) {
    return this->getMinCost(a2) + 40;
}