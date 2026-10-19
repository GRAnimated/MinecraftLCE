#include "net/minecraft/world/effect/MobEffectTypes.h"

// name guessed
AttackDamageMobEffect::AttackDamageMobEffect(bool harmful, eMinecraftColour color, double damage)
    : MobEffect(harmful, color), m_damage(damage) {}

// name guessed
double AttackDamageMobEffect::getAttributeModifierValue(int amplifier, AttributeModifier*) {
    return static_cast<int>(static_cast<unsigned int>(amplifier) + 1) * m_damage;
}
