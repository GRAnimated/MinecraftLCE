#pragma once

#include "net/minecraft/world/item/Item.h"

class MobEffectInstance;

class FoodItem : public Item {
public:
    FoodItem(int nutrition, float saturation, bool meat);
    FoodItem(int nutrition, bool meat);

    unsigned int GetUseTooltip(const ItemToolTipDataHolder&) override;
    InteractionResultHolder use(Level*, std::shared_ptr<Player>, InteractionHand::EInteractionHand) override;
    not_null_ptr<ItemInstance> finishUsingItem(not_null_ptr<ItemInstance>, Level*,
                                               std::shared_ptr<LivingEntity>) override;
    int getUseAnimation(not_null_ptr<ItemInstance>) override;
    int getUseDuration(not_null_ptr<ItemInstance>) override;

    virtual void applyFoodEffect(not_null_ptr<ItemInstance>, Level*, std::shared_ptr<Player>);
    virtual int getNutrition(const not_null_ptr<ItemInstance>&);
    virtual float getSaturationModifier(const not_null_ptr<ItemInstance>&);
    virtual bool isMeat();
    virtual FoodItem* setEffect(MobEffectInstance*, float probability);
    virtual FoodItem* setAlwaysEat();

    void initEffects();

    int m_nutrition;
    float m_saturation;
    bool m_meat;
    bool m_alwaysEat;
    MobEffectInstance* m_effect;
    float m_effectProbability;
};

ASSERT_SIZEOF(FoodItem, 0x98)
