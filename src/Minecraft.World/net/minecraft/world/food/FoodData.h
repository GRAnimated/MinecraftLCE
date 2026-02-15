#pragma once

#include "com/mojang/nbt/CompoundTag.h"
#include "net/minecraft/world/item/FoodItem.h"
#include "net/minecraft/world/item/ItemInstance.h"

class Player;

class FoodData {
public:
    FoodData();

    int m_foodLevel;
    float m_saturationLevel;
    float m_exhaustionLevel;
    int m_tickTimer;
    int m_lastFoodLevel;

    void eat(int, float);
    void eat(FoodItem*, const not_null_ptr<ItemInstance>&);
    void addExhaustion(float exhaustionLevel);
    void tick(const std::shared_ptr<Player>& player);
    void readAdditionalSaveData(CompoundTag* tag);
    void addAdditionalSaveData(CompoundTag* tag);
    int getFoodLevel();
    int getLastFoodLevel();
    bool needsFood();
    bool isStarving();
    float getSaturationLevel();
    void setFoodLevel(int foodLevel);
    void setSaturation(float saturationLevel);
    void setExhaustion(float exhaustionLevel);
};
