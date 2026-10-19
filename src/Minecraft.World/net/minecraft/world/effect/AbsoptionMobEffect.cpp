#include "net/minecraft/world/effect/MobEffectTypes.h"

// name guessed
void AbsoptionMobEffect::removeAttributeModifiers(const std::shared_ptr<LivingEntity>& entity,
                                                  BaseAttributeMap* attributes, int amplifier) {
    entity->setAbsorptionAmount(
        entity->getAbsorptionAmount()
        - static_cast<float>(static_cast<int>(static_cast<unsigned int>(amplifier) * 4 + 4)));
    MobEffect::removeAttributeModifiers(entity, attributes, amplifier);
}

// name guessed
void AbsoptionMobEffect::addAttributeModifiers(const std::shared_ptr<LivingEntity>& entity,
                                               BaseAttributeMap* attributes, int amplifier) {
    entity->setAbsorptionAmount(
        entity->getAbsorptionAmount()
        + static_cast<float>(static_cast<int>(static_cast<unsigned int>(amplifier) * 4 + 4)));
    MobEffect::addAttributeModifiers(entity, attributes, amplifier);
}

AbsoptionMobEffect::AbsoptionMobEffect(bool harmful, eMinecraftColour color) : MobEffect(harmful, color) {}
