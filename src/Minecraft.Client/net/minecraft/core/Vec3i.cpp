#include "net/minecraft/core/Vec3i.h"
#include "net/minecraft/util/Mth.h"

Vec3i::Vec3i(int x, int y, int z) {
    this->m_x = x;
    this->m_y = y;
    this->m_z = z;
}

Vec3i::Vec3i(double x, double y, double z) {
    this->m_x = Mth::floor(x);
    this->m_y = Mth::floor(y);
    this->m_z = Mth::floor(z);
}

int Vec3i::getX() const {
    return m_x;
}

int Vec3i::getY() const {
    return m_y;
}

int Vec3i::getZ() const {
    return m_z;
}
