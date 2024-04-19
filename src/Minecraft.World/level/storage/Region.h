#pragma once

#include "Minecraft.World/ArrayWithLength.h"
#include "Minecraft.World/level/storage/LevelSource.h"

class Level;
class LevelChunk;

class Region : public LevelSource {
public:
    Region(Level*, BlockPos const&, BlockPos const&, int);

    virtual void getBlockEntity(BlockPos const&) override;
    virtual void getLightColor(BlockPos const&, int, int) override;
    virtual void getBrightness(LightLayer::variety, BlockPos const&) override;
    virtual void getBrightness(BlockPos const&, int) override;
    virtual void getBrightness(BlockPos const&) override;
    virtual void getBlockState(BlockPos const&) override;
    virtual void getBlockId(int, int, int) override;
    virtual void getBlockData(int, int, int) override;
    virtual void getBlock(BlockPos const&) override;
    virtual void isEmptyBlock(BlockPos const&) override;
    virtual void getBiome(BlockPos const&) override;
    virtual void getBiomeSource() override;
    virtual void getMaxBuildHeight() override;
    virtual void isAllEmpty() override;
    virtual void getDirectSignal(BlockPos const&, Direction const*) override;
    virtual void getGeneratorType() override;
    virtual ~Region();

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