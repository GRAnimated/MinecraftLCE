#pragma once

#include <string>

class BlockPos;
class LevelChunk;
class Level;
class MobCategory;
class ProgressListener;

class ChunkSource {
public:
    virtual ~ChunkSource();
    virtual void getChunkIfLoaded(int, int) = 0;
    virtual LevelChunk* getOrCreateChunk(int, int, bool) = 0;
    virtual void tick() = 0;
    virtual void gatherStats() = 0;
    virtual void getLoadedChunksCount() = 0;
    virtual void flagPostProcessComplete(short, int, int);
    virtual void isChunkGeneratedAt(int, int);
    virtual void hasChunk(int, int) = 0;
    virtual void reallyHasChunk(int, int);
    virtual void getChunk(int, int) = 0;
    virtual void getChunkAt(const BlockPos&) = 0;
    virtual void getChunkLoadedOrUnloaded(int, int);
    virtual void lightChunk(LevelChunk*);
    virtual void create(int, int) = 0;
    virtual void saveAllEntities();
    virtual void save(bool, ProgressListener*) = 0;
    virtual void shouldSave() = 0;
    virtual ChunkSource* getCache();
    virtual void dataReceived(int, int);
    virtual void getMobsAt(MobCategory*, const BlockPos&) = 0;
    virtual void findNearestMapFeature(Level*, const std::wstring&, const BlockPos&, bool) = 0;
    virtual void getLoadedChunks() = 0;
    virtual void recreateLogicStructuresForChunk(LevelChunk*, int, int) = 0;

    int mXZSize;
};
