#pragma once

#include <cstdio>

class BlockPos;

class ChunkPos {
public:
    int m_x;
    int m_z;

    static long long asLong(int x, int z);
    static bool eq_test(const ChunkPos& pos0, const ChunkPos& pos1);

    ChunkPos(int x, int z);
    explicit ChunkPos(const BlockPos& blockPos);

    long long toLong() const;
    double distanceToSqr(double x, double z);
    int getMiddleBlockX();
    int getMiddleBlockZ();
    BlockPos getMiddleBlockPosition(int y);
    int getMinBlockX() const;
    int getMinBlockZ() const;
    int getMaxBlockX() const;
    int getMaxBlockZ() const;
    BlockPos getWorldPosition() const;
};

struct ChunkPosKeyHash {
    std::size_t operator()(const ChunkPos& chunkPos) const { return chunkPos.toLong(); }
};

struct ChunkPosKeyEq {
    bool operator()(const ChunkPos& pos0, const ChunkPos& pos1) const {
        return ChunkPos::eq_test(pos0, pos1);
    }
};
