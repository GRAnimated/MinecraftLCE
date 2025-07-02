#include "Minecraft.World/Random.h"
#include "Minecraft.World/level/Level.h"
#include "Minecraft.World/level/block/Blocks.h"
#include "Minecraft.World/level/block/state/BlockState.h"
#include "Minecraft.World/level/levelgen/feature/ClayFeature.h"
#include "Minecraft.World/level/material/Material.h"
#include "Minecraft.Core/BlockPos.h"

ClayFeature::ClayFeature(int unk) : Feature(false), mBlock(Blocks::CLAY), field_18(unk) {}

bool ClayFeature::place(Level* level, Random& random, const BlockPos& pos) {
    if (level->getBlockState(pos)->getBlock()->getMaterial() != (Material*)Material::WATER) {
        return false;
    }

    int radius = random.nextInt(field_18 - 2) + 2;
    for (int x = pos.getX() - radius; x <= pos.getX() + radius; ++x) {
        for (int z = pos.getZ() - radius; z <= pos.getZ() + radius; ++z) {
            int deltaX = x - pos.getX();
            int deltaZ = z - pos.getZ();

            if ((deltaX * deltaX) + (deltaZ * deltaZ) <= (radius * radius)) {
                int y = pos.getY();
                for (int currentY = y - 1; currentY <= pos.getY() + 1; currentY++) {
                    BlockPos result = BlockPos(x, currentY, z);
                    Block* block = level->getBlockState(result)->getBlock();

                    if (block == Blocks::DIRT || block == Blocks::CLAY)
                        level->setBlock(result, mBlock->defaultBlockState(), 2, false);
                }
            }
        }
    }

    return true;
}