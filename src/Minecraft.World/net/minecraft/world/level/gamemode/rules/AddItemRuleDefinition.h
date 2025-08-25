#pragma once

#include "net/minecraft/world/level/gamemode/rules/GameRuleDefinition.h"

class AddEnchantmentRuleDefinition;

class AddItemRuleDefinition : public GameRuleDefinition {
public:
    AddItemRuleDefinition();

    ~AddItemRuleDefinition() override;
    ConsoleGameRules::EGameRuleType getActionType() override;
    void getChildren(std::vector<GameRuleDefinition*>*) override;
    GameRuleDefinition* addChild(ConsoleGameRules::EGameRuleType) override;

    int mItemId;
    int mQuantity;
    int mAuxValue;
    int mDataTag;
    int mSlot;
    std::vector<AddEnchantmentRuleDefinition*> mAddEnchantmentRules;
};
