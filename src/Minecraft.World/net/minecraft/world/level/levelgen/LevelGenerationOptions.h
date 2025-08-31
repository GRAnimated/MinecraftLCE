#pragma once

#include "net/minecraft/world/level/LevelRuleset.h"

class LevelGenerationOptions {
public:
    LevelRuleset* getRequiredGameRules();
    void loadBaseSaveData();
};
