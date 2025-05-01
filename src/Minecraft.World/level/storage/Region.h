#pragma once

#include "Minecraft.World/ArrayWithLength.h"
#include "Minecraft.World/level/storage/LevelSource.h"

class Level;
class LevelChunk;

class Region : public LevelSource {
public:
    Region(Level*, BlockPos const&, BlockPos const&, int);

    virtual std::shared_ptr<BlockEntity> getBlockEntity(BlockPos const&) override;
    virtual void getLightColor(BlockPos const&, int, int) override;
    virtual void getBrightness(LightLayer::variety, BlockPos const&) override;
    virtual void getBrightness(BlockPos const&, int) override;
    virtual void getBrightness(BlockPos const&) override;
    virtual const BlockState* getBlockState(BlockPos const&) override;
    virtual void getBlockId(int, int, int) override;
    virtual void getBlockData(int, int, int) override;
    virtual Block* getBlock(BlockPos const&) override;
    virtual bool isEmptyBlock(BlockPos const&) override;
    virtual Biome* getBiome(BlockPos const&) override;
    virtual BiomeSource* getBiomeSource() override;
    virtual void getMaxBuildHeight() override;
    virtual bool isAllEmpty() override;
    virtual void getDirectSignal(BlockPos const&, Direction const*) override;
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