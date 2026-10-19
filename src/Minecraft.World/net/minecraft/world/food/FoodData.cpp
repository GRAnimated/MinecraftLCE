#include "net/minecraft/world/food/FoodData.h"

#include "net/minecraft/client/Minecraft.h"
#include "net/minecraft/world/Difficulty.h"
#include "net/minecraft/world/damagesource/DamageSource.h"
#include "net/minecraft/world/entity/player/Player.h"
#include "net/minecraft/world/food/FoodConstants.h"
#include "net/minecraft/world/level/GameRules.h"
#include "net/minecraft/world/level/Level.h"
#include "net/minecraft/world/level/gamemode/minigames/EMiniGameId.h"
#include <algorithm>

FoodData::FoodData() {
    m_exhaustionLevel = 0;
    m_tickTimer = 0;
    m_foodLevel = FoodConstants::MaxFood();
    m_lastFoodLevel = FoodConstants::MaxFood();
    m_saturationLevel = FoodConstants::StartSaturation();
}

void FoodData::eat(int nutrition, float saturationModifier) {
    m_foodLevel = std::min(m_foodLevel + nutrition, FoodConstants::MaxFood());
    m_saturationLevel
        = std::min(m_saturationLevel + static_cast<float>(nutrition) * saturationModifier * 2.0f,
                   static_cast<float>(m_foodLevel));
}

void FoodData::eat(FoodItem* food, const not_null_ptr<ItemInstance>& item) {
    // Both temporary owners survive through eat; each virtual receives its own copy.
    eat(food->getNutrition(not_null_ptr<ItemInstance>(item)),
        food->getSaturationModifier(not_null_ptr<ItemInstance>(item)));
}

// name guessed
void FoodData::addExhaustion(float exhaustion) {
    m_exhaustionLevel = std::min(m_exhaustionLevel + exhaustion, FoodConstants::MaxSaturation() * 2.0f);
}

// name guessed
void FoodData::tick(const std::shared_ptr<Player>& player) {
    const Difficulty* difficulty = player->m_level->getDifficulty();
    m_lastFoodLevel = m_foodLevel;

    if (m_exhaustionLevel > FoodConstants::ExhaustionDrop()) {
        m_exhaustionLevel -= FoodConstants::ExhaustionDrop();
        if (m_saturationLevel > 0.0f) {
            m_saturationLevel = std::max(m_saturationLevel - 1.0f, 0.0f);
        } else if (difficulty != Difficulty::PEACEFUL) {
            m_foodLevel = std::max(m_foodLevel - 1, 0);
        }
    }

    bool naturalRegeneration = player->m_level->getGameRules()->getBoolean(7);
    bool legacyFoodHealing = player->usesLegacyFoodHealing();
    if (naturalRegeneration && legacyFoodHealing) {
        // This mode retains the timer when food is absent or health is already full.
        if (m_foodLevel > 0 && player->isHurt()) {
            ++m_tickTimer;
            if (m_tickTimer >= FoodConstants::HealthTickCount()) {
                player->heal(1.0f);
                --m_foodLevel;
                m_tickTimer = 0;
            }
        }
    } else if (!Minecraft::InMiniGame(EMiniGameId::NORMAL_WORLD, true) && naturalRegeneration
               && m_saturationLevel > 0.0f && player->isHurt() && m_foodLevel >= FoodConstants::MaxFood()) {
        ++m_tickTimer;
        if (m_tickTimer >= FoodConstants::HealthTickCountSaturated()) {
            float saturation = std::min(m_saturationLevel, FoodConstants::SprintLevel());
            player->heal(saturation / FoodConstants::SprintLevel());
            addExhaustion(saturation);
            m_tickTimer = 0;
        }
    } else if (player->m_level->getGameRules()->getBoolean(7) && m_foodLevel >= FoodConstants::HealLevel()
               && player->isHurt()) {
        ++m_tickTimer;
        if (m_tickTimer >= FoodConstants::HealthTickCount()) {
            player->heal(1.0f);
            addExhaustion(FoodConstants::SprintLevel());
            m_tickTimer = 0;
        }
    } else if (m_foodLevel <= FoodConstants::StarveLevel()) {
        ++m_tickTimer;
        if (m_tickTimer >= FoodConstants::HealthTickCount()) {
            if ((player->getHealth() > 10.0f || difficulty == Difficulty::HARD
                 || (player->getHealth() > 1.0f
                     && (difficulty == Difficulty::NORMAL || difficulty == Difficulty::HARD)))
                && !Minecraft::InMiniGame(EMiniGameId::GLIDE, true)) {
                player->hurt(DamageSource::STARVE, 1.0f);
            }
            m_tickTimer = 0;
        }
    } else {
        m_tickTimer = 0;
    }
}

void FoodData::readAdditionalSaveData(CompoundTag* tag) {
    if (tag->contains(L"foodLevel", 99)) {
        m_foodLevel = tag->getInt(L"foodLevel");
        m_tickTimer = tag->getInt(L"foodTickTimer");
        m_saturationLevel = tag->getFloat(L"foodSaturationLevel");
        m_exhaustionLevel = tag->getFloat(L"foodExhaustionLevel");
    }
}

void FoodData::addAdditionalSaveData(CompoundTag* tag) {
    tag->putInt(L"foodLevel", m_foodLevel);
    tag->putInt(L"foodTickTimer", m_tickTimer);
    tag->putFloat(L"foodSaturationLevel", m_saturationLevel);
    tag->putFloat(L"foodExhaustionLevel", m_exhaustionLevel);
}

int FoodData::getFoodLevel() {
    return m_foodLevel;
}

int FoodData::getLastFoodLevel() {
    return m_lastFoodLevel;
}

// name guessed
bool FoodData::needsFood() {
    return m_foodLevel < FoodConstants::MaxFood();
}

bool FoodData::isStarving() {
    return m_foodLevel <= FoodConstants::StarveLevel();
}

// name guessed
float FoodData::getSaturationLevel() {
    return m_saturationLevel;
}

void FoodData::setFoodLevel(int foodLevel) {
    m_foodLevel = foodLevel;
}

void FoodData::setSaturation(float saturationLevel) {
    m_saturationLevel = saturationLevel;
}

void FoodData::setExhaustion(float exhaustionLevel) {
    m_exhaustionLevel = exhaustionLevel;
}
