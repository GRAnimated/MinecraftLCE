#pragma once

#include <string>

class LevelChunk;
class MobCategory;
class BlockPos;
class Level;

class ChunkGenerator {
public:
    ChunkGenerator();
    virtual ~ChunkGenerator();
    virtual LevelChunk* createChunk(int, int) = 0;
    virtual void postProcess(int, int) = 0;
    virtual bool postProcessLoadedChunk(LevelChunk*, int, int) = 0;
    virtual void getMobsAt(MobCategory*, BlockPos const&) = 0;
    virtual void* findNearestMapFeature(Level*, std::wstring const&, BlockPos const&, bool) = 0;
    virtual void recreateLogicStructuresForChunk(LevelChunk*, int, int) = 0;
    virtual bool isPosInFeature(Level*, std::wstring const&, BlockPos const&) = 0;
    virtual void lightChunk(LevelChunk*);

    static bool inPostProcessStep;
};
