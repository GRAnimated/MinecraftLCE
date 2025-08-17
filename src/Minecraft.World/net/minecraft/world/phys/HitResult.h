#pragma once

class Vec3;
class Direction;
class BlockPos;

class HitResult {
public:
    ~HitResult();
    HitResult(Vec3*, const Direction*, const BlockPos&);

    void* fill[2];
    const Direction* mDirection;
    Vec3* mHitVector;
    void* anotherFiller[2];
};
