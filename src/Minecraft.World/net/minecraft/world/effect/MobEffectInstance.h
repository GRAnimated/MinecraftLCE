#pragma once

#include "com/mojang/nbt/CompoundTag.h"
#include "net/minecraft/world/effect/MobEffect.h"
#include "net/minecraft/world/entity/LivingEntity.h"
#include <cstdint>

class MobEffectInstance {
public:
    MobEffectInstance(MobEffectInstance* instance);
    MobEffectInstance(MobEffect* effect);
    MobEffectInstance(MobEffect*, int duration);
    MobEffectInstance(MobEffect*, int duration, int amplifier);
    MobEffectInstance(MobEffect*, int duration, int amplifier, bool ambient, bool showParticles);
    void init(MobEffect* effect, int duration, int amplifier, bool showParticles);
    void update(MobEffectInstance* instance);
    void tickDownDuration();
    void tick(std::shared_ptr<LivingEntity> entity);
    void setNoCounter(bool noCounter);
    void save(CompoundTag* tag);
    bool isVisible();
    bool isNoCounter();
    bool isAmbient();
    MobEffect* getEffect();
    int getDuration();
    int getDescriptionId();
    int getAmplifier();
    bool compareTo(MobEffectInstance* instance);
    void applyEffect(std::shared_ptr<LivingEntity> entity);

    MobEffect* mEffect;
    int mDuration;
    int mAmplifier;
    bool bool10;
    bool mAmbient;
    bool mNoCounter;
    bool mParticles;
    int dword14;
};
