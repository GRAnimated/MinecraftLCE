#pragma once

#include "net/minecraft/world/level/gamemode/rules/GameRuleDefinition.h"

class CompoundGameRuleDefinition : public GameRuleDefinition {
public:
    ~CompoundGameRuleDefinition() override;
    void getChildren(std::vector<GameRuleDefinition*>*) override;
    void getChildren(std::vector<GameRuleDefinition*>*, ConsoleGameRules::EGameRuleType) override;
    GameRuleDefinition* addChild(ConsoleGameRules::EGameRuleType) override;
    void populateGameRule(GameRulesInstance::EGameRulesInstanceType, GameRule*) override;
    bool onUseBlock(GameRule*, int, int, int, int) override;
    bool onCollectItem(GameRule*, not_null_ptr<ItemInstance>) override;
    void postProcessPlayer(std::__1::shared_ptr<Player>) override;
};
