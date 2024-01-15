#pragma once

#include <memory>
#include "Minecraft/util/math/Vec3i.h"

class Direction;
class Entity;
class Vec3;

class BlockPos {
public:
    BlockPos(int x, int y, int z);
    BlockPos();
    BlockPos(std::shared_ptr<Entity> const&);
    BlockPos(Vec3*);
    BlockPos(Vec3i const&);
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

    Vec3i mArr;
};