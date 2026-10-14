#include "net/minecraft/world/effect/MobEffectTypes.h"

AbsoptionMobEffect::AbsoptionMobEffect(bool harmful, eMinecraftColour color) : MobEffect(harmful, color) {}

AttackDamageMobEffect::AttackDamageMobEffect(bool harmful, eMinecraftColour color, double damage)
    : MobEffect(harmful, color), m_damage(damage) {}

HealthBoostMobEffect::HealthBoostMobEffect(bool harmful, eMinecraftColour color)
    : MobEffect(harmful, color) {}

InstantenousMobEffect::InstantenousMobEffect(bool harmful, eMinecraftColour color)
    : MobEffect(harmful, color) {}

double AttackDamageMobEffect::getAttributeModifierValue(int amplifier, AttributeModifier*) {
    return static_cast<int>(static_cast<unsigned int>(amplifier) + 1) * m_damage;
}

bool InstantenousMobEffect::isInstantenous() {
    return true;
}

bool InstantenousMobEffect::isDurationEffectTick(int tick, int) {
    return tick > 0;
}
