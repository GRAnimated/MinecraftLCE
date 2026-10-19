#include "net/minecraft/core/MutableBlockPos.h"

#include "net/minecraft/core/Direction.h"

// name guessed
MutableBlockPos::MutableBlockPos() : BlockPos(0, 0, 0) {}

MutableBlockPos::MutableBlockPos(int x, int y, int z) : BlockPos(x, y, z) {}

// name guessed
MutableBlockPos* MutableBlockPos::set(const Vec3i& pos) {
    m_x = pos.getX();
    m_y = pos.getY();
    m_z = pos.getZ();
    return this;
}

// name guessed
MutableBlockPos* MutableBlockPos::move(const Direction* direction, int amount) {
    return set(static_cast<const Vec3i&>(BlockPos(*this).offset(direction->getNormal().multiply(amount))));
}
