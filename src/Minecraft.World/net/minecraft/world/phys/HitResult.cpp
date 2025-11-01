#include "HitResult.h"
#include "net/minecraft/core/BlockPos.h"

const BlockPos& HitResult::getBlockPos() const {
    return this->mBlockPos;
}