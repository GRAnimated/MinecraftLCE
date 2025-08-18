#include "net/minecraft/world/enchantment/enchantments/DigDurabilityEnchantment.h"

#include "net/minecraft/client/ui/StringIDs.h"
#include "net/minecraft/world/enchantment/categories/BreakableCategory.h"
#include "net/minecraft/world/item/ItemInstance.h"
#include "net/minecraft/world/item/enchantment/Enchantment.h"
#include "types.h"

DigDurabilityEnchantment::DigDurabilityEnchantment(const Rarity* rarity,
                                                   arrayWithLength<const EquipmentSlot*> equipmentSlots)
    : Enchantment(rarity, BreakableCategory::sBreakableCategory, equipmentSlots) {
    this->setDescriptionId(StringIDs::Unbreaking);
}

int DigDurabilityEnchantment::getMaxLevel() {
    return 3;
}

int DigDurabilityEnchantment::getMinCost(int a2) {
    return 8 * a2 - 3;
}

int DigDurabilityEnchantment::getMaxCost(int a2) {
    return Enchantment::getMinCost(a2) + 50;
}

bool DigDurabilityEnchantment::canEnchant(const not_null_ptr<ItemInstance>& other) {
    return other->isDamageableItem() || Enchantment::canEnchant(not_null_ptr<ItemInstance>(other));
}
