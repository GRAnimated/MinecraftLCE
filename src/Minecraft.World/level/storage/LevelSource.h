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
    virtual std::shared_ptr<BlockEntity> getBlockEntity(const BlockPos&) = 0;
    virtual void getLightColor(const BlockPos&, int, int) = 0;
    virtual void getBrightness(LightLayer::variety, const BlockPos&) = 0;
    virtual void getBrightness(const BlockPos&, int) = 0;
    virtual void getBrightness(const BlockPos&) = 0;
    virtual const BlockState* getBlockState(const BlockPos&) = 0;
    virtual void getBlockId(int, int, int) = 0;
    virtual void getBlockData(int, int, int) = 0;
    virtual Block* getBlock(const BlockPos&) = 0;
    virtual bool isEmptyBlock(const BlockPos&) = 0;
    virtual Biome* getBiome(const BlockPos&) = 0;
    virtual BiomeSource* getBiomeSource() = 0;
    virtual void getMaxBuildHeight() = 0;
    virtual bool isAllEmpty() = 0;
    virtual void getDirectSignal(const BlockPos&, const Direction*) = 0;
    virtual void getGeneratorType() = 0;
    virtual ~LevelSource();
};