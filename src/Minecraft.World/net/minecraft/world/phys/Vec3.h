#pragma once

#include "net/minecraft/util/ThreadStorage.h"

class AABB;
class Vec3i;

class Vec3 {
public:
    DECLARE_THREAD_STORAGE(Vec3)

    Vec3(double x, double y, double z) {
        if (x == -0.0)
            x = 0.0;
        if (y == -0.0)
            y = 0.0;
        if (z == -0.0)
            z = 0.0;
        this->m_x = x;
        this->m_y = y;
        this->m_z = z;
    }
    Vec3() {}

    static Vec3* newTemp(double x, double y, double z);
    static Vec3* newTemp(const Vec3* other);
    static Vec3* newTemp(const Vec3i& other);
    static void staticCtor();
    static Vec3* ZERO;

    Vec3 operator=(Vec3 o);

    Vec3 operator+(Vec3 o) { return Vec3(m_x + o.m_x, m_y + o.m_y, m_z + o.m_z); }

    Vec3 operator-(Vec3 o) { return Vec3(-o.m_x, m_y - o.m_y, m_z - o.m_z); }

    Vec3 operator*(Vec3 o) { return Vec3(m_x * o.m_x, m_y * o.m_y, m_z * o.m_z); }

    Vec3 operator/(Vec3 o) { return Vec3(m_x / o.m_x, m_y / o.m_y, m_z / o.m_z); }

    static Vec3* newPermanent(double, double, double);
    static Vec3* newPermanent(const Vec3* other);

    Vec3* xRot(float);
    Vec3* yRot(float);
    Vec3* zRot(float);
    double dot(Vec3* rhs);
    double length();
    double lengthSqr();
    Vec3* set(double x, double y, double z);
    static void resetPool();
    double distanceTo(AABB* aabb);
    double distanceTo(Vec3* other);
    double distanceToSqr(Vec3* other);
    Vec3* subtract(Vec3* other);
    Vec3* subtract(double, double, double);
    Vec3* add(double, double, double);
    Vec3* add(Vec3* other);
    Vec3* vectorTo(Vec3* other);
    Vec3* cross(Vec3* other);
    Vec3* lerp(Vec3* other, double weight);
    bool equals(Vec3* other);
    Vec3* getIntermediateWithXValue(Vec3* other, double x);
    Vec3* getIntermediateWithYValue(Vec3* other, double y);
    Vec3* getIntermediateWithZValue(Vec3* other, double z);
    Vec3* normalize();
    Vec3* scale(double);

    Vec3* closestPointOnSegment(Vec3* segStart, Vec3* segEnd);  // made up name
    double distanceToSegment(Vec3* segStart, Vec3* segEnd);     // made up name

    double m_x;
    double m_y;
    double m_z;
};
