#pragma once

#include "net/minecraft/world/level/gamemode/ConsoleGameRules.h"
#include "net/minecraft/world/phys/AABB.h"
#include <string>
#include <vector>

class TargetAreaRuleDefinition;
class ThermalAreaRuleDefinition;
class StringTable;
class PowerupRuleDefinition;
class CheckpointRuleDefinition;
class NamedAreaRuleDefinition;
class GameRuleDefinition;

class LevelRuleset {
protected:
    unsigned char padding[343];
    StringTable* stringTable;

public:
    void getNamedAreas(int type, std::vector<AABB>* out);
    void getActiveChunkAreas(std::vector<AABB>* out);
    void getRingsWithinArea(std::vector<TargetAreaRuleDefinition*>* out, AABB* aabb);
    StringTable* getStringTable();
    void getThermalAreas(std::vector<ThermalAreaRuleDefinition*>* out);
    void getPowerups(std::vector<PowerupRuleDefinition*>* out);
    void getTargetAreas(std::vector<TargetAreaRuleDefinition*>* out);
    const AABB* getNamedArea(const std::wstring& areaName);
    std::vector<CheckpointRuleDefinition*>* getCheckpoints();
    void getPlayerBoundsVolumes(std::vector<NamedAreaRuleDefinition*>* out);
    GameRuleDefinition* getRuleByType(ConsoleGameRules::EGameRuleType);
};
