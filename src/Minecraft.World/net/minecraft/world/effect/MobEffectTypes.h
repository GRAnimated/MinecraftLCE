#pragma once

#include "net/minecraft/world/effect/MobEffect.h"

// Preserve the original subclass vtables as external dependencies while their
// destructors await reconstruction.
class AbsoptionMobEffect : public MobEffect {
public:
    AbsoptionMobEffect(bool harmful, eMinecraftColour color);
    ~AbsoptionMobEffect() override;
    void removeAttributeModifiers(const std::shared_ptr<LivingEntity>&, BaseAttributeMap*, int) override;
    void addAttributeModifiers(const std::shared_ptr<LivingEntity>&, BaseAttributeMap*, int) override;
};

class AttackDamageMobEffect : public MobEffect {
public:
    AttackDamageMobEffect(bool harmful, eMinecraftColour color, double damage);
    ~AttackDamageMobEffect() override;
    double getAttributeModifierValue(int amplifier, AttributeModifier*) override;

    double m_damage;
};

class HealthBoostMobEffect : public MobEffect {
public:
    HealthBoostMobEffect(bool harmful, eMinecraftColour color);
    ~HealthBoostMobEffect() override;
    void removeAttributeModifiers(const std::shared_ptr<LivingEntity>&, BaseAttributeMap*, int) override;
};

class InstantenousMobEffect : public MobEffect {
public:
    InstantenousMobEffect(bool harmful, eMinecraftColour color);
    ~InstantenousMobEffect() override;
    bool isInstantenous() override;
    bool isDurationEffectTick(int tick, int amplifier) override;
};

ASSERT_SIZEOF(AbsoptionMobEffect, 0x50)
ASSERT_SIZEOF(AttackDamageMobEffect, 0x58)
ASSERT_SIZEOF(HealthBoostMobEffect, 0x50)
ASSERT_SIZEOF(InstantenousMobEffect, 0x50)
