#include "net/minecraft/world/enchantment/enchantments/WaterWorkerEnchantment.h"

#include "net/minecraft/client/ui/StringIDs.h"
#include "net/minecraft/world/enchantment/categories/HeadArmorCategory.h"

WaterWorkerEnchantment::WaterWorkerEnchantment(const Rarity* rarity,
                                               arrayWithLength<const EquipmentSlot*> equipmentSlots)
    : Enchantment(rarity, HeadArmorCategory::sHeadArmorCategory, equipmentSlots) {
    this->setDescriptionId(StringIDs::AquaAffinity);
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
