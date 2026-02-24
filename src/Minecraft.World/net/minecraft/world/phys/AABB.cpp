#include "net/minecraft/world/phys/AABB.h"

#include "NX/Platform.h"
#include "net/minecraft/core/BlockPos.h"
#include "net/minecraft/util/ThreadStorage.h"
#include "net/minecraft/world/phys/Vec3.h"
#include <algorithm>

DEFINE_THREAD_STORAGE(AABB, 1024)

AABB::AABB(double x1, double y1, double z1, double x2, double y2, double z2) {
    m_inX = std::min(x1, x2);
    m_inY = std::min(y1, y2);
    m_inZ = std::min(z1, z2);
    m_axX = std::max(x1, x2);
    m_axY = std::max(y1, y2);
    m_axZ = std::max(z1, z2);
}

AABB* AABB::newPermanent(double x1, double y1, double z1, double x2, double y2, double z2) {
    return new AABB(x1, y1, z1, x2, y2, z2);
}

AABB* AABB::newPermanent(const AABB* other) {
    return newPermanent(other->m_inX, other->m_inY, other->m_inZ, other->m_axX, other->m_axY, other->m_axZ);
}

AABB* AABB::newTemp(double x1, double y1, double z1, double x2, double y2, double z2) {
    ThreadStorage* ts = ((ThreadStorage*)TlsGetValue(sThreadStorageIndex));

    AABB* temp = &ts->m_storage[ts->m_unk];
    temp->set(x1, y1, z1, x2, y2, z2);

    ts->m_unk++;
    ts->m_unk &= 0x3ff;
    return temp;
}

AABB* AABB::set(double x1, double y1, double z1, double x2, double y2, double z2) {
    m_inX = std::min(x1, x2);
    m_inY = std::min(y1, y2);
    m_inZ = std::min(z1, z2);
    m_axX = std::max(x1, x2);
    m_axY = std::max(y1, y2);
    m_axZ = std::max(z1, z2);
    return this;
}

AABB* AABB::set(const AABB* newAABB) {
    m_inX = newAABB->m_inX;
    m_inY = newAABB->m_inY;
    m_inZ = newAABB->m_inZ;
    m_axX = newAABB->m_axX;
    m_axY = newAABB->m_axY;
    m_axZ = newAABB->m_axZ;
    return this;
}

Vec3* AABB::getCenter() const {
    return Vec3::newTemp(this->m_inX + (this->m_axX - this->m_inX) * 0.5,
                         this->m_inY + (this->m_axY - this->m_inY) * 0.5,
                         this->m_inZ + (this->m_axZ - this->m_inZ) * 0.5);
}

double AABB::getSize() const {
    double sizeX = this->m_axX - this->m_inX;
    double sizeY = this->m_axY - this->m_inY;
    double sizeZ = this->m_axZ - this->m_inZ;

    return (sizeX + sizeY + sizeZ) / 3.0;
}

AABB* AABB::grow(double multiplier) const {
    return this->grow(multiplier, multiplier, multiplier);
}

AABB* AABB::grow(double x, double y, double z) const {
    const double x0 = this->m_inX - x;
    const double y0 = this->m_inY - y;
    const double z0 = this->m_inZ - z;
    const double x1 = this->m_axX + x;
    const double y1 = this->m_axY + y;
    const double z1 = this->m_axZ + z;

    return this->newTemp(x0, y0, z0, x1, y1, z1);
}

AABB* AABB::expand(double dx, double dy, double dz) const {
    double x1 = this->m_inX;
    double y1 = this->m_inY;
    double z1 = this->m_inZ;
    double x2 = this->m_axX;
    double y2 = this->m_axY;
    double z2 = this->m_axZ;

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
    if (vec->m_x <= this->m_inX || vec->m_x >= this->m_axX)
        return false;

    if (vec->m_y <= this->m_inY || vec->m_y >= this->m_axY)
        return false;

    if (vec->m_z <= this->m_inZ || vec->m_z >= this->m_axZ)
        return false;

    return true;
}

bool AABB::intersects(const AABB* rhs) const {
    return intersects(rhs->m_inX, rhs->m_inY, rhs->m_inZ, rhs->m_axX, rhs->m_axY, rhs->m_axZ);
}

// NON_MATCHING SCORE: 1005, i have no idea, it's only the conditional branches
bool AABB::intersects(double oMinX, double oMinY, double oMinZ, double oMaxX, double oMaxY,
                      double oMaxZ) const {
    if (oMaxX <= m_inX || oMinX >= m_axX)
        return false;
    if (oMaxY <= m_inY || oMinY >= m_axY)
        return false;
    return (!(oMaxZ <= m_inZ)) && (!(oMinZ >= m_axZ));
}

void AABB::resetPool() {};

AABB* AABB::move(const BlockPos& pos) const {
    return newTemp(m_inX + pos.getX(), m_inY + pos.getY(), m_inZ + pos.getZ(), m_axX + pos.getX(),
                   m_axY + pos.getY(), m_axZ + pos.getZ());
}

AABB* AABB::move(double x, double y, double z) const {
    return newTemp(m_inX + x, m_inY + y, m_inZ + z, m_axX + x, m_axY + y, m_axZ + z);
}

double AABB::clipXCollide(const AABB* o, double offX) {
    if (o->m_axY <= m_inY || o->m_inY >= m_axY || o->m_axZ <= m_inZ || o->m_inZ >= m_axZ)
        return offX;
    if (offX > 0.0 && o->m_axX <= m_inX)
        return std::min(offX, m_inX - o->m_axX);
    if (offX < 0.0 && o->m_inX >= m_axX)
        return std::max(offX, m_axX - o->m_inX);

    return offX;
}

double AABB::clipYCollide(const AABB* o, double offY) {
    if (o->m_axX <= m_inX || o->m_inX >= m_axX || o->m_axZ <= m_inZ || o->m_inZ >= m_axZ)
        return offY;
    if (offY > 0.0 && o->m_axY <= m_inY)
        return std::min(offY, m_inY - o->m_axY);
    if (offY < 0.0 && o->m_inY >= m_axY)
        return std::max(offY, m_axY - o->m_inY);

    return offY;
}

double AABB::clipZCollide(const AABB* o, double offZ) {
    if (o->m_axX <= m_inX || o->m_inX >= m_axX || o->m_axY <= m_inY || o->m_inY >= m_axY)
        return offZ;
    if (offZ > 0.0 && o->m_axZ <= m_inZ)
        return std::min(offZ, m_inZ - o->m_axZ);
    if (offZ < 0.0 && o->m_inZ >= m_axZ)
        return std::max(offZ, m_axZ - o->m_inZ);

    return offZ;
}
