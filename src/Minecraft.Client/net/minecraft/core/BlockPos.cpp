#include "net/minecraft/core/BlockPos.h"

#include "net/minecraft/core/MutableBlockPos.h"

#include <cstdint>

#include "net/minecraft/core/Direction.h"
#include "net/minecraft/world/phys/Vec3.h"

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

BlockPos::BlockPos(int x, int y, int z) : Vec3i(x, y, z) {}

// name guessed
BlockPos::BlockPos(double x, double y, double z) : Vec3i(x, y, z) {}

BlockPos::BlockPos() : Vec3i(0, 0, 0) {}

BlockPos::BlockPos(Vec3* vec) : Vec3i(vec->m_x, vec->m_y, vec->m_z) {}

BlockPos::BlockPos(const Vec3i& vec) : Vec3i(vec.getX(), vec.getY(), vec.getZ()) {}

bool BlockPos::equals(const BlockPos& pos) const {
    return getX() == pos.getX() && getY() == pos.getY() && getZ() == pos.getZ();
}

bool BlockPos::equals(const BlockPos* pos) const {
    return equals(*pos);
}

// name guessed
bool BlockPos::operator!=(const BlockPos& pos) const {
    return !equals(pos);
}

// name guessed
BlockPos BlockPos::offset(double x, double y, double z) const {
    return BlockPos(getX() + x, getY() + y, getZ() + z);
}

/** The original static initializers derive 26 X/Z bits from the 30,000,000
 * world border, leaving 12 Y bits. Positions are packed X:Y:Z, high to low.
 */
// NON_MATCHING | score: 2615 (lower is better)
long long BlockPos::compressBlockPos() const {
    return (std::uint64_t(getX()) & 0x3ffffffULL) << 38 | (std::uint64_t(getY()) & 0xfffULL) << 26
           | (std::uint64_t(getZ()) & 0x3ffffffULL);
}

// NON_MATCHING | score: 3010 (lower is better)
BlockPos BlockPos::decompressBlockPos(long long value) {
    const std::uint64_t bits = static_cast<std::uint64_t>(value);
    const int x = static_cast<std::int64_t>(bits) >> 38;
    const int y = static_cast<std::int64_t>(bits << 26) >> 52;
    const int z = static_cast<std::int64_t>(bits << 38) >> 38;
    return BlockPos(x, y, z);
}

// name guessed
BlockPos BlockPos::offset(const Vec3i& delta) const {
    return offset(delta.getX(), delta.getY(), delta.getZ());
}
