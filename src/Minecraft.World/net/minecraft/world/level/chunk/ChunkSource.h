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
    virtual LevelChunk* getChunkIfLoaded(int, int) = 0;
    virtual LevelChunk* getOrCreateChunk(int, int, bool) = 0;
    virtual void tick() = 0;
    virtual std::wstring gatherStats() = 0;
    virtual int getLoadedChunksCount() = 0;
    virtual void flagPostProcessComplete(short, int, int);
    virtual bool isChunkGeneratedAt(int, int);
    virtual bool hasChunk(int, int) = 0;
    virtual bool reallyHasChunk(int, int);
    virtual LevelChunk* getChunk(int, int) = 0;
    virtual LevelChunk* getChunkAt(const BlockPos&) = 0;
    virtual LevelChunk* getChunkLoadedOrUnloaded(int, int);
    virtual void lightChunk(LevelChunk*);
    virtual LevelChunk* create(int, int) = 0;
    virtual bool saveAllEntities();
    virtual void save(bool, ProgressListener*) = 0;
    virtual bool shouldSave() = 0;
    virtual ChunkSource* getCache();
    virtual void dataReceived(int, int);
    virtual std::vector<Biome::MobSpawnerData>* getMobsAt(MobCategory*, const BlockPos&) = 0;
    virtual void findNearestMapFeature(Level*, const std::wstring&, const BlockPos&, bool) = 0;
    virtual int getLoadedChunks() = 0;
    virtual void recreateLogicStructuresForChunk(LevelChunk*, int, int) = 0;

    int m_xzSize;
};
