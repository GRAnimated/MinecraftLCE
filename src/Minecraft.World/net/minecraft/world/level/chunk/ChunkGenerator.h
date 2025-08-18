#pragma once

#include <string>

class LevelChunk;
class MobCategory;
class BlockPos;
class Level;

class ChunkGenerator {
public:
    ChunkGenerator() {}
    virtual ~ChunkGenerator();
    virtual LevelChunk* createChunk(int, int) = 0;
    virtual void postProcess(int, int) = 0;
    virtual bool postProcessLoadedChunk(LevelChunk*, int, int) = 0;
    virtual void getMobsAt(MobCategory*, const BlockPos&) = 0;
    virtual void* findNearestMapFeature(Level*, const std::wstring&, const BlockPos&, bool) = 0;
    virtual void recreateLogicStructuresForChunk(LevelChunk*, int, int) = 0;
    virtual bool isPosInFeature(Level*, const std::wstring&, const BlockPos&) = 0;
    virtual void lightChunk(LevelChunk*);

    static bool inPostProcessStep;

    bool mIsClassicMoat;
    bool mIsSmallMoat;
    bool mIsMediumMoat;
    bool mIsLargeMoat;
    int mXZSize2;
};
