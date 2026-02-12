#include "net/minecraft/world/effect/MobEffect.h"
#include "net/minecraft/world/effect/MobEffects.h"

MobEffect::MobEffect(bool harmful, eMinecraftColour color) {
    m_harmful = harmful;
    m_color = color;
    m_beneficial = false;
    m_descriptionId = -1;
    m_icon = EMobEffectIcon::Unknown;
    if (harmful)
        m_durationModifier = 0.5;
    else
        m_durationModifier = 1.0;
}

bool MobEffect::isDurationEffectTick(int tick, int amplifier) {
    int interval;

    if (this == MobEffects::REGENERATION) {
        interval = 50 >> amplifier;
        if (interval < 1) {
            return true;
        }
        return (tick % interval) == 0;
    }

    if (this == MobEffects::POISON) {
        interval = 25 >> amplifier;
        if (interval < 1) {
            return true;
        }
        return (tick % interval) == 0;
    }

    if (this == MobEffects::WITHER) {
        interval = 40 >> amplifier;
        if (interval < 1) {
            return true;
        }
        return (tick % interval) == 0;
    }

    return this == MobEffects::HUNGER;
}

void MobEffect::setIcon(EMobEffectIcon icon) {
    m_icon = icon;
}

void MobEffect::setDurationModifier(double durationModifier) {
    m_durationModifier = durationModifier;
}

void MobEffect::setDescriptionId(int descriptionId) {
    m_descriptionId = descriptionId;
}

void MobEffect::setBeneficial() {
    m_beneficial = true;
}

bool MobEffect::isInstantenous() {
    return false;
}

bool MobEffect::isHarmful() {
    return m_harmful;
}

bool MobEffect::isBeneficial() const {
    return m_beneficial;
}

bool MobEffect::hasIcon() {
    return m_icon != MobEffect::EMobEffectIcon::Unknown;
}

MobEffect::EMobEffectIcon MobEffect::getIcon() {
    return m_icon;
}

double MobEffect::getDurationModifier() const {
    return m_durationModifier;
}

int MobEffect::getDescriptionId() {
    return m_descriptionId;
}

eMinecraftColour MobEffect::getColor() const {
    return m_color;
}
