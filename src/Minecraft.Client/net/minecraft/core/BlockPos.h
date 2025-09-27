#pragma once

#include "net/minecraft/core/Vec3i.h"
#include "types.h"
#include <memory>

class Direction;
class Entity;
class Vec3;
class BlockPosIterator;

class BlockPos : public Vec3i {
public:
    static BlockPos zero;

    BlockPos(int x, int y, int z);
    BlockPos();
    BlockPos(const std::shared_ptr<Entity>&);
    BlockPos(Vec3*);
    BlockPos(const Vec3i&);
    BlockPos(double x, double y, double z);

    static BlockPosIterator* between(const BlockPos&, const BlockPos&);

    bool equals(const BlockPos& pos) const;
    bool equals(const BlockPos* pos) const;

    BlockPos offset(int x, int y, int z) const;

    BlockPos relative(const Direction*) const;
    BlockPos relative(const Direction*, int) const;

    BlockPos above() const;
    BlockPos above(int) const;
    BlockPos below() const;
    BlockPos below(int) const;
    BlockPos north() const;
    BlockPos north(int) const;
    BlockPos south() const;
    BlockPos south(int) const;
    BlockPos west() const;
    BlockPos west(int) const;
    BlockPos east() const;
    BlockPos east(int) const;

    long long compressBlockPos() const;
    void decompressBlockPos(long long);
};

ASSERT_SIZEOF(BlockPos, 0xC)
