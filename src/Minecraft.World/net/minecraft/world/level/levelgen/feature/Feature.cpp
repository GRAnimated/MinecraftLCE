#include "net/minecraft/world/level/levelgen/feature/Feature.h"

#include "net/minecraft/world/level/Level.h"

Feature::Feature(bool isUpdate) : mIsUpdate(isUpdate) {}

// NON_MATCHING
Feature::~Feature() {}

void Feature::init() {}

void Feature::setBlock(Level* level, const BlockPos& pos, const BlockState* blockState) {
    if (mIsUpdate) {
        level->setBlock(pos, blockState, 3, false);
    } else {
        level->setBlock(pos, blockState, 2, false);
    }
}
