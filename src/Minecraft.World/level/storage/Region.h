#pragma once

#include "Minecraft.World/ArrayWithLength.h"
#include "Minecraft.World/level/storage/LevelSource.h"

class Level;
class LevelChunk;

class Region : public LevelSource {
public:
    Region(Level*, const BlockPos&, const BlockPos&, int);

    virtual std::shared_ptr<BlockEntity> getBlockEntity(const BlockPos&) override;
    virtual void getLightColor(const BlockPos&, int, int) override;
    virtual void getBrightness(LightLayer::variety, const BlockPos&) override;
    virtual void getBrightness(const BlockPos&, int) override;
    virtual void getBrightness(const BlockPos&) override;
    virtual const BlockState* getBlockState(const BlockPos&) override;
    virtual void getBlockId(int, int, int) override;
    virtual void getBlockData(int, int, int) override;
    virtual Block* getBlock(const BlockPos&) override;
    virtual bool isEmptyBlock(const BlockPos&) override;
    virtual Biome* getBiome(const BlockPos&) override;
    virtual BiomeSource* getBiomeSource() override;
    virtual void getMaxBuildHeight() override;
    virtual bool isAllEmpty() override;
    virtual void getDirectSignal(const BlockPos&, const Direction*) override;
    virtual void getGeneratorType() override;
    virtual ~Region();

    void setCachedBlocksAndData(unsigned char*, unsigned char*, int, int, int, const BlockState**);

    int x;
    int y;
    array2DWithLength<LevelChunk*>* chunks;
    Level* level;
    bool allEmpty;
    int dword_24;
    int dword_28;
    int dword_2c;
    void* field_30;
};