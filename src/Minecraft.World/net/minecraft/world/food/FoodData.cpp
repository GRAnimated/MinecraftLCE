#include "net/minecraft/world/food/FoodData.h"

#include "net/minecraft/client/Minecraft.h"
#include "net/minecraft/world/Difficulty.h"
#include "net/minecraft/world/entity/player/Player.h"
#include "net/minecraft/world/food/FoodConstants.h"
#include "net/minecraft/world/level/GameRules.h"
#include "net/minecraft/world/level/Level.h"

FoodData::FoodData() {
    m_exhaustionLevel = 0;
    m_tickTimer = 0;
    m_foodLevel = FoodConstants::MaxFood();
    m_lastFoodLevel = FoodConstants::MaxFood();
    m_saturationLevel = FoodConstants::StartSaturation();
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

bool FoodData::needsFood() {
    return m_foodLevel < FoodConstants::MaxFood();
}

bool FoodData::isStarving() {
    return m_foodLevel <= FoodConstants::StarveLevel();
}

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
