#include "net/minecraft/core/Vec3i.h"
#include "net/minecraft/util/Mth.h"

Vec3i::Vec3i(int x, int y, int z) {
    this->x = x;
    this->y = y;
    this->z = z;
}

Vec3i::Vec3i(double x, double y, double z) {
    this->x = Mth::floor(x);
    this->y = Mth::floor(y);
    this->z = Mth::floor(z);
}

int Vec3i::getX() const {
    return x;
}

int Vec3i::getY() const {
    return y;
}

int Vec3i::getZ() const {
    return z;
}
