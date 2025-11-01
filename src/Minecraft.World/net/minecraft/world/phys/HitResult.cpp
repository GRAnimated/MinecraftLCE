#include "net/minecraft/core/BlockPos.h"
#include "net/minecraft/world/phys/HitResult.h"

const BlockPos& HitResult::getBlockPos() const {
    return this->mBlockPos;
}
