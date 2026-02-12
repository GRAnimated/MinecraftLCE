#pragma once

#include "net/minecraft/world/item/enchantment/Enchantment.h"
#include <memory>

class ProtectionEnchantment : public Enchantment {
public:
    class Type {
    public:
        Type(int mNameId, int mMinCost, int mLevelCost, int dwordC);

        int getMinCost() const { return this->m_minCost; }
        int getLevelCost() const { return this->m_levelCost; }
        int getName() const { return this->m_nameId; }

        static const ProtectionEnchantment::Type* ALL;
        static const ProtectionEnchantment::Type* FIRE;
        static const ProtectionEnchantment::Type* FALL;
        static const ProtectionEnchantment::Type* EXPLOSION;
        static const ProtectionEnchantment::Type* PROJECTILE;

        int m_nameId;
        int m_minCost;
        int m_levelCost;
        int m_dwordC;
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

    const Type* m_type;
};
