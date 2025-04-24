#include "Minecraft.World/enchantment/Enchantment.h"

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
    int getDamageProtection(int, DamageSource const*) override;
    bool checkCompatibility(Enchantment const*) override;
    int getDescriptionId() override;

    const Type* mType;
};
