#pragma once

#include "net/minecraft/world/phys/Vec3.h"

class AABB {
public:
    Vec3 min;
    Vec3 max;

    static void CreateNewThreadStorage();

    class ThreadStorage {};

    static AABB* newPermanent(double, double, double, double, double, double);
    static AABB* newTemp(double, double, double, double, double, double);
    bool containsIncludingLowerBound(Vec3*) const;

    void set(double, double, double, double, double, double);
    Vec3* getCenter();
    AABB* divideInternalsBy(double);

    static AABB* sCrossShape;  // .got:000000710176F5E0
};
