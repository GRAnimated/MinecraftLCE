#include "net/minecraft/core/BlockSourceImpl.h"
#include "net/minecraft/world/level/Level.h"
#include "net/minecraft/world/level/block/state/BlockState.h"

BlockSourceImpl::BlockSourceImpl(Level* level, const BlockPos& pos) {
    mLevel = level;
    mPos = pos;
}

double BlockSourceImpl::getX() {
    return mPos.getX() + 0.5;
}

double BlockSourceImpl::getY() {
    return mPos.getY() + 0.5;
}

double BlockSourceImpl::getZ() {
    return mPos.getZ() + 0.5;
}

BlockPos BlockSourceImpl::getPos() {
    return mPos;
}

const BlockState* BlockSourceImpl::getBlockState() {
    return mLevel->getBlockState(mPos);
}

Material* BlockSourceImpl::getMaterial() {
    return mLevel->getBlockState(mPos)->getMaterial();
}

std::shared_ptr<BlockEntity> BlockSourceImpl::getEntity() {
    return mLevel->getBlockEntity(mPos);
}

Level* BlockSourceImpl::getWorld() {
    return mLevel;
}
