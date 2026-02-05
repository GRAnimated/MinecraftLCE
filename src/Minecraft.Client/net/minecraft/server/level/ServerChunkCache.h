#pragma once

#include "net/minecraft/world/level/chunk/ChunkSource.h"
#include "nn/os/os_MutexTypes.h"
#include "types.h"
#include <deque>
#include <vector>

class ChunkGenerator;
class ChunkStorage;
class ServerLevel;
class Dimension;

/* NOTE:
 * Several functions in this class are quite different than Wii U Edition, with the inclusion of a
 * mUnloadedChunks array containing chunks that are likely to be reloaded.
 */
class ServerChunkCache : public ChunkSource {
public:
    ServerChunkCache(ServerLevel* level, ChunkStorage* storage, ChunkGenerator* generator);

    ~ServerChunkCache() override;
    LevelChunk* getChunkIfLoaded(int chunkX, int chunkZ) override;
    LevelChunk* getOrCreateChunk(int chunkX, int chunkZ, bool unk) override;
    void tick() override;
    std::wstring gatherStats() override;
    int getLoadedChunksCount() override;
    void flagPostProcessComplete(short unk, int chunkX, int chunkZ) override;
    bool isChunkGeneratedAt(int chunkX, int chunkZ) override;
    bool hasChunk(int chunkX, int chunkZ) override;
    LevelChunk* getChunk(int chunkX, int chunkZ) override;
    LevelChunk* getChunkAt(const BlockPos&) override;
    LevelChunk* getChunkLoadedOrUnloaded(int chunkX, int chunkZ) override;
    LevelChunk* create(int chunkX, int chunkZ) override;
    LevelChunk* create(int chunkX, int chunkZ, bool unk);
    bool saveAllEntities() override;
    bool save(bool, ProgressListener*) override;
    bool shouldSave() override;
    LevelChunk** getCache() override;
    std::vector<Biome::MobSpawnerData>* getMobsAt(MobCategory* category, const BlockPos& pos) override;
    BlockPos* findNearestMapFeature(Level* level, const std::wstring& name, const BlockPos& pos,
                                    bool unk) override;
    int getLoadedChunks() override;
    void recreateLogicStructuresForChunk(LevelChunk* chunk, int chunkX, int chunkZ) override;

    int inBounds(int chunkX, int chunkZ);
    int computeIdx(int chunkX, int chunkZ);
    LevelChunk* getChunkIfGenerated(int chunkX, int chunkZ, bool unk);
    LevelChunk* load(int chunkX, int chunkZ, LevelChunk* chunk);
    LevelChunk* updateCacheAndPostProcess(int chunkX, int chunkZ, LevelChunk* newChunk, LevelChunk* oldChunk,
                                          bool unk);
    std::vector<LevelChunk*>* getLoadedChunkList();
    void updatePostProcessFlag(short flag, int baseX, int baseZ, int offsetX, int offsetZ, LevelChunk* chunk);
    void updatePostProcessFlags(int chunkX, int chunkZ);
    LevelChunk* getChunkIfLoadedOrInvalid(int chunkX, int chunkZ);

    LevelChunk* mEmptyChunk;
    ChunkGenerator* mChunkGenerator;
    ChunkStorage* mChunkStorage;
    bool byte_28;
    LevelChunk** m_cache;
    std::vector<LevelChunk*> mChunkList;
    ServerLevel* mLevel;
    Dimension* mDimension;
    std::deque<LevelChunk*> mDeque;
    LevelChunk** mUnloadedChunks;
    nn::os::MutexType mMutex;
    int dword_b8;
    int dword_bc;
    bool (*mContainsChunkFunc)(Dimension*, int, int);
    Dimension* qword_c8;
};

ASSERT_SIZEOF(ServerChunkCache, 0xD0)
