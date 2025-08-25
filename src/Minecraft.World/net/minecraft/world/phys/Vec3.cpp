#include "net/minecraft/world/phys/Vec3.h"

#include "cmath"
#include "net/minecraft/world/phys/AABB.h"

DEFINE_THREAD_STORAGE(Vec3, 1024)

double Vec3::dot(Vec3* rhs) {
    return this->x * rhs->x + this->y * rhs->y + this->z * rhs->z;
}

double Vec3::length() {
    return sqrt(this->x * this->x + this->y * this->y + this->z * this->z);
}

void Vec3::set(double x, double y, double z) {
    this->x = x;
    this->y = y;
    this->z = z;
}

void Vec3::resetPool() {}

double Vec3::distanceTo(AABB* aabb) {
    if (aabb->contains(this))
        return 0.0;

    double dX = 0.0;
    double dY = 0.0;
    double dZ = 0.0;

    if (this->x < aabb->min.x)
        dX = aabb->min.x - this->x;
    else if (this->x > aabb->max.x)
        dX = this->x - aabb->max.x;

    if (this->y < aabb->min.y)
        dY = aabb->min.y - this->y;
    else if (this->y > aabb->max.y)
        dY = this->y - aabb->max.y;

    if (this->z < aabb->min.z)
        dZ = aabb->min.z - this->z;
    else if (this->z > aabb->max.z)
        dZ = this->z - aabb->max.z;

    return std::sqrt(dX * dX + dY * dY + dZ * dZ);
}

Vec3* Vec3::closestPointOnSegment(Vec3* segStart, Vec3* segEnd) {
    Vec3* v1 = newTemp(this->x - segStart->x, this->y - segStart->y, this->z - segStart->z);
    Vec3* v2 = newTemp(segEnd->x - segStart->x, segEnd->y - segStart->y, segEnd->z - segStart->z);

    double dot = v1->dot(v2);
    if (dot <= 0.0) {
        return segStart;
    }

    double len2 = v2->dot(v2);
    if (len2 <= dot)
        return segEnd;

    double t = dot / len2;
    return newTemp(segStart->x + t * v2->x, segStart->y + t * v2->y, segStart->z + t * v2->z);
}

double Vec3::distanceToSegment(Vec3* segStart, Vec3* segEnd) {
    Vec3* closest = closestPointOnSegment(segStart, segEnd);
    Vec3* diff = newTemp(this->x - closest->x, this->y - closest->y, this->z - closest->z);
    return diff->length();
}
