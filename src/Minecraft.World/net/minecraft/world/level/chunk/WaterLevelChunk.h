#pragma once

#include "net/minecraft/world/level/chunk/LevelChunk.h"

class WaterLevelChunk : public LevelChunk {
public:
    void reSyncLighting() override;
    void dropLighting() override;
    void recalcBlockLights() override;
    void recalcHeightmapOnly() override;
    void recalcHeightmap() override;
    void lightLava() override;
    bool setData(int, int, int, int, int, bool*) override;
    const BlockState *setBlock(const BlockPos&, const BlockState*) override;
    bool setBlockAndData(int, int, int, int, int, bool) override;
    void setBrightness(LightLayer::variety, const BlockPos&, int) override;
    void addEntity(std::shared_ptr<Entity>) override;
    void removeEntity(std::shared_ptr<Entity>) override;
    void removeEntity(std::shared_ptr<Entity>, int) override;
    void getBlockEntity(const BlockPos&, LevelChunk::EntityCreationType) override;
    void addBlockEntity(std::shared_ptr<BlockEntity>) override;
    void setBlockEntity(const BlockPos&, std::shared_ptr<BlockEntity>) override;
    void removeBlockEntity(const BlockPos&) override;
    void load(bool) override;
    void unload(bool, bool) override;
    bool containsPlayer() override;
    void markUnsaved() override;
    void getEntities(std::shared_ptr<Entity>, AABB const*, std::vector<std::shared_ptr<Entity>>&, const Predicate<std::shared_ptr<Entity>>*) override;
    void getEntitiesOfClass(const std::type_info&, AABB const*, std::vector<std::shared_ptr<Entity>>&, const Predicate<std::shared_ptr<Entity>>*, bool) override;
    int countEntities() override;
    bool shouldSave(bool) override;
    void setBlocksAndData(arrayWithLength<unsigned char>, int, int, int, int, int, int, int, bool) override;
    void testSetBlocksAndData(arrayWithLength<unsigned char>, int, int, int, int, int, int, int) override;
    void getRandom(long long) override;
    Biome* getBiome(const BlockPos&, BiomeSource*) override;
};
