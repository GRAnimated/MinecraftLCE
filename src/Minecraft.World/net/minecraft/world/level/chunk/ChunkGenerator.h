#pragma once

#include "net/minecraft/world/level/biome/Biome.h"

#include <string>

class LevelChunk;
class MobCategory;
class BlockPos;
class Level;

class ChunkGenerator {
public:
    static const std::wstring STRONGHOLD_NAME;
    static const std::wstring MANSION_NAME;
    static const std::wstring MONUMENT_NAME;
    static const std::wstring VILLAGE_NAME;
    static const std::wstring MINESHAFT_NAME;
    static const std::wstring TEMPLE_NAME;

    ChunkGenerator() {}
    virtual ~ChunkGenerator();
    virtual LevelChunk* createChunk(int, int) = 0;
    virtual void postProcess(int, int) = 0;
    virtual bool postProcessLoadedChunk(LevelChunk*, int, int) = 0;
    virtual std::vector<Biome::MobSpawnerData>* getMobsAt(MobCategory*, const BlockPos&) = 0;
    virtual BlockPos* findNearestMapFeature(Level*, const std::wstring&, const BlockPos&, bool) = 0;
    virtual void recreateLogicStructuresForChunk(LevelChunk*, int, int) = 0;
    virtual bool isPosInFeature(Level*, const std::wstring&, const BlockPos&) = 0;
    virtual void lightChunk(LevelChunk*);

    static bool inPostProcessStep;

    bool mIsClassicMoat;
    bool mIsSmallMoat;
    bool mIsMediumMoat;
    bool mIsLargeMoat;
    int mSize;
};
