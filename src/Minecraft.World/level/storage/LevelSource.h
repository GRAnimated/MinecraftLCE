#pragma once

#include "Minecraft.World/level/LightLayer.h"
#include <memory>

class BlockEntity;
class BlockState;
class BlockPos;
class Direction;
class Biome;
class BiomeSource;
class Block;

class LevelSource {
public:
    virtual std::shared_ptr<BlockEntity> getBlockEntity(BlockPos const&) = 0;
    virtual void getLightColor(BlockPos const&, int, int) = 0;
    virtual void getBrightness(LightLayer::variety, BlockPos const&) = 0;
    virtual void getBrightness(BlockPos const&, int) = 0;
    virtual void getBrightness(BlockPos const&) = 0;
    virtual const BlockState* getBlockState(BlockPos const&) = 0;
    virtual void getBlockId(int, int, int) = 0;
    virtual void getBlockData(int, int, int) = 0;
    virtual Block* getBlock(BlockPos const&) = 0;
    virtual bool isEmptyBlock(BlockPos const&) = 0;
    virtual Biome* getBiome(BlockPos const&) = 0;
    virtual BiomeSource* getBiomeSource() = 0;
    virtual void getMaxBuildHeight() = 0;
    virtual bool isAllEmpty() = 0;
    virtual void getDirectSignal(BlockPos const&, Direction const*) = 0;
    virtual void getGeneratorType() = 0;
    virtual ~LevelSource();
};