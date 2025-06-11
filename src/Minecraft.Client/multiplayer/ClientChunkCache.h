#pragma once

#include "Minecraft.World/level/chunk/ChunkSource.h"

class ChunkStorage;

class ClientChunkCache : public ChunkSource {
public:
    ClientChunkCache(Level*);
    ClientChunkCache(Level*, ChunkStorage*);

    ~ClientChunkCache() override;
    void getChunkIfLoaded(int, int) override;
    LevelChunk* getOrCreateChunk(int, int, bool) override;
    void tick() override;
    void gatherStats() override;
    void getLoadedChunksCount() override;
    void isChunkGeneratedAt(int, int) override;
    void hasChunk(int, int) override;
    void getChunk(int, int) override;
    void getChunkAt(const BlockPos&) override;
    void create(int, int) override;
    void save(bool, ProgressListener*) override;
    void shouldSave() override;
    ChunkSource* getCache() override;
    void getMobsAt(MobCategory*, const BlockPos&) override;
    void findNearestMapFeature(Level*, const std::wstring&, const BlockPos&, bool) override;
    void getLoadedChunks() override;
    void recreateLogicStructuresForChunk(LevelChunk*, int, int) override;

private:
    char size[0x110 - sizeof(ChunkSource)];
};
