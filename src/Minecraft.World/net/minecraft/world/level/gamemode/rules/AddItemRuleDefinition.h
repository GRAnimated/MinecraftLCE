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

    int m_itemId;
    int m_quantity;
    int m_auxValue;
    int m_dataTag;
    int m_slot;
    std::vector<AddEnchantmentRuleDefinition*> m_addEnchantmentRules;
};
