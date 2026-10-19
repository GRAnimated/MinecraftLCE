#include "net/minecraft/world/effect/MobEffect.h"

#include "net/minecraft/world/entity/ai/attributes/AttributeModifier.h"

#include "net/minecraft/world/entity/ai/attributes/AttributeInstance.h"
#include "net/minecraft/world/entity/ai/attributes/BaseAttributeMap.h"

#include "net/minecraft/world/damagesource/EntityDamageSource.h"
#include "net/minecraft/world/entity/player/Player.h"
#include "net/minecraft/world/food/FoodConstants.h"

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

static inline __attribute__((__always_inline__)) int effectAmount(int base, int amplifier) {
    // ARM64 masks the variable shift count.
    return base << amplifier;
}

// name guessed
// NON_MATCHING | score: 986 (lower is better)
void MobEffect::applyEffectTick(const std::shared_ptr<LivingEntity>& entity, int amplifier) {
    if (this == MobEffects::REGENERATION) {
        if (entity->getHealth() < entity->getMaxHealth()) {
            entity->heal(1.0f);
        }
    } else if (this == MobEffects::POISON) {
        if (entity->getHealth() > 1.0f) {
            entity->hurt(DamageSource::POISON, 1.0f);
        }
    } else if (this == MobEffects::WITHER) {
        entity->hurt(DamageSource::WITHER, 1.0f);
    } else if (this == MobEffects::HUNGER && entity->isType(ePlayer)) {
        std::shared_ptr<Player> player = std::dynamic_pointer_cast<Player>(entity);
        const float exhaustion = FoodConstants::ExhaustionMine();
        player->causeFoodExhaustion(static_cast<int>(static_cast<unsigned int>(amplifier) + 1) * exhaustion);
    } else if (this == MobEffects::SATURATION && entity->isType(ePlayer)) {
        if (!entity->m_level->m_isLocal) {
            std::shared_ptr<Player> player = std::dynamic_pointer_cast<Player>(entity);
            player->getFoodData()->eat(static_cast<int>(static_cast<unsigned int>(amplifier) + 1), 1.0f);
        }
    } else if ((this == MobEffects::INSTANT_HEALTH && !entity->isInvertedHealAndHarm())
               || (this == MobEffects::INSTANT_DAMAGE && entity->isInvertedHealAndHarm())) {
        const int amount = effectAmount(4, amplifier);
        entity->heal(static_cast<float>(amount < 0 ? 0 : amount));
    } else if ((this == MobEffects::INSTANT_DAMAGE && !entity->isInvertedHealAndHarm())
               || (this == MobEffects::INSTANT_HEALTH && entity->isInvertedHealAndHarm())) {
        entity->hurt(DamageSource::INSTANT_MAGIC, static_cast<float>(effectAmount(6, amplifier)));
    }
}

// name guessed
void MobEffect::applyInstantenousEffect(const std::shared_ptr<Entity>& source,
                                        const std::shared_ptr<Entity>& indirectSource,
                                        const std::shared_ptr<LivingEntity>& target, int amplifier,
                                        double proximity) {
    if ((this == MobEffects::INSTANT_HEALTH && !target->isInvertedHealAndHarm())
        || (this == MobEffects::INSTANT_DAMAGE && target->isInvertedHealAndHarm())) {
        const float amount = static_cast<float>(effectAmount(4, amplifier) * proximity + 0.5);
        target->heal(amount);
    } else if ((this == MobEffects::INSTANT_DAMAGE && !target->isInvertedHealAndHarm())
               || (this == MobEffects::INSTANT_HEALTH && target->isInvertedHealAndHarm())) {
        const float amount = static_cast<float>(effectAmount(6, amplifier) * proximity + 0.5);
        if (!source) {
            target->hurt(DamageSource::MAGIC, amount);
        } else {
            EntityDamageSource* damage
                = DamageSource::CreateIndirectMagic(source, indirectSource, DamageSource::INSTANT_MAGIC);
            target->hurt(damage, amount);
            delete damage;
        }
    }
}

MobEffect* MobEffect::addAttributeModifier(Attribute* attribute, eMODIFIER_ID id, double amount,
                                           int operation) {
    AttributeModifier* modifier = new AttributeModifier(static_cast<eATTRIBUTE_ID>(id), amount, operation);
    m_attributeModifiers.insert(std::make_pair(attribute, modifier));
    return this;
}

// name guessed
void MobEffect::removeAttributeModifiers(const std::shared_ptr<LivingEntity>&, BaseAttributeMap* attributes,
                                         int) {
    for (const auto& entry : m_attributeModifiers) {
        AttributeInstance* instance = attributes->getInstance(entry.first);
        if (instance != nullptr)
            instance->removeModifier(entry.second);
    }
}

// name guessed
void MobEffect::addAttributeModifiers(const std::shared_ptr<LivingEntity>&, BaseAttributeMap* attributes,
                                      int amplifier) {
    for (const auto& entry : m_attributeModifiers) {
        AttributeInstance* instance = attributes->getInstance(entry.first);
        if (instance != nullptr) {
            AttributeModifier* modifier = entry.second;
            instance->removeModifier(modifier);
            instance->addModifier(new AttributeModifier(
                modifier->getId(), getAttributeModifierValue(amplifier, modifier), modifier->getOperation()));
        }
    }
}

MappedRegistry<ResourceLocation, MobEffect*>* MobEffect::REGISTRY;  // name guessed
int MobEffect::EFFECT_COUNT;

// name guessed
MobEffect* MobEffect::byId(int id) {
    return REGISTRY->byId(id);
}

// name guessed
int MobEffect::getId(MobEffect* effect) {
    return REGISTRY->getId(effect);
}

// name guessed
int MobEffect::GetEffectCount() {
    return EFFECT_COUNT;
}

std::unordered_map<Attribute*, AttributeModifier*>& MobEffect::getAttributeModifiers() {
    return m_attributeModifiers;
}

double MobEffect::getAttributeModifierValue(int amplifier, AttributeModifier* modifier) {
    double amount = modifier->getAmount();
    return static_cast<int>(static_cast<unsigned int>(amplifier) + 1) * amount;
}
