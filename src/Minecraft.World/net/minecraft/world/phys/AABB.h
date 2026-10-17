#pragma once

#include "net/minecraft/world/phys/Vec3.h"

class BlockPos;
class HitResult;

class AABB {
public:
    double m_inX;
    double m_inY;
    double m_inZ;
    double m_axX;
    double m_axY;
    double m_axZ;

    class ThreadStorage {
    public:
        ThreadStorage();
        ~ThreadStorage();

        AABB* m_storage;
        unsigned int m_unk;
    };
    static ThreadStorage* sDefaultThreadStorage;
    static int sThreadStorageIndex;
    static void CreateNewThreadStorage();
    static void UseDefaultThreadStorage();
    static void ReleaseThreadStorage();

    AABB() {}
    AABB(double, double, double, double, double, double);

    static AABB* newPermanent(double, double, double, double, double, double);
    static AABB* newPermanent(const BlockPos&);
    static AABB* newPermanent(const BlockPos&, const BlockPos&);
    static AABB* newPermanent(const AABB*);
    static AABB* newTemp(double, double, double, double, double, double);
    static AABB* newTemp(const BlockPos&);
    static AABB* newTemp(const BlockPos&, const BlockPos&);
    static AABB* newTemp(const AABB*);
    bool containsIncludingLowerBound(Vec3*) const;

    AABB* set(const AABB*);
    AABB* set(double, double, double, double, double, double);
    Vec3* getCenter() const;
    AABB* divideInternalsBy(double);
    double getSize() const;
    AABB* grow(double multiplier) const;
    AABB* grow(double x, double y, double z) const;
    AABB* shrink(double multiplier) const;
    AABB* shrink(double x, double y, double z) const;
    AABB* expand(double x, double y, double z) const;
    AABB* contract(double x, double y, double z);
    bool equals(const AABB* other) const;
    bool contains(Vec3* vec);
    bool contains(const BlockPos& pos) const;
    bool intersects(const AABB* rhs) const;
    bool intersects(double, double, double, double, double, double) const;
    void resetPool();
    AABB* move(const BlockPos&) const;
    AABB* move(double, double, double) const;
    HitResult* clip(Vec3*, Vec3*) const;
    Vec3* collideWithXPlane(double, Vec3*, Vec3*) const;
    Vec3* collideWithYPlane(double, Vec3*, Vec3*) const;
    Vec3* collideWithZPlane(double, Vec3*, Vec3*) const;
    bool isClosest(Vec3* start, Vec3* closest, Vec3* candidate) const;
    bool containsYZ(Vec3*) const;
    bool containsXZ(Vec3*) const;
    bool containsXY(Vec3*) const;
    void correctMinMax();
    double clipXCollide(const AABB*, double);
    double clipYCollide(const AABB*, double);
    double clipZCollide(const AABB*, double);

    static AABB* sCrossShape;  // .got:000000710176F5E0
};
