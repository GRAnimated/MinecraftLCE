#include "net/minecraft/world/effect/MobEffectTypes.h"

// name guessed
void HealthBoostMobEffect::removeAttributeModifiers(const std::shared_ptr<LivingEntity>& entity,
                                                    BaseAttributeMap* attributes, int amplifier) {
    MobEffect::removeAttributeModifiers(entity, attributes, amplifier);
    if (entity->getHealth() > entity->getMaxHealth()) {
        entity->setHealth(entity->getMaxHealth());
    }
}

// name guessed
HealthBoostMobEffect::HealthBoostMobEffect(bool harmful, eMinecraftColour color)
    : MobEffect(harmful, color) {}
