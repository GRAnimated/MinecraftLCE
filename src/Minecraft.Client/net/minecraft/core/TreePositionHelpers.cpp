#include "net/minecraft/core/Direction.h"
#include "net/minecraft/core/MutableBlockPos.h"

BlockPos BlockPos::offset(const Vec3i& delta) const {
    return offset(delta.getX(), delta.getY(), delta.getZ());
}

Vec3i Vec3i::multiply(int amount) const {
    return Vec3i(getX() * amount, getY() * amount, getZ() * amount);
}

Vec3i Direction::getNormal() const {
    return *m_pos;
}

MutableBlockPos* MutableBlockPos::set(const Vec3i& pos) {
    m_x = pos.getX();
    m_y = pos.getY();
    m_z = pos.getZ();
    return this;
}

MutableBlockPos* MutableBlockPos::move(const Direction* direction, int amount) {
    return set(static_cast<const Vec3i&>(BlockPos(*this).offset(direction->getNormal().multiply(amount))));
}
