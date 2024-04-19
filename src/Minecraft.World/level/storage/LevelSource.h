#pragma once

class BlockPos;
class LightLayer {
public:
    enum variety {};
};
class Direction;

class LevelSource {
public:
    virtual void getBlockEntity(BlockPos const&) = 0;
    virtual void getLightColor(BlockPos const&, int, int) = 0;
    virtual void getBrightness(LightLayer::variety, BlockPos const&) = 0;
    virtual void getBrightness(BlockPos const&, int) = 0;
    virtual void getBrightness(BlockPos const&) = 0;
    virtual void getBlockState(BlockPos const&) = 0;
    virtual void getBlockId(int, int, int) = 0;
    virtual void getBlockData(int, int, int) = 0;
    virtual void getBlock(BlockPos const&) = 0;
    virtual void isEmptyBlock(BlockPos const&) = 0;
    virtual void getBiome(BlockPos const&) = 0;
    virtual void getBiomeSource() = 0;
    virtual void getMaxBuildHeight() = 0;
    virtual void isAllEmpty() = 0;
    virtual void getDirectSignal(BlockPos const&, Direction const*) = 0;
    virtual void getGeneratorType() = 0;
    virtual ~LevelSource();
};