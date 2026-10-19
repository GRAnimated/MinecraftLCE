#include "net/minecraft/world/phys/HitResult.h"

#include "net/minecraft/core/BlockPos.h"
#include "net/minecraft/world/entity/Entity.h"
#include "net/minecraft/world/phys/Vec3.h"

// name guessed
HitResult::HitResult(Vec3* hit, const Direction* direction) {
    m_type = 1;
    m_blockPos = BlockPos::zero;
    m_direction = direction;
    m_hitVector = Vec3::newTemp(hit->m_x, hit->m_y, hit->m_z);
    m_entity = nullptr;
}

HitResult::HitResult(Vec3* hit, const Direction* direction, const BlockPos& pos) {
    m_type = 1;
    m_blockPos = BlockPos(pos.getX(), pos.getY(), pos.getZ());
    m_direction = direction;
    m_hitVector = Vec3::newTemp(hit->m_x, hit->m_y, hit->m_z);
    m_entity = nullptr;
}

HitResult::HitResult(std::shared_ptr<Entity> entity) {
    m_type = 2;
    m_entity = entity;
    m_hitVector = Vec3::newTemp(entity->m_x, entity->m_y, entity->m_z);
}

HitResult::~HitResult() = default;

const BlockPos& HitResult::getBlockPos() const {
    return this->m_blockPos;
}
