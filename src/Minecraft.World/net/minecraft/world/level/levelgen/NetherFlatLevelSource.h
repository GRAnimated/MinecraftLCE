#pragma once

#include "net/minecraft/world/level/chunk/ChunkGenerator.h"

class Random;
class ChunkPrimer;

class NetherFlatLevelSource : public ChunkGenerator {
public:
    NetherFlatLevelSource(Level*, bool, long long);
    virtual ~NetherFlatLevelSource();
    LevelChunk* createChunk(int, int) override;
    void postProcess(int, int) override;
    bool postProcessLoadedChunk(LevelChunk*, int, int) override;
    void getMobsAt(MobCategory*, const BlockPos&) override;
    void* findNearestMapFeature(Level*, const std::wstring&, const BlockPos&, bool) override;
    void recreateLogicStructuresForChunk(LevelChunk*, int, int) override;
    bool isPosInFeature(Level*, const std::wstring&, const BlockPos&) override;
    void lightChunk(LevelChunk*) override;
    void prepareHeights(int, int, ChunkPrimer*);
    void buildSurfaces(int, int, ChunkPrimer*);

    int field_8;
    int mSize;
    Random* mSeed;
    Random* mRandom;
    bool mIsGenerateMapFeatures;
    Level* mLevel;
};
