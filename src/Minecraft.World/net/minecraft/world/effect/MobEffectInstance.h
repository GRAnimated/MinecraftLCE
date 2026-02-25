#pragma once

#include "types.h"
#include <memory>

class CompoundTag;
class MobEffect;
class LivingEntity;

class MobEffectInstance {
public:
    MobEffectInstance(MobEffectInstance* other);
    MobEffectInstance(MobEffect* effect);
    MobEffectInstance(MobEffect* effect, int duration);
    MobEffectInstance(MobEffect* effect, int duration, int amplifier);
    MobEffectInstance(MobEffect* effect, int duration, int amplifier, bool ambient, bool showParticles);

    void init(MobEffect* effect, int duration, int amplifier, bool showParticles);
    void update(MobEffectInstance* other);
    int tickDownDuration();
    bool tick(std::shared_ptr<LivingEntity> entity);
    void setNoCounter(bool noCounter);
    void applyEffect(const std::shared_ptr<LivingEntity>& entity);

    CompoundTag* save(CompoundTag* tag);
    static MobEffectInstance* load(CompoundTag* tag);

    bool isVisible();
    bool isNoCounter();
    bool isAmbient();

    static int getColorValue(const std::vector<MobEffectInstance*>* instance);
    MobEffect* getEffect();
    int getDuration();
    int getDescriptionId();
    int getAmplifier();
    // bool compareTo(MobEffectInstance* other); // unused

    // TODO: Find name for this function
    int get_14() { return m_dword14; }

    MobEffect* m_effect;
    int m_duration;
    int m_amplifier;
    bool m_bool10;
    bool m_ambient;
    bool m_noCounter;
    bool m_particles;
    int m_dword14;
};

ASSERT_SIZEOF(MobEffectInstance, 0x18)
