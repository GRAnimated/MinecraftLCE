#include "Minecraft.Core/BlockPos.h"
#include "Minecraft.Core/Direction.h"
#include "Minecraft.World/phys/Vec3.h"

BlockPos::BlockPos(int x, int y, int z) : mArr(Vec3i(x, y, z)) {}

BlockPos::BlockPos() : mArr(Vec3i(0, 0, 0)) {}

BlockPos::BlockPos(Vec3* vec) : mArr(Vec3i(vec->x, vec->y, vec->z)) {}

BlockPos::BlockPos(Vec3i const& vec) : mArr(Vec3i(vec.getX(), vec.getY(), vec.getZ())) {}

bool BlockPos::equals(BlockPos const& pos) const {
    return mArr.getX() == pos.mArr.getX() && mArr.getY() == pos.mArr.getY() && mArr.getZ() == pos.mArr.getZ();
}

bool BlockPos::equals(BlockPos const* pos) const {
    return equals(*pos);
}

BlockPos BlockPos::offset(int x, int y, int z) const {
    return BlockPos(mArr.getX() + x, mArr.getY() + y, mArr.getZ() + z);
}

BlockPos BlockPos::relative(Direction const* direction) const {
    return relative(direction, 1);
}

BlockPos BlockPos::relative(Direction const* direction, int amount) const {
    return BlockPos(mArr.getX() + direction->getX() * amount, mArr.getY() + direction->getY() * amount, mArr.getZ() + direction->getZ() * amount);
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
