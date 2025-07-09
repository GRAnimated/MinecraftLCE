#include "net/minecraft/world/effect/MobEffectInstance.h"

#include "net/minecraft/client/Minecraft.h"
#include "net/minecraft/world/level/gamemode/minigames/MiniGameDef.h"

MobEffectInstance::MobEffectInstance(MobEffectInstance* instance) {}

MobEffectInstance::MobEffectInstance(MobEffect* effect) {
    init(mEffect, 0, 0, true);
}

MobEffectInstance::MobEffectInstance(MobEffect* effect, int duration) {
    init(mEffect, mDuration, 0, true);
}

MobEffectInstance::MobEffectInstance(MobEffect*, int duration, int amplifier) {
    init(mEffect, mDuration, mAmplifier, true);
}

MobEffectInstance::MobEffectInstance(MobEffect*, int duration, int amplifier, bool ambient, bool showParticles) {
    init(mEffect, mDuration, mAmplifier, showParticles);
    mAmbient = ambient;
}

void MobEffectInstance::init(MobEffect* effect, int duration, int amplifier, bool showParticles) {
    mParticles = showParticles;
    mEffect = effect;
    mDuration = duration;
    mAmplifier = amplifier;
    bool10 = false;
    mAmbient = false;
    mNoCounter = false;
    dword14 = -1;
}

void MobEffectInstance::update(MobEffectInstance* instance) {}

void MobEffectInstance::tickDownDuration() {}

void MobEffectInstance::tick(std::shared_ptr<LivingEntity> entity) {}

void MobEffectInstance::setNoCounter(bool noCounter) {}

void MobEffectInstance::save(CompoundTag* tag) {
    tag->putByte(L"Id", MobEffect::getId(mEffect));
    tag->putByte(L"Amplifier", getAmplifier());
    tag->putInt(L"Duration", getDuration());
    tag->putBoolean(L"Ambient", isAmbient());
    tag->putBoolean(L"ShowParticles", isVisible());
}

bool MobEffectInstance::isVisible() {
    return mParticles;
}

bool MobEffectInstance::isNoCounter() {
    return mNoCounter;
}

bool MobEffectInstance::isAmbient() {
    return mAmbient;
}

MobEffect* MobEffectInstance::getEffect() {
    return mEffect;
}

int MobEffectInstance::getDuration() {
    if (dword14 == -1) {
        return mDuration;
    }
    Minecraft* minecraft = Minecraft::GetInstance();
    MiniGameDef* miniGame = minecraft->GetMiniGame();
    return miniGame->getPotionDuration();
}

int MobEffectInstance::getDescriptionId() {
    return mEffect->getDescriptionId();
}

int MobEffectInstance::getAmplifier() {
    return mAmplifier;
}

bool MobEffectInstance::compareTo(MobEffectInstance* instance) {
    return false;
}

void MobEffectInstance::applyEffect(std::shared_ptr<LivingEntity> entity) {}
