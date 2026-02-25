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

    BlockPos m_blockPos;
    const Direction* m_direction;
    Vec3* m_hitVector;
    std::shared_ptr<Entity> m_entity;
};
