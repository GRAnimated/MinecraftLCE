#pragma once

class Vec3i {
public:
    Vec3i();
    Vec3i(int x, int y, int z);
    Vec3i(double x, double y, double z);

    int getX() const;
    int getY() const;
    int getZ() const;
    double distSqr(const Vec3i&) const;

    int m_x;
    int m_y;
    int m_z;
};
