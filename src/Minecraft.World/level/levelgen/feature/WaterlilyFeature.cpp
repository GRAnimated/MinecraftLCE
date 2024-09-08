#include "Minecraft.World/level/levelgen/feature/WaterlilyFeature.h"
#include "Minecraft.Core/BlockPos.h"
#include "Minecraft.World/Random.h"
#include "Minecraft.World/level/Level.h"
#include "Minecraft.World/level/block/Blocks.h"
#include "Minecraft.World/level/block/state/BlockState.h"

WaterlilyFeature::WaterlilyFeature() : Feature(false) {}

bool WaterlilyFeature::place(Level* level, Random& random, const BlockPos& pos) {
    for (int i = 0; i < 10; i++) {
        int x = pos.getX() + random.nextInt(8) - random.nextInt(8);
        int y = pos.getY() + random.nextInt(4) - random.nextInt(4);
        int z = pos.getZ() + random.nextInt(8) - random.nextInt(8);

        if (level->isEmptyBlock(BlockPos(x, y, z))) {
            if (Blocks::WATERLILY->mayPlace(level, BlockPos(x, y, z))) {
                level->setBlock(BlockPos(x, y, z), Blocks::WATERLILY->defaultBlockState(), 2, false);
            }
        }
    }

    return true;
}
