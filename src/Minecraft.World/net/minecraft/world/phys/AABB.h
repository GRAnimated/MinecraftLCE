#pragma once

#include "net/minecraft/world/phys/Vec3.h"

class BlockPos;
class HitResult;

class AABB {
public:
    double minX;
    double minY;
    double minZ;
    double maxX;
    double maxY;
    double maxZ;

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
    AABB(double x1, double y1, double z1, double x2, double y2, double z2);

    static AABB* newPermanent(double x1, double y1, double z1, double x2, double y2, double z2);
    static AABB* newPermanent(const BlockPos& pos);
    static AABB* newPermanent(const AABB* aabb);
    static AABB* newPermanent(const BlockPos& lhs, const BlockPos& rhs);
    static AABB* newTemp(double x1, double y1, double z1, double x2, double y2, double z2);
    static AABB* newTemp(const BlockPos& pos);
    static AABB* newTemp(const BlockPos& lhs, const BlockPos& rhs);
    static AABB* newTemp(const AABB* aabb);
    bool containsIncludingLowerBound(Vec3*) const;

    AABB* set(const AABB*);
    AABB* set(double x1, double y1, double z1, double x2, double y2, double z2);
    Vec3* getCenter() const;
    AABB* divideInternalsBy(double);
    double getSize() const;
    AABB* grow(double multiplier) const;
    AABB* grow(double x, double y, double z) const;
    AABB* expand(double x, double y, double z) const;
    bool contains(Vec3* vec);
    bool intersects(const AABB* rhs) const;
    bool intersects(double x1, double y1, double z1, double x2, double y2, double z2) const;
    void resetPool();
    AABB* move(const BlockPos&) const;
    AABB* move(double, double, double) const;
    HitResult* clip(Vec3*, Vec3*) const;
    void correctMinMax();
    double clipXCollide(const AABB*, double);
    double clipYCollide(const AABB*, double);
    double clipZCollide(const AABB*, double);

    static AABB* sCrossShape;  // .got:000000710176F5E0
};
