#include "Enchantment.h"
#include "Minecraft.World/enchantment/EnchantmentCategory.h"
#include "Minecraft.World/item/ItemInstance.h"

const Rarity* Enchantment::getRarity() {
    return this->rarity;
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
    this->descriptionId = a2;
}

int Enchantment::getDescriptionId() {
    return this->descriptionId;
}

bool Enchantment::canEnchant(const std::shared_ptr<ItemInstance>& item){
    return enchantmentCategory->canEnchant(item->getItem());
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
Enchantment::~Enchantment() {

}