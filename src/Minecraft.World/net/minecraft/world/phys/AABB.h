#pragma once

#include "net/minecraft/world/phys/Vec3.h"

class BlockPos;
class HitResult;

class AABB {
public:
    Vec3 min;
    Vec3 max;

    class ThreadStorage {
    public:
        ThreadStorage();
        ~ThreadStorage();

        AABB* mStorage;
        unsigned int mUnk;
    };
    static ThreadStorage* sDefaultThreadStorage;
    static int sThreadStorageIndex;
    static void CreateNewThreadStorage();
    static void UseDefaultThreadStorage();
    static void ReleaseThreadStorage();

    AABB() {}

    static AABB* newPermanent(double, double, double, double, double, double);
    static AABB* newTemp(double, double, double, double, double, double);
    bool containsIncludingLowerBound(Vec3*) const;

    void set(double, double, double, double, double, double);
    Vec3* getCenter() const;
    AABB* divideInternalsBy(double);
    double getSize() const;
    AABB* grow(double multiplier) const;
    AABB* grow(double x, double y, double z) const;
    bool contains(Vec3* vec);
    bool intersects(const AABB* rhs) const;
    void resetPool();
    AABB* move(const BlockPos&) const;
    HitResult* clip(Vec3*, Vec3*) const;
    void correctMinMax();

    static AABB* sCrossShape;  // .got:000000710176F5E0
};
