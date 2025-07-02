#pragma once

class Vec3 {
public:
    Vec3(double x, double y, double z) {
        this->x = x;
        this->y = y;
        this->z = z;
    }
    Vec3() = default;

    static Vec3* newTemp(double x, double y, double z);

    Vec3 operator=(Vec3 o);

    Vec3 operator+(Vec3 o) { return Vec3(x + o.x, y + o.y, z + o.z); }

    Vec3 operator-(Vec3 o) { return Vec3(-o.x, y - o.y, z - o.z); }

    Vec3 operator*(Vec3 o) { return Vec3(x * o.x, y * o.y, z * o.z); }

    Vec3 operator/(Vec3 o) { return Vec3(x / o.x, y / o.y, z / o.z); }

    static void CreateNewThreadStorage();
    static Vec3* newPermanent(double, double, double);

    Vec3 yRot(float);

    class ThreadStorage {};

    double x;
    double y;
    double z;
};