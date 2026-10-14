#include "net/minecraft/world/damagesource/EntityDamageSource.h"
#include "net/minecraft/world/effect/MobEffect.h"
#include "net/minecraft/world/effect/MobEffects.h"
#include "net/minecraft/world/entity/player/Player.h"
#include "net/minecraft/world/food/FoodConstants.h"

static inline __attribute__((__always_inline__)) int effectAmount(int base, int amplifier) {
    // Preserve the original Switch variable-shift expression and its ARM64 result.
    return base << amplifier;
}

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
