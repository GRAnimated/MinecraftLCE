#pragma once

#include "net/minecraft/core/BlockPos.h"
#include <memory>

class Vec3;
class Direction;
class Entity;

class HitResult {
public:
    ~HitResult();
    HitResult(Vec3*, const Direction*, const BlockPos&);

    const BlockPos& getBlockPos() const;

    BlockPos mBlockPos;
    const Direction* mDirection;
    Vec3* mHitVector;
    std::shared_ptr<Entity> mEntity;
};
