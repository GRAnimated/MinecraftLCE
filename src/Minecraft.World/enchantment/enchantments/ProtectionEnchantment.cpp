#include "Minecraft.World/enchantment/Enchantment.h"
#include "Minecraft.World/enchantment/EnchantmentCategory.h"
#include "Minecraft.World/enchantment/categories/ArmorCategory.h"
#include "Minecraft.World/enchantment/categories/FeetArmorCategory.h"
#include "Minecraft.World/enchantment/enchantments/ProtectionEnchantment.h"
#include "Minecraft.World/level/DamageSource.h"

const ProtectionEnchantment::Type* ALL = new ProtectionEnchantment::Type(0xF84A0F07, 1, 11, 20);
const ProtectionEnchantment::Type* FIRE = new ProtectionEnchantment::Type(0xE1AA8A26, 10, 8, 12);
const ProtectionEnchantment::Type* FALL = new ProtectionEnchantment::Type(0xF470F5F1, 5, 6, 10);
const ProtectionEnchantment::Type* EXPLOSION = new ProtectionEnchantment::Type(0x7FF9AA23, 5, 8, 12);
const ProtectionEnchantment::Type* PROJECTILE = new ProtectionEnchantment::Type(0xCF623683, 3, 6, 15);

ProtectionEnchantment::Type::Type(int nameId, int minCost, int levelCost, int idk)
    : mNameId(nameId), mMinCost(minCost), mLevelCost(levelCost), dwordC(idk) {}

ProtectionEnchantment::ProtectionEnchantment(const Rarity* rarity, const Type* type,
                                             arrayWithLength<const EquipmentSlot*> array)
    : Enchantment(rarity,
                  // those casts are required so that crap even compiles
                  type == FALL ? (const EnchantmentCategory*)FeetArmorCategory::sFeetArmorCategory :
                                 (const EnchantmentCategory*)ArmorCategory::sArmorCategory,
                  array) {
    this->mType = type;
}

int ProtectionEnchantment::getMaxLevel() {
    return 4;
}
int ProtectionEnchantment::getMinCost(int a2) {
    const Type* type = this->mType;
    return type->getMinCost() + (a2 - 1) * type->getLevelCost();
}
int ProtectionEnchantment::getMaxCost(int a2) {
    return this->getMinCost(a2) + this->mType->getLevelCost();
}
int ProtectionEnchantment::getDamageProtection(int level, DamageSource const* source) {
    if (source->isBypassInvul()) {
        return 0;
    } else if (this->mType == ALL) {
        return level;
    } else if (this->mType == FIRE && source->isFire()) {
        return level * 2;
    } else if (this->mType == FALL && source == DamageSource::BYPASS_ARMOUR) {
        return level * 3;
    } else if (this->mType == EXPLOSION && source->isExplosion()) {
        return level * 2;
    } else {
        return this->mType == PROJECTILE && source->isProjectile() ? level * 2 : 0;
    }
}
bool ProtectionEnchantment::checkCompatibility(Enchantment const* other) {
    const ProtectionEnchantment* otherCasted = dynamic_cast<const ProtectionEnchantment*>(other);
    if (otherCasted) {
        return otherCasted->mType != this->mType && (this->mType == FALL || otherCasted->mType == FALL);
    }
    return Enchantment::checkCompatibility(other);
}
int ProtectionEnchantment::getDescriptionId() {
    return this->mType->getName();
}