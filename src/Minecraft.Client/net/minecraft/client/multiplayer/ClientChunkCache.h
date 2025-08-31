#pragma once

#include "net/minecraft/world/level/chunk/ChunkSource.h"

class ChunkStorage;

class ClientChunkCache : public ChunkSource {
public:
    ClientChunkCache(Level*);
    ClientChunkCache(Level*, ChunkStorage*);

    ~ClientChunkCache() override;
    LevelChunk* getChunkIfLoaded(int, int) override;
    LevelChunk* getOrCreateChunk(int, int, bool) override;
    void tick() override;
    std::wstring gatherStats() override;
    int getLoadedChunksCount() override;
    bool isChunkGeneratedAt(int, int) override;
    bool hasChunk(int, int) override;
    LevelChunk* getChunk(int, int) override;
    LevelChunk* getChunkAt(const BlockPos&) override;
    LevelChunk* create(int, int) override;
    void save(bool, ProgressListener*) override;
    bool shouldSave() override;
    ChunkSource* getCache() override;
    std::vector<Biome::MobSpawnerData>* getMobsAt(MobCategory*, const BlockPos&) override;
    void findNearestMapFeature(Level*, const std::wstring&, const BlockPos&, bool) override;
    int getLoadedChunks() override;
    void recreateLogicStructuresForChunk(LevelChunk*, int, int) override;

private:
    char size[0x110 - sizeof(ChunkSource)];
};
