#include "net/minecraft/world/effect/MobEffect.h"
#include "net/minecraft/world/entity/ai/attributes/AttributeModifier.h"

MappedRegistry<ResourceLocation, MobEffect*>* MobEffect::REGISTRY;
int MobEffect::EFFECT_COUNT;

MobEffect* MobEffect::byId(int id) {
    return REGISTRY->byId(id);
}

int MobEffect::getId(MobEffect* effect) {
    return REGISTRY->getId(effect);
}

int MobEffect::GetEffectCount() {
    return EFFECT_COUNT;
}

std::unordered_map<Attribute*, AttributeModifier*>& MobEffect::getAttributeModifiers() {
    return m_attributeModifiers;
}

double MobEffect::getAttributeModifierValue(int amplifier, AttributeModifier* modifier) {
    double amount = modifier->getAmount();
    return static_cast<int>(static_cast<unsigned int>(amplifier) + 1) * amount;
}
