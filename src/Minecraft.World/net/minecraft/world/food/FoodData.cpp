#include "net/minecraft/world/food/FoodData.h"

#include "net/minecraft/client/Minecraft.h"
#include "net/minecraft/world/Difficulty.h"
#include "net/minecraft/world/level/GameRules.h"
#include "net/minecraft/world/level/Level.h"
#include "net/minecraft/world/entity/player/Player.h"
#include "net/minecraft/world/food/FoodConstants.h"

FoodData::FoodData() {
    mExhaustionLevel = 0;
    mTickTimer = 0;
    mFoodLevel = FoodConstants::MaxFood();
    mLastFoodLevel = FoodConstants::MaxFood();
    mSaturationLevel = FoodConstants::StartSaturation();
}

void FoodData::readAdditionalSaveData(CompoundTag* tag) {
    if (tag->contains(L"foodLevel", 99)) {
        mFoodLevel = tag->getInt(L"foodLevel");
        mTickTimer = tag->getInt(L"foodTickTimer");
        mSaturationLevel = tag->getFloat(L"foodSaturationLevel");
        mExhaustionLevel = tag->getFloat(L"foodExhaustionLevel");
    }
}

void FoodData::addAdditionalSaveData(CompoundTag* tag) {
    tag->putInt(L"foodLevel", mFoodLevel);
    tag->putInt(L"foodTickTimer", mTickTimer);
    tag->putFloat(L"foodSaturationLevel", mSaturationLevel);
    tag->putFloat(L"foodExhaustionLevel", mExhaustionLevel);
}

int FoodData::getFoodLevel() {
    return mFoodLevel;
}

int FoodData::getLastFoodLevel() {
    return mLastFoodLevel;
}

bool FoodData::needsFood() {
    return mFoodLevel < FoodConstants::MaxFood();
}

bool FoodData::isStarving() {
    return mFoodLevel <= FoodConstants::StarveLevel();
}

float FoodData::getSaturationLevel() {
    return mSaturationLevel;
}

void FoodData::setFoodLevel(int foodLevel) {
    mFoodLevel = foodLevel;
}

void FoodData::setSaturation(float saturationLevel) {
    mSaturationLevel = saturationLevel;
}

void FoodData::setExhaustion(float exhaustionLevel) {
    mExhaustionLevel = exhaustionLevel;
}
