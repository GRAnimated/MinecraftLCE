#pragma once

#include "net/minecraft/world/Random.h"
#include "net/minecraft/world/level/gamemode/rules/AddItemRuleDefinition.h"
#include "net/minecraft/world/level/gamemode/rules/GameRuleDefinition.h"
#include "net/minecraft/world/level/gamemode/rules/NamedAreaRuleDefinition.h"

class PowerupRuleDefinition : public NamedAreaRuleDefinition {
public:
    PowerupRuleDefinition();

    ~PowerupRuleDefinition() override;
    ConsoleGameRules::EGameRuleType getActionType() override;
    void getChildren(std::vector<GameRuleDefinition*>*) override;
    GameRuleDefinition* addChild(ConsoleGameRules::EGameRuleType) override;

    std::vector<AddItemRuleDefinition*> mAddItemRules;
    Random mRandom = Random();
};
