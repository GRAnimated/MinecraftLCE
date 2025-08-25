#pragma once

#include "net/minecraft/world/level/gamemode/rules/CompoundGameRuleDefinition.h"

class OnInitialiseWorld : public CompoundGameRuleDefinition {
    ConsoleGameRules::EGameRuleType getActionType() override;
};
