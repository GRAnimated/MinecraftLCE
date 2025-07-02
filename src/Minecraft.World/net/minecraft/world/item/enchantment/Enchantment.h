#pragma once
#include "types.h"
#include "net/minecraft/world/ArrayWithLength.h"
#include "net/minecraft/world/entity/MobType.h"
#include <memory>

class EnchantmentCategory;
class EquipmentSlot;
class LivingEntity;
class DamageSource;
class ItemInstance;
class Entity;
class Rarity;

class Enchantment {
public:
    Enchantment(const Rarity* rarity, const EnchantmentCategory* category,
                arrayWithLength<const EquipmentSlot*> array);

    static void staticCtor();

    virtual const Rarity* getRarity();
    virtual void getSlotItems(const std::shared_ptr<LivingEntity>&);
    virtual int getMinLevel();
    virtual int getMaxLevel();
    virtual int getMinCost(int);
    virtual int getMaxCost(int);
    virtual int getDamageProtection(int, const DamageSource*);
    virtual float getDamageBonus(int, MobType);
    virtual bool checkCompatibility(const Enchantment*);
    virtual void setDescriptionId(int);
    virtual int getDescriptionId();
    virtual void getFullname(int);
    virtual bool canEnchant(const not_null_ptr<ItemInstance>&);
    virtual void doPostAttack(const std::shared_ptr<LivingEntity>&, const std::shared_ptr<Entity>&, int);
    virtual void doPostHurt(const std::shared_ptr<LivingEntity>&, const std::shared_ptr<Entity>&, int);
    virtual bool isTreasureOnly();
    virtual bool isCurse();
    virtual ~Enchantment();

    const EnchantmentCategory* mEnchantmentCategory;
    int mDescriptionId;
    arrayWithLength<const EquipmentSlot*> mSlots;
    const Rarity* mRarity;
};