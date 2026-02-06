#include "net/minecraft/world/phys/AABB.h"

#include "NX/Platform.h"
#include "net/minecraft/core/BlockPos.h"
#include "net/minecraft/util/ThreadStorage.h"
#include "net/minecraft/world/phys/Vec3.h"
#include <algorithm>

DEFINE_THREAD_STORAGE(AABB, 1024)

AABB::AABB(double x1, double y1, double z1, double x2, double y2, double z2) {
    minX = std::min(x1, x2);
    minY = std::min(y1, y2);
    minZ = std::min(z1, z2);
    maxX = std::max(x1, x2);
    maxY = std::max(y1, y2);
    maxZ = std::max(z1, z2);
}

AABB* AABB::newPermanent(double x1, double y1, double z1, double x2, double y2, double z2) {
    return new AABB(x1, y1, z1, x2, y2, z2);
}
AABB* AABB::newPermanent(const BlockPos& pos) {
    return newPermanent(pos.getX(), pos.getY(), pos.getZ(), pos.getX() + 1, pos.getY() + 1, pos.getZ() + 1);
}

AABB* AABB::newPermanent(const AABB* other) {
    return newPermanent(other->minX, other->minY, other->minZ, other->maxX, other->maxY, other->maxZ);
}

AABB* AABB::newPermanent(const BlockPos& lhs, const BlockPos& rhs) {
    return newPermanent(lhs.getX(), lhs.getY(), lhs.getZ(), rhs.getX(), rhs.getY(), rhs.getZ());
}

AABB* AABB::newTemp(double x1, double y1, double z1, double x2, double y2, double z2) {
    ThreadStorage* ts = ((ThreadStorage*)TlsGetValue(sThreadStorageIndex));

    AABB* temp = &ts->mStorage[ts->mUnk];
    temp->set(x1, y1, z1, x2, y2, z2);

    ts->mUnk++;
    ts->mUnk &= 0x3ff;
    return temp;
}

AABB* AABB::newTemp(const BlockPos& pos) {
    return newTemp(pos.getX(), pos.getY(), pos.getZ(), pos.getX() + 1, pos.getY() + 1, pos.getZ() + 1);
}

AABB* AABB::newTemp(const BlockPos& lhs, const BlockPos& rhs) {
    return newTemp(lhs.getX(), lhs.getY(), lhs.getZ(), rhs.getX(), rhs.getY(), rhs.getZ());
}

AABB* AABB::newTemp(const AABB* aabb) {
    return newTemp(aabb->minX, aabb->minY, aabb->minZ, aabb->maxX, aabb->maxY, aabb->maxZ);
}

AABB* AABB::set(double x1, double y1, double z1, double x2, double y2, double z2) {
    minX = std::min(x1, x2);
    minY = std::min(y1, y2);
    minZ = std::min(z1, z2);
    maxX = std::max(x1, x2);
    maxY = std::max(y1, y2);
    maxZ = std::max(z1, z2);
    return this;
}

AABB* AABB::set(const AABB* newAABB) {
    minX = newAABB->minX;
    minY = newAABB->minY;
    minZ = newAABB->minZ;
    maxX = newAABB->maxX;
    maxY = newAABB->maxY;
    maxZ = newAABB->maxZ;
    return this;
}

Vec3* AABB::getCenter() const {
    return Vec3::newTemp(this->minX + (this->maxX - this->minX) * 0.5,
                         this->minY + (this->maxY - this->minY) * 0.5,
                         this->minZ + (this->maxZ - this->minZ) * 0.5);
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

AABB* AABB::expand(double dx, double dy, double dz) const {
    double x1 = this->minX;
    double y1 = this->minY;
    double z1 = this->minZ;
    double x2 = this->maxX;
    double y2 = this->maxY;
    double z2 = this->maxZ;

    double tx1 = x1 + dx;
    tx1 = (dx < 0.0) ? tx1 : x1;
    double tx2 = x2 + dx;
    tx2 = (dx > 0.0) ? tx2 : x2;

    double ty1 = y1 + dy;
    ty1 = (dy < 0.0) ? ty1 : y1;
    double ty2 = y2 + dy;
    ty2 = (dy > 0.0) ? ty2 : y2;

    double tz1 = z1 + dz;
    tz1 = (dz < 0.0) ? tz1 : z1;
    double tz2 = z2 + dz;
    tz2 = (dz > 0.0) ? tz2 : z2;

    return newTemp(tx1, ty1, tz1, tx2, ty2, tz2);
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

AABB* AABB::move(const BlockPos& pos) const {
    return newTemp(minX + pos.getX(), minY + pos.getY(), minZ + pos.getZ(), maxX + pos.getX(),
                   maxY + pos.getY(), maxZ + pos.getZ());
}

AABB* AABB::move(double x, double y, double z) const {
    return newTemp(minX + x, minY + y, minZ + z, maxX + x, maxY + y, maxZ + z);
}

double AABB::clipXCollide(const AABB* o, double offX) {
    if (o->maxY <= minY || o->minY >= maxY || o->maxZ <= minZ || o->minZ >= maxZ)
        return offX;
    if (offX > 0.0 && o->maxX <= minX)
        return std::min(offX, minX - o->maxX);
    if (offX < 0.0 && o->minX >= maxX)
        return std::max(offX, maxX - o->minX);

    return offX;
}

double AABB::clipYCollide(const AABB* o, double offY) {
    if (o->maxX <= minX || o->minX >= maxX || o->maxZ <= minZ || o->minZ >= maxZ)
        return offY;
    if (offY > 0.0 && o->maxY <= minY)
        return std::min(offY, minY - o->maxY);
    if (offY < 0.0 && o->minY >= maxY)
        return std::max(offY, maxY - o->minY);

    return offY;
}

double AABB::clipZCollide(const AABB* o, double offZ) {
    if (o->maxX <= minX || o->minX >= maxX || o->maxY <= minY || o->minY >= maxY)
        return offZ;
    if (offZ > 0.0 && o->maxZ <= minZ)
        return std::min(offZ, minZ - o->maxZ);
    if (offZ < 0.0 && o->minZ >= maxZ)
        return std::max(offZ, maxZ - o->minZ);

    return offZ;
}
