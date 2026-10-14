#include "net/minecraft/world/effect/MobEffectTypes.h"

void AbsoptionMobEffect::removeAttributeModifiers(const std::shared_ptr<LivingEntity>& entity,
                                                  BaseAttributeMap* attributes, int amplifier) {
    entity->setAbsorptionAmount(
        entity->getAbsorptionAmount()
        - static_cast<float>(static_cast<int>(static_cast<unsigned int>(amplifier) * 4 + 4)));
    MobEffect::removeAttributeModifiers(entity, attributes, amplifier);
}

void AbsoptionMobEffect::addAttributeModifiers(const std::shared_ptr<LivingEntity>& entity,
                                               BaseAttributeMap* attributes, int amplifier) {
    entity->setAbsorptionAmount(
        entity->getAbsorptionAmount()
        + static_cast<float>(static_cast<int>(static_cast<unsigned int>(amplifier) * 4 + 4)));
    MobEffect::addAttributeModifiers(entity, attributes, amplifier);
}

void HealthBoostMobEffect::removeAttributeModifiers(const std::shared_ptr<LivingEntity>& entity,
                                                    BaseAttributeMap* attributes, int amplifier) {
    MobEffect::removeAttributeModifiers(entity, attributes, amplifier);
    if (entity->getHealth() > entity->getMaxHealth()) {
        entity->setHealth(entity->getMaxHealth());
    }
}
