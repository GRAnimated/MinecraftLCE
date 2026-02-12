#pragma once

#include "net/minecraft/world/ArrayWithLength.h"
#include "net/minecraft/world/level/storage/LevelSource.h"

class Level;
class LevelChunk;

class Region : public LevelSource {
public:
    Region(Level*, const BlockPos&, const BlockPos&, int);

    std::shared_ptr<BlockEntity> getBlockEntity(const BlockPos&) override;
    int getLightColor(const BlockPos&, int, int) override;
    int getBrightness(LightLayer::variety, const BlockPos&) override;
    float getBrightness(const BlockPos&, int) override;
    float getBrightness(const BlockPos&) override;
    const BlockState* getBlockState(const BlockPos&) override;
    int getBlockId(int, int, int) override;
    int getBlockData(int, int, int) override;
    Block* getBlock(const BlockPos&) override;
    bool isEmptyBlock(const BlockPos&) override;
    Biome* getBiome(const BlockPos&) override;
    BiomeSource* getBiomeSource() override;
    int getMaxBuildHeight() override;
    bool isAllEmpty() override;
    int getDirectSignal(const BlockPos&, const Direction*) override;
    LevelType* getGeneratorType() override;
    virtual ~Region();

    void setCachedBlocksAndData(unsigned char*, unsigned char*, int, int, int, const BlockState**);

    int m_x;
    int m_y;
    array2DWithLength<LevelChunk*>* m_chunks;
    Level* m_level;
    bool m_allEmpty;
    int m_dword24;
    int m_dword28;
    int m_dword2c;
    void* m_field30;
};
