#include "net/minecraft/core/BlockPos.h"
#include "net/minecraft/world/phys/Vec3.h"

BlockPos::BlockPos(int x, int y, int z) : Vec3i(x, y, z) {}

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

bool BlockPos::operator!=(const BlockPos& pos) const {
    return !equals(pos);
}

BlockPos BlockPos::offset(double x, double y, double z) const {
    return BlockPos(getX() + x, getY() + y, getZ() + z);
}
