#include "net/minecraft/world/phys/AABB.h"

#include "net/minecraft/util/ThreadStorage.h"

DEFINE_THREAD_STORAGE(AABB, 1024)

Vec3* AABB::getCenter() const {
    return Vec3::newTemp(this->min.x + (this->max.x - this->min.x) * 0.5,
                         this->min.y + (this->max.y - this->min.y) * 0.5,
                         this->min.z + (this->max.z - this->min.z) * 0.5);
}

double AABB::getSize() const {
    double sizeX = this->max.x - this->min.x;
    double sizeY = this->max.y - this->min.y;
    double sizeZ = this->max.z - this->min.z;

    return (sizeX + sizeY + sizeZ) / 3.0;
}

AABB* AABB::grow(double multiplier) const {
    return this->grow(multiplier, multiplier, multiplier);
}

AABB* AABB::grow(double x, double y, double z) const {
    const double x0 = this->min.x - x;
    const double y0 = this->min.y - y;
    const double z0 = this->min.z - z;
    const double x1 = this->max.x + x;
    const double y1 = this->max.y + y;
    const double z1 = this->max.z + z;

    return this->newTemp(x0, y0, z0, x1, y1, z1);
}

bool AABB::contains(Vec3* vec) {
    if (vec->x <= this->min.x || vec->x >= this->max.x)
        return false;

    if (vec->y <= this->min.y || vec->y >= this->max.y)
        return false;

    if (vec->z <= this->min.z || vec->z >= this->max.z)
        return false;

    return true;
}

// NON_MATCHING | Score: 1070 (lower is better)
// Not sure how to make this match.
bool AABB::intersects(const AABB* rhs) const {
    return (this->min.x<rhs->max.x&& this->max.x> rhs->min.x
            && this->min.y<rhs->max.y&& this->max.y> rhs->min.y
            && this->min.z<rhs->max.z&& this->max.z> rhs->min.z);
}

void AABB::resetPool() {};
