#pragma once

#include "Minecraft.World/level/levelgen/ChunkGenerator.h"

class Random;
class ChunkPrimer;

class NetherFlatLevelSource : public ChunkGenerator {
public:
    NetherFlatLevelSource(Level*, bool, long long);
    virtual ~NetherFlatLevelSource();
    virtual LevelChunk* createChunk(int, int) override;
    virtual void postProcess(int, int) override;
    virtual bool postProcessLoadedChunk(LevelChunk*, int, int) override;
    virtual void getMobsAt(MobCategory*, BlockPos const&) override;
    virtual void* findNearestMapFeature(Level*, std::wstring const&, BlockPos const&, bool) override;
    virtual void recreateLogicStructuresForChunk(LevelChunk*, int, int) override;
    virtual bool isPosInFeature(Level*, std::wstring const&, BlockPos const&) override;
    virtual void lightChunk(LevelChunk*) override;
    void prepareHeights(int, int, ChunkPrimer*);
    void buildSurfaces(int, int, ChunkPrimer*);

    int field_8;
    int mSize;
    Random* mSeed;
    Random* mRandom;
    bool mIsGenerateMapFeatures;
    Level* mLevel;
};