#pragma once

#include "nn/os/os_MutexTypes.h"
#include "Minecraft.World/level/chunk/ChunkSource.h"
#include <vector>

class ChunkGenerator;
class ChunkStorage;
class ServerLevel;
class Dimension;

class ServerChunkCache : public ChunkSource {
public:
    ServerChunkCache(ServerLevel*, ChunkStorage*, ChunkGenerator*);

    ~ServerChunkCache() override;
    void getChunkIfLoaded(int, int) override;
    LevelChunk* getOrCreateChunk(int, int, bool) override;
    void tick() override;
    void gatherStats() override;
    void getLoadedChunksCount() override;
    void flagPostProcessComplete(short, int, int) override;
    void isChunkGeneratedAt(int, int) override;
    void hasChunk(int, int) override;
    void getChunk(int, int) override;
    void getChunkAt(const BlockPos&) override;
    void getChunkLoadedOrUnloaded(int, int) override;
    void create(int, int) override;
    void saveAllEntities() override;
    void save(bool, ProgressListener*) override;
    void shouldSave() override;
    ChunkSource* getCache() override;
    void getMobsAt(MobCategory*, const BlockPos&) override;
    void findNearestMapFeature(Level*, const std::wstring&, const BlockPos&, bool) override;
    void getLoadedChunks() override;
    void recreateLogicStructuresForChunk(LevelChunk*, int, int) override;

    LevelChunk* field_10;
    ChunkGenerator* field_18;
    ChunkStorage* field_20;
    bool byte_28;
    LevelChunk** field_30;
    std::vector<LevelChunk*> field_38;
    Level* field_50;
    Dimension* field_58;
    void* qword_60;
    void* qword_68;
    void* qword_70;
    void* qword_78;
    void* qword_80;
    void* qword_88;
    void* field_90;
    nn::os::MutexType field_98;
    int dword_b8;
    int dword_bc;
    void* qword_c0;
    void* qword_c8;
};
