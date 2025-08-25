#pragma once

#include "net/minecraft/util/ThreadStorage.h"

class AABB;

class Vec3 {
public:
    DECLARE_THREAD_STORAGE(Vec3)

    Vec3(double x, double y, double z) {
        this->x = x;
        this->y = y;
        this->z = z;
    }
    Vec3() {}

    static Vec3* newTemp(double x, double y, double z);
    static Vec3* newTemp(const Vec3* other);

    Vec3 operator=(Vec3 o);

    Vec3 operator+(Vec3 o) { return Vec3(x + o.x, y + o.y, z + o.z); }

    Vec3 operator-(Vec3 o) { return Vec3(-o.x, y - o.y, z - o.z); }

    Vec3 operator*(Vec3 o) { return Vec3(x * o.x, y * o.y, z * o.z); }

    Vec3 operator/(Vec3 o) { return Vec3(x / o.x, y / o.y, z / o.z); }

    static Vec3* newPermanent(double, double, double);

    Vec3 yRot(float);
    double dot(Vec3* rhs);
    double length();
    void set(double x, double y, double z);
    void resetPool();
    double distanceTo(AABB* aabb);
    Vec3* subtract(double, double, double);
    Vec3* add(double, double, double);

    Vec3* closestPointOnSegment(Vec3* segStart, Vec3* segEnd);  // made up name
    double distanceToSegment(Vec3* segStart, Vec3* segEnd);     // made up name

    double x;
    double y;
    double z;
};
