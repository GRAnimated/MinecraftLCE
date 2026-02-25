#include "net/minecraft/world/level/levelgen/feature/ClayFeature.h"

#include "net/minecraft/core/BlockPos.h"
#include "net/minecraft/world/Random.h"
#include "net/minecraft/world/level/Level.h"
#include "net/minecraft/world/level/block/Blocks.h"
#include "net/minecraft/world/level/block/state/BlockState.h"
#include "net/minecraft/world/level/material/Material.h"

ClayFeature::ClayFeature(int unk) : Feature(false), m_block(Blocks::CLAY), m_field18(unk) {}

bool ClayFeature::place(Level* level, Random& random, const BlockPos& pos) {
    if (level->getBlockState(pos)->getBlock()->getMaterial() != (Material*)Material::WATER) {
        return false;
    }

    int radius = random.nextInt(m_field18 - 2) + 2;
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
                        level->setBlock(result, m_block->defaultBlockState(), 2, false);
                }
            }
        }
    }

    return true;
}
