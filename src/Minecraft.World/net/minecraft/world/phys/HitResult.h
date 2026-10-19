#pragma once

#include "net/minecraft/core/BlockPos.h"
#include <memory>

class Vec3;
class Direction;
class Entity;

class HitResult {
public:
    ~HitResult();
    HitResult(Vec3*, const Direction*);
    HitResult(Vec3*, const Direction*, const BlockPos&);
    HitResult(std::shared_ptr<Entity> entity);

    const BlockPos& getBlockPos() const;

    BlockPos m_blockPos;
    int m_type;
    const Direction* m_direction;
    Vec3* m_hitVector;
    std::shared_ptr<Entity> m_entity;
};

ASSERT_SIZEOF(HitResult, 0x30)
