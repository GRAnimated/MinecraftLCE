#include "net/minecraft/world/phys/HitResult.h"
#include "net/minecraft/core/BlockPos.h"

const BlockPos& HitResult::getBlockPos() const {
    return this->mBlockPos;
}
