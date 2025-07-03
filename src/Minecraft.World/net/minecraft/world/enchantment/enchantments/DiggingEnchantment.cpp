#include "net/minecraft/world/enchantment/enchantments/DiggingEnchantment.h"

#include "net/minecraft/world/enchantment/categories/DiggerCategory.h"
#include "net/minecraft/world/item/ItemInstance.h"
#include "net/minecraft/world/item/Items.h"
#include "net/minecraft/world/item/enchantment/Enchantment.h"
#include "types.h"

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
