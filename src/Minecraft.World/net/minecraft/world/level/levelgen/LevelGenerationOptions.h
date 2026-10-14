#pragma once

#include "net/minecraft/world/level/LevelRuleset.h"

class BlockPos;

class LevelGenerationOptions {
public:
    LevelRuleset* getRequiredGameRules();
    void loadBaseSaveData();
    bool intersects(const BlockPos& lower, const BlockPos& upper);
};
