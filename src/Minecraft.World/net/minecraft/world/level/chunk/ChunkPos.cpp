#include "net/minecraft/world/level/chunk/ChunkPos.h"

#include "net/minecraft/core/BlockPos.h"

long long ChunkPos::asLong(int x, int z) {
    return ((long long)x & 4294967295LL) | ((long long)z & 4294967295LL) << 32;
}

bool ChunkPos::eq_test(const ChunkPos& pos0, const ChunkPos& pos1) {
    return pos0.m_x == pos1.m_x && pos0.m_z == pos1.m_z;
}

ChunkPos::ChunkPos(int x, int z) {
    m_x = x;
    m_z = z;
}

ChunkPos::ChunkPos(const BlockPos& blockPos) {
    m_x = blockPos.getX() >> 4;
    m_z = blockPos.getZ() >> 4;
}

long long ChunkPos::toLong() const {
    return asLong(m_x, m_z);
}

double ChunkPos::distanceToSqr(double x, double z) {
    auto blockX = (double)(m_x * 16 + 8);
    auto blockZ = (double)(m_z * 16 + 8);

    double newX = blockX - x;
    double newZ = blockZ - z;

    return newX * newX + newZ * newZ;
}

int ChunkPos::getMiddleBlockX() {
    return (m_x << 4) + 8;
}

int ChunkPos::getMiddleBlockZ() {
    return (m_z << 4) + 8;
}

BlockPos ChunkPos::getMiddleBlockPosition(int y) {
    int x = getMiddleBlockX();
    int z = getMiddleBlockZ();

    return {x, y, z};
}

int ChunkPos::getMinBlockX() const {
    return m_x << 4;
}

int ChunkPos::getMinBlockZ() const {
    return m_z << 4;
}

int ChunkPos::getMaxBlockX() const {
    return (m_x << 4) + 15;
}

int ChunkPos::getMaxBlockZ() const {
    return (m_z << 4) + 15;
}

BlockPos ChunkPos::getWorldPosition() const {
    return {m_x << 4, 0, m_z << 4};
}
