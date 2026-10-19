#include "net/minecraft/world/item/FoodItem.h"

#include "net/minecraft/world/effect/MobEffectInstance.h"
#include "net/minecraft/world/item/ItemBootstrapTypes.h"

FoodItem::FoodItem(int nutrition, float saturation, bool meat)
    : m_nutrition(nutrition), m_saturation(saturation), m_meat(meat) {
    initEffects();
}

FoodItem::FoodItem(int nutrition, bool meat) : m_nutrition(nutrition), m_saturation(0.6f), m_meat(meat) {
    initEffects();
}

// name guessed
void FoodItem::initEffects() {
    m_alwaysEat = false;
    m_effect = nullptr;
    m_effectProbability = 0.0f;
}

// name guessed
FoodItem* FoodItem::setEffect(MobEffectInstance* effect, float probability) {
    delete m_effect;
    m_effect = effect;
    m_effectProbability = probability;
    return this;
}

// name guessed
FoodItem* FoodItem::setAlwaysEat() {
    m_alwaysEat = true;
    return this;
}
