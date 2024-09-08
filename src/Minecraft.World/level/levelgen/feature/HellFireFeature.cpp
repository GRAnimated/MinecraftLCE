#include "Minecraft.World/level/levelgen/feature/HellFireFeature.h"
#include "Minecraft.Core/BlockPos.h"
#include "Minecraft.World/Random.h"
#include "Minecraft.World/level/Level.h"
#include "Minecraft.World/level/block/Blocks.h"
#include "Minecraft.World/level/block/state/BlockState.h"

HellFireFeature::HellFireFeature() : Feature(false) {}

bool HellFireFeature::place(Level* level, Random& random, const BlockPos& pos) {
    for (int i = 0; i < 64; i++) {
        BlockPos pos2 = pos.offset(random.nextInt(8) - random.nextInt(8), random.nextInt(4) - random.nextInt(4), random.nextInt(8) - random.nextInt(8));
        if (!level->isEmptyBlock(pos2) || level->getBlockState(pos2.below())->getBlock() != Blocks::NETHERRACK)
            continue;
        level->setBlock(pos2, Blocks::FIRE->defaultBlockState(), 2, false);
    }
    return true;
}
