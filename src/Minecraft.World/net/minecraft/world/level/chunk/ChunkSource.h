#pragma once

#include <string>

#include "net/minecraft/world/level/biome/Biome.h"

class BlockPos;
class LevelChunk;
class Level;
class MobCategory;
class ProgressListener;

class ChunkSource {
public:
    virtual ~ChunkSource() {}
    virtual LevelChunk* getChunkIfLoaded(int x, int z) = 0;
    virtual LevelChunk* getOrCreateChunk(int x, int z, bool) = 0;
    virtual void tick() = 0;
    virtual std::wstring gatherStats() = 0;
    virtual int getLoadedChunksCount() = 0;
    virtual void flagPostProcessComplete(short, int, int);
    virtual bool isChunkGeneratedAt(int x, int z);
    virtual bool hasChunk(int x, int z) = 0;
    virtual bool reallyHasChunk(int x, int z);
    virtual LevelChunk* getChunk(int x, int z) = 0;
    virtual LevelChunk* getChunkAt(const BlockPos&) = 0;
    virtual LevelChunk* getChunkLoadedOrUnloaded(int x, int z);
    virtual void lightChunk(LevelChunk*);
    virtual LevelChunk* create(int x, int z) = 0;
    virtual bool saveAllEntities();
    virtual bool save(bool, ProgressListener*) = 0;
    virtual bool shouldSave() = 0;
    virtual LevelChunk** getCache();
    virtual void dataReceived(int, int);
    virtual std::vector<Biome::MobSpawnerData>* getMobsAt(MobCategory *category, const BlockPos &pos) = 0;
    virtual BlockPos *findNearestMapFeature(Level*, const std::wstring&, const BlockPos&, bool) = 0;
    virtual int getLoadedChunks() = 0;
    virtual void recreateLogicStructuresForChunk(LevelChunk*, int, int) = 0;

    int m_xzSize;
};
