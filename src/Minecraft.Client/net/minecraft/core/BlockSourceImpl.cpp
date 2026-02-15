#include "net/minecraft/core/BlockSourceImpl.h"
#include "net/minecraft/world/level/Level.h"
#include "net/minecraft/world/level/block/state/BlockState.h"

BlockSourceImpl::BlockSourceImpl(Level* level, const BlockPos& pos) {
    m_level = level;
    m_pos = pos;
}

double BlockSourceImpl::getX() {
    return m_pos.getX() + 0.5;
}

double BlockSourceImpl::getY() {
    return m_pos.getY() + 0.5;
}

double BlockSourceImpl::getZ() {
    return m_pos.getZ() + 0.5;
}

BlockPos BlockSourceImpl::getPos() {
    return m_pos;
}

const BlockState* BlockSourceImpl::getBlockState() {
    return m_level->getBlockState(m_pos);
}

Material* BlockSourceImpl::getMaterial() {
    return m_level->getBlockState(m_pos)->getMaterial();
}

std::shared_ptr<BlockEntity> BlockSourceImpl::getEntity() {
    return m_level->getBlockEntity(m_pos);
}

Level* BlockSourceImpl::getWorld() {
    return m_level;
}
