#include "net/minecraft/world/enchantment/enchantments/ProtectionEnchantment.h"

#include "net/minecraft/client/ui/StringIDs.h"
#include "net/minecraft/world/damagesource/DamageSource.h"
#include "net/minecraft/world/enchantment/categories/ArmorCategory.h"
#include "net/minecraft/world/enchantment/categories/FeetArmorCategory.h"
#include "net/minecraft/world/item/enchantment/Enchantment.h"
#include "net/minecraft/world/item/enchantment/EnchantmentCategory.h"

const ProtectionEnchantment::Type* ALL = new ProtectionEnchantment::Type(StringIDs::Protection, 1, 11, 20);
const ProtectionEnchantment::Type* FIRE
    = new ProtectionEnchantment::Type(StringIDs::FireProtection, 10, 8, 12);
const ProtectionEnchantment::Type* FALL
    = new ProtectionEnchantment::Type(StringIDs::FeatherFalling, 5, 6, 10);
const ProtectionEnchantment::Type* EXPLOSION
    = new ProtectionEnchantment::Type(StringIDs::BlastProtection, 5, 8, 12);
const ProtectionEnchantment::Type* PROJECTILE
    = new ProtectionEnchantment::Type(StringIDs::ProjectileProtection, 3, 6, 15);

ProtectionEnchantment::Type::Type(int nameId, int minCost, int levelCost, int idk)
    : m_nameId(nameId), m_minCost(minCost), m_levelCost(levelCost), m_dwordC(idk) {}

ProtectionEnchantment::ProtectionEnchantment(const Rarity* rarity, const Type* type,
                                             arrayWithLength<const EquipmentSlot*> array)
    : Enchantment(rarity,
                  // those casts are required so that crap even compiles
                  type == FALL ? (const EnchantmentCategory*)FeetArmorCategory::sFeetArmorCategory :
                                 (const EnchantmentCategory*)ArmorCategory::sArmorCategory,
                  array) {
    this->m_type = type;
}

int ProtectionEnchantment::getMaxLevel() {
    return 4;
}
int ProtectionEnchantment::getMinCost(int a2) {
    const Type* type = this->m_type;
    return type->getMinCost() + (a2 - 1) * type->getLevelCost();
}
int ProtectionEnchantment::getMaxCost(int a2) {
    return this->getMinCost(a2) + this->m_type->getLevelCost();
}
int ProtectionEnchantment::getDamageProtection(int level, const DamageSource* source) {
    if (source->isBypassInvul()) {
        return 0;
    } else if (this->m_type == ALL) {
        return level;
    } else if (this->m_type == FIRE && source->isFire()) {
        return level * 2;
    } else if (this->m_type == FALL && source == DamageSource::BYPASS_ARMOUR) {
        return level * 3;
    } else if (this->m_type == PROJECTILE && source->isProjectile()) {
        return level * 2;
    } else {
        return this->m_type == EXPLOSION && source->isExplosion() ? level * 2 : 0;
    }
}
bool ProtectionEnchantment::checkCompatibility(const Enchantment* other) {
    const ProtectionEnchantment* otherCasted = dynamic_cast<const ProtectionEnchantment*>(other);
    if (otherCasted) {
        return otherCasted->m_type != this->m_type && (this->m_type == FALL || otherCasted->m_type == FALL);
    }
    return Enchantment::checkCompatibility(other);
}
int ProtectionEnchantment::getDescriptionId() {
    return this->m_type->getName();
}
