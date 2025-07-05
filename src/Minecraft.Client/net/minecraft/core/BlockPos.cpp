#include "net/minecraft/core/BlockPos.h"
#include "net/minecraft/core/Direction.h"
#include "net/minecraft/world/phys/Vec3.h"

BlockPos::BlockPos(int x, int y, int z) : Vec3i(x, y, z) {}

BlockPos::BlockPos() : Vec3i(0, 0, 0) {}

BlockPos::BlockPos(Vec3* vec) : Vec3i(vec->x, vec->y, vec->z) {}

BlockPos::BlockPos(const Vec3i& vec) : Vec3i(vec.getX(), vec.getY(), vec.getZ()) {}

bool BlockPos::equals(const BlockPos& pos) const {
    return getX() == pos.getX() && getY() == pos.getY() && getZ() == pos.getZ();
}

bool BlockPos::equals(const BlockPos* pos) const {
    return equals(*pos);
}

BlockPos BlockPos::offset(int x, int y, int z) const {
    return BlockPos(getX() + x, getY() + y, getZ() + z);
}

BlockPos BlockPos::relative(const Direction* direction) const {
    return relative(direction, 1);
}

BlockPos BlockPos::relative(const Direction* direction, int amount) const {
    return BlockPos(getX() + direction->getX() * amount, getY() + direction->getY() * amount,
                    getZ() + direction->getZ() * amount);
}

BlockPos BlockPos::above() const {
    return above(1);
}

BlockPos BlockPos::above(int amount) const {
    return relative(Direction::UP, amount);
}

BlockPos BlockPos::below() const {
    return below(1);
}

BlockPos BlockPos::below(int amount) const {
    return relative(Direction::DOWN, amount);
}

BlockPos BlockPos::north() const {
    return north(1);
}

BlockPos BlockPos::north(int amount) const {
    return relative(Direction::NORTH, amount);
}

BlockPos BlockPos::south() const {
    return south(1);
}

BlockPos BlockPos::south(int amount) const {
    return relative(Direction::SOUTH, amount);
}

BlockPos BlockPos::west() const {
    return west(1);
}

BlockPos BlockPos::west(int amount) const {
    return relative(Direction::WEST, amount);
}

BlockPos BlockPos::east() const {
    return east(1);
}

BlockPos BlockPos::east(int amount) const {
    return relative(Direction::EAST, amount);
}

MutableBlockPos::MutableBlockPos(int x, int y, int z) : BlockPos(x, y, z) {};
