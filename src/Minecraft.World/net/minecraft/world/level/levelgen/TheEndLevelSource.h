#pragma once

#include "net/minecraft/world/level/chunk/ChunkGenerator.h"

class TheEndLevelSource : public ChunkGenerator {
public:
    TheEndLevelSource(Level*, bool, long long, const BlockPos&);
    virtual ~TheEndLevelSource();
    LevelChunk* createChunk(int, int) override;
    void postProcess(int, int) override;
    bool postProcessLoadedChunk(LevelChunk*, int, int) override;
    std::vector<Biome::MobSpawnerData>* getMobsAt(MobCategory*, const BlockPos&) override;
    BlockPos* findNearestMapFeature(Level*, const std::wstring&, const BlockPos&, bool) override;
    void recreateLogicStructuresForChunk(LevelChunk*, int, int) override;
    bool isPosInFeature(Level*, const std::wstring&, const BlockPos&) override;
};
