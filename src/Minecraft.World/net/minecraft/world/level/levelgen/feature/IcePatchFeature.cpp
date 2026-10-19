#include "net/minecraft/world/level/levelgen/feature/IcePatchFeature.h"

#include "net/minecraft/core/MutableBlockPos.h"
#include "net/minecraft/world/Random.h"
#include "net/minecraft/world/level/Level.h"
#include "net/minecraft/world/level/block/Blocks.h"

// name guessed
IcePatchFeature::IcePatchFeature(int radius)
    : Feature(false), m_block(Blocks::PACKED_ICE), m_radius(radius) {}
IcePatchFeature::~IcePatchFeature() = default;

// name guessed
bool IcePatchFeature::place(Level* level, Random& random, const BlockPos& origin) {
    BlockPos pos = origin;
    while (level->isEmptyBlock(pos) && pos.getY() > 2)
        pos = pos.below();
    if (level->getBlockState(pos)->getBlock() != Blocks::SNOW)
        return false;
    int radius = random.nextInt(m_radius - 2) + 2;
    MutableBlockPos candidate(0, 0, 0);
    for (int x = pos.getX() - radius; x <= pos.getX() + radius; ++x) {
        for (int z = pos.getZ() - radius; z <= pos.getZ() + radius; ++z) {
            int dx = x - pos.getX();
            int dz = z - pos.getZ();
            if (dx * dx + dz * dz > radius * radius)
                continue;
            for (int y = pos.getY() - 1; y <= pos.getY() + 1; ++y) {
                candidate.set(x, y, z);
                Block* block = level->getBlockState(candidate)->getBlock();
                if (block == Blocks::DIRT || block == Blocks::SNOW || block == Blocks::ICE)
                    level->setBlock(candidate, m_block->defaultBlockState(), 2, false);
            }
        }
    }
    return true;
}
