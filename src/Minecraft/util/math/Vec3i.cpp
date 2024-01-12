#include "Vec3i.h"
#include "Mth.h"

Vec3i::Vec3i(int x, int y, int z) : x(x), y(y), z(z) {}

Vec3i::Vec3i(double x, double y, double z) {
    this->x = Mth::floor(x);
    this->y = Mth::floor(y);
    this->z = Mth::floor(z);
}
