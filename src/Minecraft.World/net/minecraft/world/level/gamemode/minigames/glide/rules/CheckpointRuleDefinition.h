#pragma once

#include "net/minecraft/world/level/gamemode/rules/NamedAreaRuleDefinition.h"

class ServerLevel;

class CheckpointRuleDefinition : NamedAreaRuleDefinition {
public:
    void processBeacons(ServerLevel*);
};
