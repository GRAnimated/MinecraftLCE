#pragma once

#include "NX/Thread/C4JThreadImpl.h"
#include "net/minecraft/world/level/chunk/ChunkPos.h"
#include "net/minecraft/world/level/chunk/ChunkSource.h"
#include "net/minecraft/world/level/chunk/EmptyLevelChunk.h"
#include "net/minecraft/world/level/chunk/WaterLevelChunk.h"
#include "net/minecraft/world/level/dimension/Dimension.h"

class ChunkStorage;

class ClientChunkCache : public ChunkSource {
public:
    ClientChunkCache(Level* lvl);
    ClientChunkCache(Level* lvl, ChunkStorage* storage);

    void MultiPlayerChunkCacheInit(Level* lvl, ChunkStorage* storage);

    ~ClientChunkCache() override;

    /** Returns a pointer to a loaded chunk at a given location, if one doesn't exist, returns m_waterChunk,
     * if m_waterChunk doesn't exist, returns m_chunkStorage(?!?!?!?) */
    LevelChunk* getChunkIfLoaded(int x, int z) override;
    LevelChunk* getOrCreateChunk(int x, int z, bool) override;
    void tick() override;
    std::wstring gatherStats() override;
    int getLoadedChunksCount() override;
    bool isChunkGeneratedAt(int x, int z) override;
    bool hasChunk(int x, int z) override;
    bool reallyHasChunk(int x, int z) override;
    LevelChunk* getChunk(int x, int z) override;
    LevelChunk* getChunkAt(const BlockPos& pos) override;
    LevelChunk* create(int x, int z) override;
    bool save(bool, ProgressListener*) override;
    bool shouldSave() override;
    LevelChunk** getCache() override;  // TODO this might have been implemented in the header due to it's
                                       // appearance being elsewhere in memory
    void dataReceived(int, int) override;
    std::vector<Biome::MobSpawnerData>* getMobsAt(MobCategory* category, const BlockPos& pos) override;
    BlockPos* findNearestMapFeature(Level*, const std::wstring&, const BlockPos&, bool) override;
    int getLoadedChunks() override;
    void recreateLogicStructuresForChunk(LevelChunk*, int, int) override;

    int inBounds(int x, int z);
    int computeIdx(int x, int z);

    static int StorageThreadProc(void*);

    EmptyLevelChunk* m_emptyChunk;
    WaterLevelChunk* m_waterChunk;

    ChunkStorage* m_chunkStorage;
    C4JThreadImpl* m_storageThread;

    ChunkPos m_chunkPos;

    void* unk3;
    int unk4;
    int unk45;
    nn::os::MutexType m_storageMutex;
    unsigned long long m_loadedChunksSize2;
    unsigned long long m_loadedChunksSize1;
    void* unk11;
    void* unk12;
    void* unk13;
    void* unk14;
    LevelChunk** m_cache;  // no clue if type is correct, just went off of vibes lmao
    void* unk16;
    void* unk17;
    void* unk18;
    void* unk19;
    void* unk20;
    void* unk21;
    nn::os::MutexType m_mutex;
    int m_xzBounds;
    int m_xzCenter;
    char* unk28;
    Level* m_level;
    Dimension* m_dimension;
};
