#include "types.h"
#include "Minecraft.World/enchantment/Enchantment.h"
#include "Minecraft.World/enchantment/categories/BreakableCategory.h"
#include "Minecraft.World/enchantment/enchantments/DigDurabilityEnchantment.h"
#include "Minecraft.World/item/ItemInstance.h"

DigDurabilityEnchantment::DigDurabilityEnchantment(const Rarity* rarity,
                                                   arrayWithLength<const EquipmentSlot*> equipmentSlots)
    : Enchantment(rarity, BreakableCategory::sBreakableCategory, equipmentSlots) {
    this->setDescriptionId(0xF4AF0AC3);
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