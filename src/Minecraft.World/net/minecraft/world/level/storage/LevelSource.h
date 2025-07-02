#pragma once

#include "net/minecraft/world/level/LightLayer.h"
#include <memory>

class BlockEntity;
class BlockState;
class BlockPos;
class Direction;
class Biome;
class BiomeSource;
class LevelType;
class Block;

class LevelSource {
public:
    LevelSource() = default;

    virtual std::shared_ptr<BlockEntity> getBlockEntity(const BlockPos&) = 0;
    virtual int getLightColor(const BlockPos&, int, int) = 0;
    virtual int getBrightness(LightLayer::variety, const BlockPos&) = 0;
    virtual float getBrightness(const BlockPos&, int) = 0;
    virtual float getBrightness(const BlockPos&) = 0;
    virtual const BlockState* getBlockState(const BlockPos&) = 0;
    virtual int getBlockId(int, int, int) = 0;
    virtual int getBlockData(int, int, int) = 0;
    virtual Block* getBlock(const BlockPos&) = 0;
    virtual bool isEmptyBlock(const BlockPos&) = 0;
    virtual Biome* getBiome(const BlockPos&) = 0;
    virtual BiomeSource* getBiomeSource() = 0;
    virtual int getMaxBuildHeight() = 0;
    virtual bool isAllEmpty() = 0;
    virtual int getDirectSignal(const BlockPos&, const Direction*) = 0;
    virtual LevelType* getGeneratorType() = 0;
    virtual ~LevelSource();
};