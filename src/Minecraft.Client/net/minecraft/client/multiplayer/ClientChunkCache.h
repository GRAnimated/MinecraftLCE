#pragma once

#include "net/minecraft/world/level/chunk/ChunkPos.h"
#include "net/minecraft/world/level/chunk/ChunkSource.h"
#include "net/minecraft/world/level/chunk/EmptyLevelChunk.h"
#include "net/minecraft/world/level/chunk/WaterLevelChunk.h"
#include "net/minecraft/world/level/dimension/Dimension.h"

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

    EmptyLevelChunk* m_emptyChunk;
    WaterLevelChunk* m_waterChunk;

    void* unk1;
    void* unk2;

    ChunkPos m_chunkPos;

    void* unk3;
    int unk4;
    int unk45;
    void* unk5;
    void* unk6;
    void* unk7;
    void* unk8;
    void* unk9;
    void* unk10;
    void* unk11;
    void* unk12;
    void* unk13;
    void* unk14;
    char* unk15;
    void* unk16;
    void* unk17;
    void* unk18;
    void* unk19;
    void* unk20;
    void* unk21;
    nn::os::MutexType m_mutex;
    int m_xzSize2;
    int unk27;
    char* unk28;
    Level* m_level;
    Dimension* m_dimension;
};
