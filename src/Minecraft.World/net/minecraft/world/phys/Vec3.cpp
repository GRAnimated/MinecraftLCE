#include "net/minecraft/world/phys/Vec3.h"

#include "cmath"
#include "net/minecraft/world/phys/AABB.h"

DEFINE_THREAD_STORAGE(Vec3, 1024)

double Vec3::dot(Vec3* rhs) {
    return this->m_x * rhs->m_x + this->m_y * rhs->m_y + this->m_z * rhs->m_z;
}

double Vec3::length() {
    return sqrt(this->m_x * this->m_x + this->m_y * this->m_y + this->m_z * this->m_z);
}

void Vec3::set(double x, double y, double z) {
    this->m_x = x;
    this->m_y = y;
    this->m_z = z;
}

void Vec3::resetPool() {}

double Vec3::distanceTo(AABB* aabb) {
    if (aabb->contains(this))
        return 0.0;

    double dX = 0.0;
    double dY = 0.0;
    double dZ = 0.0;

    if (this->m_x < aabb->m_inX)
        dX = aabb->m_inX - this->m_x;
    else if (this->m_x > aabb->m_axX)
        dX = this->m_x - aabb->m_axX;

    if (this->m_y < aabb->m_inY)
        dY = aabb->m_inY - this->m_y;
    else if (this->m_y > aabb->m_axY)
        dY = this->m_y - aabb->m_axY;

    if (this->m_z < aabb->m_inZ)
        dZ = aabb->m_inZ - this->m_z;
    else if (this->m_z > aabb->m_axZ)
        dZ = this->m_z - aabb->m_axZ;

    return std::sqrt(dX * dX + dY * dY + dZ * dZ);
}

Vec3* Vec3::closestPointOnSegment(Vec3* segStart, Vec3* segEnd) {
    Vec3* v1 = newTemp(this->m_x - segStart->m_x, this->m_y - segStart->m_y, this->m_z - segStart->m_z);
    Vec3* v2 = newTemp(segEnd->m_x - segStart->m_x, segEnd->m_y - segStart->m_y, segEnd->m_z - segStart->m_z);

    double dot = v1->dot(v2);
    if (dot <= 0.0) {
        return segStart;
    }

    double len2 = v2->dot(v2);
    if (len2 <= dot)
        return segEnd;

    double t = dot / len2;
    return newTemp(segStart->m_x + t * v2->m_x, segStart->m_y + t * v2->m_y, segStart->m_z + t * v2->m_z);
}

double Vec3::distanceToSegment(Vec3* segStart, Vec3* segEnd) {
    Vec3* closest = closestPointOnSegment(segStart, segEnd);
    Vec3* diff = newTemp(this->m_x - closest->m_x, this->m_y - closest->m_y, this->m_z - closest->m_z);
    return diff->length();
}
