#include "net/minecraft/world/effect/MobEffectInstance.h"

#include "com/mojang/nbt/CompoundTag.h"
#include "net/minecraft/client/Minecraft.h"
#include "net/minecraft/client/color/ColourTable.h"
#include "net/minecraft/world/effect/MobEffect.h"
#include "net/minecraft/world/level/gamemode/minigames/MiniGameDef.h"
#include "net/minecraft/world/level/material/MaterialColor.h"

MobEffectInstance::MobEffectInstance(MobEffectInstance* other) {
    mEffect = other->mEffect;
    mDuration = other->mDuration;
    mAmplifier = other->mAmplifier;
    bool10 = other->bool10;
    mAmbient = other->mAmbient;
    mParticles = other->mParticles;
    mNoCounter = other->mNoCounter;
    dword14 = other->get_14();
}

MobEffectInstance::MobEffectInstance(MobEffect* effect) {
    init(effect, 0, 0, true);
}

MobEffectInstance::MobEffectInstance(MobEffect* effect, int duration) {
    init(effect, duration, 0, true);
}

MobEffectInstance::MobEffectInstance(MobEffect* effect, int duration, int amplifier) {
    init(effect, duration, amplifier, true);
}

MobEffectInstance::MobEffectInstance(MobEffect* effect, int duration, int amplifier, bool ambient,
                                     bool showParticles) {
    init(effect, duration, amplifier, showParticles);
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

void MobEffectInstance::update(MobEffectInstance* other) {
    if (other->mAmplifier > mAmplifier) {
        mAmplifier = other->mAmplifier;
        mDuration = other->mDuration;
    } else if (other->mAmplifier == mAmplifier && (mDuration < other->mDuration)) {
        mDuration = other->mDuration;
    } else if (other->mAmbient == false && mAmbient == true) {
        mAmbient = false;
    }
    mParticles = other->mParticles;
}

int MobEffectInstance::tickDownDuration() {
    return --mDuration;
}

bool MobEffectInstance::tick(std::shared_ptr<LivingEntity> entity) {
    getDuration();  // unused call

    if (mDuration < 1) {
        return mDuration > 0;
    }

    if (mEffect->isDurationEffectTick(mDuration, mAmplifier)) {
        applyEffect(entity);
    }

    tickDownDuration();
    return mDuration > 0;
}

void MobEffectInstance::setNoCounter(bool noCounter) {
    mNoCounter = noCounter;
}

CompoundTag* MobEffectInstance::save(CompoundTag* tag) {
    tag->putByte(L"Id", MobEffect::getId(mEffect));
    tag->putByte(L"Amplifier", getAmplifier());
    tag->putInt(L"Duration", getDuration());
    tag->putBoolean(L"Ambient", isAmbient());
    tag->putBoolean(L"ShowParticles", isVisible());
    return tag;
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
    return miniGame->getPotionDuration(dword14, mDuration);
}

int MobEffectInstance::getDescriptionId() {
    return mEffect->getDescriptionId();
}

int MobEffectInstance::getAmplifier() {
    return mAmplifier;
}

/* unused
bool MobEffectInstance::compareTo(MobEffectInstance* other) {
    return false;
} */

void MobEffectInstance::applyEffect(const std::shared_ptr<LivingEntity>& entity) {
    if (mDuration > 0) {
        mEffect->applyEffectTick(entity, mAmplifier);
    }
}

// NON_MATCHING: Placement of a couple instructions are different
int MobEffectInstance::getColorValue(const std::vector<MobEffectInstance*>* instance) {
    if (instance->empty()) {
        return 0x385DC6;
    }

    int totalColor = 0;
    int count = 0;

    for (int i = 0; i < instance->size(); i++) {
        MobEffectInstance* effectInstance = instance->at(i);
        if (effectInstance->isVisible()) {
            MobEffect* effect = effectInstance->getEffect();
            if (effect) {
                for (int j = -1; j < effectInstance->getAmplifier(); count++) {
                    ColourTable* colourTable = Minecraft::GetInstance()->getColourTable();
                    eMinecraftColour color = effect->getColor();
                    totalColor += colourTable->getColour(color);
                    j++;
                }
            }
        }
    }
    if (count > 0)
        return totalColor / count;

    return totalColor;
}

MobEffectInstance* MobEffectInstance::load(CompoundTag* tag) {
    int id = tag->getByte(L"Id");
    MobEffect* effect = MobEffect::byId(id);
    if (!effect) {
        return nullptr;
    }

    int amplifier = tag->getByte(L"Amplifier");
    int duration = tag->getInt(L"Duration");
    bool ambient = tag->getBoolean(L"Ambient");
    bool showParticles = true;
    if (tag->contains(L"ShowParticles", 1)) {
        showParticles = tag->getBoolean(L"ShowParticles");
    }

    return new MobEffectInstance(effect, duration, amplifier < 0 ? 0 : amplifier, ambient, showParticles);
}
