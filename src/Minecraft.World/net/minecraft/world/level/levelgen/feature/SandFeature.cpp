#include "net/minecraft/world/level/levelgen/feature/SandFeature.h"

#include "net/minecraft/client/CMinecraftApp.h"
#include "net/minecraft/core/MutableBlockPos.h"
#include "net/minecraft/world/Random.h"
#include "net/minecraft/world/level/Level.h"
#include "net/minecraft/world/level/block/Blocks.h"
#include "net/minecraft/world/level/block/state/BlockState.h"
#include "net/minecraft/world/level/material/Material.h"

// name guessed
SandFeature::SandFeature(Block* block, int radius) : Feature(false), m_block(block), m_radius(radius) {}

// name guessed
bool SandFeature::place(Level* level, Random& random, const BlockPos& pos) {
    if (level->getBlockState(pos)->getMaterial() != Material::WATER)
        return false;

    Level::setInstaTick(true);
    int radius = random.nextInt(m_radius - 2) + 2;
    if (CConsoleMinecraftApp::sInstance.getLevelGenerationOptions()
        && CConsoleMinecraftApp::sInstance.getLevelGenerationOptions()->intersects(
            pos.offset(-radius, -2, -radius), pos.offset(radius, 2, radius))) {
        Level::setInstaTick(false);
        return false;
    }

    MutableBlockPos candidate(0, 0, 0);
    for (int x = pos.getX() - radius; x <= pos.getX() + radius; ++x) {
        for (int z = pos.getZ() - radius; z <= pos.getZ() + radius; ++z) {
            int dx = x - pos.getX();
            int dz = z - pos.getZ();
            if (static_cast<unsigned int>(dx * dx + dz * dz) <= static_cast<unsigned int>(radius * radius)) {
                int y = pos.getY();
                for (int currentY = y - 2; currentY <= pos.getY() + 2; ++currentY) {
                    candidate.set(x, currentY, z);
                    Block* block = level->getBlockState(candidate)->getBlock();
                    if (block == Blocks::DIRT || block == Blocks::GRASS)
                        level->setBlock(candidate, m_block->defaultBlockState(), 2, false);
                }
            }
        }
    }
    Level::setInstaTick(false);
    return true;
}
