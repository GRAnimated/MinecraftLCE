#include "net/minecraft/world/level/chunk/ChunkPos.h"

#include "net/minecraft/core/BlockPos.h"

long long ChunkPos::asLong(int x, int z) {
    return ((long long)x & 4294967295LL) | ((long long)z & 4294967295LL) << 32;
}

bool ChunkPos::eq_test(const ChunkPos& pos0, const ChunkPos& pos1) {
    return pos0.mX == pos1.mX && pos0.mZ == pos1.mZ;
}

ChunkPos::ChunkPos(int x, int z) {
    mX = x;
    mZ = z;
}

ChunkPos::ChunkPos(const BlockPos& blockPos) {
    mX = blockPos.getX() >> 4;
    mZ = blockPos.getZ() >> 4;
}

long long ChunkPos::toLong() const {
    return asLong(mX, mZ);
}

double ChunkPos::distanceToSqr(double x, double z) {
    auto blockX = (double)(mX * 16 + 8);
    auto blockZ = (double)(mZ * 16 + 8);

    double newX = blockX - x;
    double newZ = blockZ - z;

    return newX * newX + newZ * newZ;
}

int ChunkPos::getMiddleBlockX() {
    return (mX << 4) + 8;
}

int ChunkPos::getMiddleBlockZ() {
    return (mZ << 4) + 8;
}

BlockPos ChunkPos::getMiddleBlockPosition(int y) {
    int x = getMiddleBlockX();
    int z = getMiddleBlockZ();

    return {x, y, z};
}

int ChunkPos::getMinBlockX() const {
    return mX << 4;
}

int ChunkPos::getMinBlockZ() const {
    return mZ << 4;
}

int ChunkPos::getMaxBlockX() const {
    return (mX << 4) + 15;
}

int ChunkPos::getMaxBlockZ() const {
    return (mZ << 4) + 15;
}

BlockPos ChunkPos::getWorldPosition() const {
    return {mX << 4, 0, mZ << 4};
}
