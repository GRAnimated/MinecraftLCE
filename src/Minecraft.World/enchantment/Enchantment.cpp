#include "Minecraft.World/enchantment/EnchantmentCategory.h"
#include "Minecraft.World/item/ItemInstance.h"
#include "Enchantment.h"

Enchantment::Enchantment(const Rarity* rarity, const EnchantmentCategory* category,
                         arrayWithLength<const EquipmentSlot*> array)
    : mEnchantmentCategory(category) {
    this->mRarity = rarity;
    this->mSlots = array;
}

const Rarity* Enchantment::getRarity() {
    return this->mRarity;
}

void Enchantment::getSlotItems(const std::shared_ptr<LivingEntity>&) {}

int Enchantment::getMinLevel() {
    return 1;
}

int Enchantment::getMaxLevel() {
    return 1;
}

int Enchantment::getMinCost(int a2) {
    return (10 * a2) | 1;
}

int Enchantment::getMaxCost(int a2) {
    return this->getMinCost(a2) + 5;
}

int Enchantment::getDamageProtection(int, DamageSource const*) {
    return 0;
}

float Enchantment::getDamageBonus(int, MobType) {
    return 0.0f;
}

bool Enchantment::checkCompatibility(Enchantment const* a2) {
    return this != a2;
}

void Enchantment::setDescriptionId(int a2) {
    this->mDescriptionId = a2;
}

int Enchantment::getDescriptionId() {
    return this->mDescriptionId;
}

bool Enchantment::canEnchant(const not_null_ptr<ItemInstance>& item) {
    return this->mEnchantmentCategory->canEnchant(item->getItem());
}

void Enchantment::doPostAttack(const std::shared_ptr<LivingEntity>&, const std::shared_ptr<Entity>&, int) {}

void Enchantment::doPostHurt(const std::shared_ptr<LivingEntity>&, const std::shared_ptr<Entity>&, int) {}

bool Enchantment::isTreasureOnly() {
    return false;
}

bool Enchantment::isCurse() {
    return false;
}

// I don't know how to handle destructors...
Enchantment::~Enchantment() {}