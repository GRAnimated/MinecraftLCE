#include "net/minecraft/world/effect/MobEffectInstance.h"

#include "com/mojang/nbt/CompoundTag.h"
#include "net/minecraft/client/Minecraft.h"
#include "net/minecraft/client/color/ColourTable.h"
#include "net/minecraft/world/effect/MobEffect.h"
#include "net/minecraft/world/level/gamemode/minigames/MiniGameDef.h"
#include "net/minecraft/world/level/material/MaterialColor.h"

MobEffectInstance::MobEffectInstance(MobEffectInstance* other) {
    m_effect = other->m_effect;
    m_duration = other->m_duration;
    m_amplifier = other->m_amplifier;
    m_bool10 = other->m_bool10;
    m_ambient = other->m_ambient;
    m_particles = other->m_particles;
    m_noCounter = other->m_noCounter;
    m_dword14 = other->get_14();
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
    m_ambient = ambient;
}

void MobEffectInstance::init(MobEffect* effect, int duration, int amplifier, bool showParticles) {
    m_particles = showParticles;
    m_effect = effect;
    m_duration = duration;
    m_amplifier = amplifier;
    m_bool10 = false;
    m_ambient = false;
    m_noCounter = false;
    m_dword14 = -1;
}

void MobEffectInstance::update(MobEffectInstance* other) {
    if (other->m_amplifier > m_amplifier) {
        m_amplifier = other->m_amplifier;
        m_duration = other->m_duration;
    } else if (other->m_amplifier == m_amplifier && (m_duration < other->m_duration)) {
        m_duration = other->m_duration;
    } else if (other->m_ambient == false && m_ambient == true) {
        m_ambient = false;
    }
    m_particles = other->m_particles;
}

int MobEffectInstance::tickDownDuration() {
    return --m_duration;
}

bool MobEffectInstance::tick(std::shared_ptr<LivingEntity> entity) {
    getDuration();  // unused call

    if (m_duration < 1) {
        return m_duration > 0;
    }

    if (m_effect->isDurationEffectTick(m_duration, m_amplifier)) {
        applyEffect(entity);
    }

    tickDownDuration();
    return m_duration > 0;
}

void MobEffectInstance::setNoCounter(bool noCounter) {
    m_noCounter = noCounter;
}

CompoundTag* MobEffectInstance::save(CompoundTag* tag) {
    tag->putByte(L"Id", MobEffect::getId(m_effect));
    tag->putByte(L"Amplifier", getAmplifier());
    tag->putInt(L"Duration", getDuration());
    tag->putBoolean(L"Ambient", isAmbient());
    tag->putBoolean(L"ShowParticles", isVisible());
    return tag;
}

bool MobEffectInstance::isVisible() {
    return m_particles;
}

bool MobEffectInstance::isNoCounter() {
    return m_noCounter;
}

bool MobEffectInstance::isAmbient() {
    return m_ambient;
}

MobEffect* MobEffectInstance::getEffect() {
    return m_effect;
}

int MobEffectInstance::getDuration() {
    if (m_dword14 == -1) {
        return m_duration;
    }
    Minecraft* minecraft = Minecraft::GetInstance();
    MiniGameDef* miniGame = minecraft->GetMiniGame();
    return miniGame->getPotionDuration(m_dword14, m_duration);
}

int MobEffectInstance::getDescriptionId() {
    return m_effect->getDescriptionId();
}

int MobEffectInstance::getAmplifier() {
    return m_amplifier;
}

/* unused
bool MobEffectInstance::compareTo(MobEffectInstance* other) {
    return false;
} */

void MobEffectInstance::applyEffect(const std::shared_ptr<LivingEntity>& entity) {
    if (m_duration > 0) {
        m_effect->applyEffectTick(entity, m_amplifier);
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
