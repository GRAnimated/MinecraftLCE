#pragma once

#include "net/minecraft/world/level/LevelRuleset.h"
#include "net/minecraft/world/level/biome/Biome.h"

class BlockPos;

class LevelGenerationOptions {
public:
    LevelRuleset* getRequiredGameRules();
    void loadBaseSaveData();
    bool intersects(const BlockPos& lower, const BlockPos& upper);
    /** LegacyBlockData is the reconstruction's existing name for original BlockPair.
     */
    void getBiomeOverride(int biomeId, Biome::LegacyBlockData* filler, Biome::LegacyBlockData* surface);
};
