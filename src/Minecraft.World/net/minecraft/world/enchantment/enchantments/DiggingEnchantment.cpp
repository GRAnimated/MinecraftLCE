#include "types.h"
#include "Minecraft.World/enchantment/Enchantment.h"
#include "Minecraft.World/enchantment/categories/DiggerCategory.h"
#include "Minecraft.World/enchantment/enchantments/DiggingEnchantment.h"
#include "Minecraft.World/item/ItemInstance.h"
#include "Minecraft.World/item/Items.h"

DiggingEnchantment::DiggingEnchantment(const Rarity* rarity,
                                       arrayWithLength<const EquipmentSlot*> equipmentSlots)
    : Enchantment(rarity, DiggerCategory::sDiggerCategory, equipmentSlots) {
    this->setDescriptionId(0x7C8A12EF);
}

int DiggingEnchantment::getMaxLevel() {
    return 5;
}

int DiggingEnchantment::getMinCost(int a2) {
    return 10 * a2 - 9;
}

int DiggingEnchantment::getMaxCost(int a2) {
    return Enchantment::getMinCost(a2) + 50;
}

bool DiggingEnchantment::canEnchant(const not_null_ptr<ItemInstance>& other) {
    return other->getItem() == Items::SHEARS || Enchantment::canEnchant(not_null_ptr<ItemInstance>(other));
}