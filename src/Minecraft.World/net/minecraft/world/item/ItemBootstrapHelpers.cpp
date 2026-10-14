#include "net/minecraft/world/effect/MobEffectInstance.h"
#include "net/minecraft/world/item/ItemBootstrapTypes.h"

TintedBlockItem* TintedBlockItem::setDescriptionIds(arrayWithLength<int> ids) {
    m_descriptionIds = arrayWithLength<int>(ids.m_length, true);
    for (unsigned int i = 0; i < ids.m_length; ++i)
        m_descriptionIds[i] = ids[i];
    return this;
}

FoodItem::FoodItem(int nutrition, float saturation, bool meat)
    : m_nutrition(nutrition), m_saturation(saturation), m_meat(meat) {
    initEffects();
}

FoodItem::FoodItem(int nutrition, bool meat) : m_nutrition(nutrition), m_saturation(0.6f), m_meat(meat) {
    initEffects();
}

void FoodItem::initEffects() {
    m_alwaysEat = false;
    m_effect = nullptr;
    m_effectProbability = 0.0f;
}

FoodItem* FoodItem::setEffect(MobEffectInstance* effect, float probability) {
    delete m_effect;
    m_effect = effect;
    m_effectProbability = probability;
    return this;
}

FoodItem* FoodItem::setAlwaysEat() {
    m_alwaysEat = true;
    return this;
}
