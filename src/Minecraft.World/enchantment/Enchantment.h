#pragma once
#include <memory>
#include "Minecraft.World/ArrayWithLength.h"

class EnchantmentCategory;
class EquipmentSlot;
class LivingEntity;
class DamageSource;
class MobType{};
class ItemInstance;
class Entity;
class Rarity;

class Enchantment {
    public:
        Enchantment(const Rarity* rarity, const EnchantmentCategory* category, arrayWithLength<EquipmentSlot>* array) {
            this->enchantmentCategory = category;
            this->rarity = rarity;
            this->slots.data = array->data;
            this->slots.length = array->length;
        }
    
        virtual const Rarity* getRarity();
        virtual void getSlotItems(const std::shared_ptr<LivingEntity>&);
        virtual int getMinLevel();
        virtual int getMaxLevel();
        virtual int getMinCost(int);
        virtual int getMaxCost(int);
        virtual int getDamageProtection(int, DamageSource const*);
        virtual float getDamageBonus(int, MobType);
        virtual bool checkCompatibility(Enchantment const*);
        virtual void setDescriptionId(int);
        virtual int getDescriptionId();
        virtual void getFullname(int);
        virtual bool canEnchant(const std::shared_ptr<ItemInstance>&);
        virtual void doPostAttack(const std::shared_ptr<LivingEntity>&, const std::shared_ptr<Entity>&, int);
        virtual void doPostHurt(const std::shared_ptr<LivingEntity>&, const std::shared_ptr<Entity>&, int);
        virtual bool isTreasureOnly();
        virtual bool isCurse();
        virtual ~Enchantment();
    
        const EnchantmentCategory* enchantmentCategory;
        int descriptionId;
        arrayWithLength<EquipmentSlot> slots;
        const Rarity* rarity;
    };