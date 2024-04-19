#pragma once

#include "Minecraft.World/level/levelgen/ChunkGenerator.h"

class Random;

class NetherFlatLevelSource : public ChunkGenerator {
public:
    NetherFlatLevelSource(Level*, bool, long long);
    virtual ~NetherFlatLevelSource();
    virtual void createChunk(int, int) override;
    virtual void postProcess(int, int) override;
    virtual void postProcessLoadedChunk(LevelChunk*, int, int) override;
    virtual void getMobsAt(MobCategory*, BlockPos const&) override;
    virtual void findNearestMapFeature(Level*, std::wstring const&, BlockPos const&, bool) override;
    virtual void recreateLogicStructuresForChunk(LevelChunk*, int, int) override;
    virtual void isPosInFeature(Level*, std::wstring const&, BlockPos const&) override;
    virtual void lightChunk(LevelChunk*) override;

    int field_8;
    int size;
    long long seed;
    Random* random;
    bool isGenerateMapFeatures;
    Level* level;
};