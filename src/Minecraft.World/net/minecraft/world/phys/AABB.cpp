#include "net/minecraft/util/Mth.h"
#include "net/minecraft/world/phys/AABB.h"

#include "net/minecraft/util/ThreadStorage.h"
#include <algorithm>

DEFINE_THREAD_STORAGE(AABB, 1024)

Vec3* AABB::getCenter() const {
    return Vec3::newTemp(this->minX + (this->maxX - this->minX) * 0.5,
                         this->minY + (this->maxY - this->minY) * 0.5,
                         this->minZ + (this->maxZ - this->minZ) * 0.5);
}

AABB* AABB::newPermanent(double x1, double y1, double z1, double x2, double y2, double z2) {
    return new AABB(x1, y1, z1, x2, y2, z2);
}

AABB* AABB::newPermanent(const AABB* other) {
    return newPermanent(other->minX, other->minY, other->minZ, other->maxX, other->maxY, other->maxZ);
}

AABB::AABB(double x1, double y1, double z1, double x2, double y2, double z2) {
    minX = std::min(x1, x2);
    minY = std::min(y1, y2);
    minZ = std::min(z1, z2);
    maxX = std::max(x1, x2);
    maxY = std::max(y1, y2);
    maxZ = std::max(z1, z2);
}

double AABB::getSize() const {
    double sizeX = this->maxX - this->minX;
    double sizeY = this->maxY - this->minY;
    double sizeZ = this->maxZ - this->minZ;

    return (sizeX + sizeY + sizeZ) / 3.0;
}

AABB* AABB::grow(double multiplier) const {
    return this->grow(multiplier, multiplier, multiplier);
}

AABB* AABB::grow(double x, double y, double z) const {
    const double x0 = this->minX - x;
    const double y0 = this->minY - y;
    const double z0 = this->minZ - z;
    const double x1 = this->maxX + x;
    const double y1 = this->maxY + y;
    const double z1 = this->maxZ + z;

    return this->newTemp(x0, y0, z0, x1, y1, z1);
}

bool AABB::contains(Vec3* vec) {
    if (vec->x <= this->minX || vec->x >= this->maxX)
        return false;

    if (vec->y <= this->minY || vec->y >= this->maxY)
        return false;

    if (vec->z <= this->minZ || vec->z >= this->maxZ)
        return false;

    return true;
}

bool AABB::intersects(const AABB* rhs) const {
    return intersects(rhs->minX, rhs->minY, rhs->minZ, rhs->maxX, rhs->maxY, rhs->maxZ);
}

// NON_MATCHING SCORE: 1005, i have no idea, it's only the conditional branches
bool AABB::intersects(double oMinX, double oMinY, double oMinZ, double oMaxX, double oMaxY,
                      double oMaxZ) const {
    if (oMaxX <= minX || oMinX >= maxX)
        return false;
    if (oMaxY <= minY || oMinY >= maxY)
        return false;
    return (!(oMaxZ <= minZ)) && (!(oMinZ >= maxZ));
}

void AABB::resetPool() {};
