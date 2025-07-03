#pragma once

#include "net/minecraft/world/ArrayWithLength.h"
#include "net/minecraft/world/item/Item.h"

class DiggerItem : public Item {
public:
    DiggerItem(const Item::Tier* tier, arrayWithLength<Block*> blocks);
    DiggerItem(float attackDamage, float attackSpeed, const Item::Tier* tier, arrayWithLength<Block*> blocks);

    void _init(float attackDamage, float attackSpeed, arrayWithLength<Block*> blocks);

    ~DiggerItem() override;
    float getDestroySpeed(not_null_ptr<ItemInstance>, BlockState*) override;
    bool hurtEnemy(not_null_ptr<ItemInstance>, std::shared_ptr<LivingEntity> victim,
                   std::shared_ptr<LivingEntity> attacker) override;
    bool mineBlock(not_null_ptr<ItemInstance>, Level*, const BlockState*, const BlockPos&,
                   std::shared_ptr<LivingEntity>) override;
    bool isHandEquipped() override;
    int getEnchantmentValue() override;
    bool isValidRepairItem(not_null_ptr<ItemInstance> source, not_null_ptr<ItemInstance> repairItem) override;
    std::unordered_map<eATTRIBUTE_ID, AttributeModifier*>*
    getDefaultAttributeModifiers(const EquipmentSlot*) override;

    arrayWithLength<Block*> mBlocks = arrayWithLength<Block*>();
    float mSpeed;
    float mAttackDamage;
    float mAttackSpeed;
    const Item::Tier* mTier;
};
