#pragma once

#include "net/minecraft/util/ThreadStorage.h"

class AABB;

class Vec3 {
public:
    DECLARE_THREAD_STORAGE(Vec3)

    Vec3(double x, double y, double z) {
        this->m_x = x;
        this->m_y = y;
        this->m_z = z;
    }
    Vec3() {}

    static Vec3* newTemp(double x, double y, double z);
    static Vec3* newTemp(const Vec3* other);

    Vec3 operator=(Vec3 o);

    Vec3 operator+(Vec3 o) { return Vec3(m_x + o.m_x, m_y + o.m_y, m_z + o.m_z); }

    Vec3 operator-(Vec3 o) { return Vec3(-o.m_x, m_y - o.m_y, m_z - o.m_z); }

    Vec3 operator*(Vec3 o) { return Vec3(m_x * o.m_x, m_y * o.m_y, m_z * o.m_z); }

    Vec3 operator/(Vec3 o) { return Vec3(m_x / o.m_x, m_y / o.m_y, m_z / o.m_z); }

    static Vec3* newPermanent(double, double, double);

    Vec3 yRot(float);
    double dot(Vec3* rhs);
    double length();
    void set(double x, double y, double z);
    static void resetPool();
    double distanceTo(AABB* aabb);
    Vec3* subtract(double, double, double);
    Vec3* add(double, double, double);
    Vec3* normalize();
    Vec3* scale(double);

    Vec3* closestPointOnSegment(Vec3* segStart, Vec3* segEnd);  // made up name
    double distanceToSegment(Vec3* segStart, Vec3* segEnd);     // made up name

    double m_x;
    double m_y;
    double m_z;
};
