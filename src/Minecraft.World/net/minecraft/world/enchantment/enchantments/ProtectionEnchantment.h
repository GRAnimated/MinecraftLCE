#pragma once

#include "net/minecraft/world/enchantment/Enchantment.h"
#include <memory>

class ProtectionEnchantment : public Enchantment {
public:
    class Type {
    public:
        Type(int mNameId, int mMinCost, int mLevelCost, int dwordC);

        int getMinCost() const { return this->mMinCost; }
        int getLevelCost() const { return this->mLevelCost; }
        int getName() const { return this->mNameId; }

        static const ProtectionEnchantment::Type* ALL;
        static const ProtectionEnchantment::Type* FIRE;
        static const ProtectionEnchantment::Type* FALL;
        static const ProtectionEnchantment::Type* EXPLOSION;
        static const ProtectionEnchantment::Type* PROJECTILE;

        int mNameId;
        int mMinCost;
        int mLevelCost;
        int dwordC;
    };
    ProtectionEnchantment(const Rarity* rarity, const Type* type,
                          arrayWithLength<const EquipmentSlot*> array);

    int getMaxLevel() override;
    int getMinCost(int) override;
    int getMaxCost(int) override;
    int getDamageProtection(int, const DamageSource*) override;
    bool checkCompatibility(const Enchantment*) override;
    int getDescriptionId() override;

    static int getFireAfterDampener(const std::shared_ptr<LivingEntity>&, int);

    const Type* mType;
};
