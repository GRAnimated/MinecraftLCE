#include "net/minecraft/core/BlockPos.h"
#include "net/minecraft/world/level/Level.h"
#include "net/minecraft/world/level/block/Blocks.h"
#include "net/minecraft/world/level/block/state/BlockState.h"
#include "net/minecraft/world/level/levelgen/feature/HellSpringFeature.h"
#include "net/minecraft/world/level/material/Material.h"

HellSpringFeature::HellSpringFeature(Block* block, bool forcePlacement)
    : Feature(false), mBlock(block), mIsForcePlacement(forcePlacement) {}

bool HellSpringFeature::place(Level* level, Random& random, const BlockPos& pos) {
    if (level->getBlockState(pos.above())->getBlock() == Blocks::NETHERRACK
        && (level->getBlockState(pos)->getBlock()->getMaterial() == (Material*)Material::AIR
            || level->getBlockState(pos)->getBlock() == Blocks::NETHERRACK)) {
        int netherrackCount = 0;

        if (level->getBlockState(pos.west())->getBlock() == Blocks::NETHERRACK) {
            netherrackCount++;
        }
        if (level->getBlockState(pos.east())->getBlock() == Blocks::NETHERRACK) {
            netherrackCount++;
        }
        if (level->getBlockState(pos.north())->getBlock() == Blocks::NETHERRACK) {
            netherrackCount++;
        }
        if (level->getBlockState(pos.south())->getBlock() == Blocks::NETHERRACK) {
            netherrackCount++;
        }
        if (level->getBlockState(pos.below())->getBlock() == Blocks::NETHERRACK) {
            netherrackCount++;
        }

        int airCount = 0;

        if (level->isEmptyBlock(pos.west())) {
            airCount++;
        }
        if (level->isEmptyBlock(pos.east())) {
            airCount++;
        }
        if (level->isEmptyBlock(pos.north())) {
            airCount++;
        }
        if (level->isEmptyBlock(pos.south())) {
            airCount++;
        }
        if (level->isEmptyBlock(pos.below())) {
            airCount++;
        }

        if ((!mIsForcePlacement && netherrackCount == 4 && airCount == 1) || netherrackCount == 5) {
            const BlockState* lava = mBlock->defaultBlockState();
            level->setBlock(pos, lava, 2, false);
            level->instaTick(pos, lava, random);
        }
        return true;
    }
    return false;
}
