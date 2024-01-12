#pragma once

#include "Minecraft/util/math/Vec3i.h"

class Direction;
class Vec3;

class BlockPos {
public:
    BlockPos(int x, int y, int z);
    BlockPos() = default;
    BlockPos(Vec3*);
    static BlockPos* relative(Direction const*, int);
    static BlockPos* create(int x, int y, int z);

    static BlockPos* above();
    static BlockPos* above(int);
    static BlockPos* below();
    static BlockPos* below(int);
    static BlockPos* north();
    static BlockPos* north(int);
    static BlockPos* south();
    static BlockPos* south(int);
    static BlockPos* west();
    static BlockPos* west(int);
    static BlockPos* east();
    static BlockPos* east(int);

    Vec3i mArr = Vec3i(0, 0 ,0);
};