#include "net/minecraft/world/level/levelgen/feature/BlockBlobFeature.h"

#include "net/minecraft/core/BlockPosIterator.h"
#include "net/minecraft/world/Random.h"
#include "net/minecraft/world/level/Level.h"
#include "net/minecraft/world/level/block/Blocks.h"
#include "net/minecraft/world/level/block/state/BlockState.h"

BlockBlobFeature::BlockBlobFeature(Block* block, int radius)
    : Feature(false), m_block(block), m_radius(radius) {}

BlockBlobFeature::~BlockBlobFeature() = default;

// Settle on natural ground, then overlap three independently sized stone blobs.
bool BlockBlobFeature::place(Level* level, Random& random, const BlockPos& origin) {
    BlockPos pos = origin;
    while (pos.getY() > 3) {
        if (!level->isEmptyBlock(pos.below())) {
            Block* ground = level->getBlockState(pos.below())->getBlock();
            if (ground == Blocks::GRASS || ground == Blocks::DIRT || ground == Blocks::STONE)
                break;
        }
        pos = pos.below();
    }
    if (pos.getY() <= 3)
        return false;

    int size = m_radius;
    for (int attempt = 0; size >= 0 && attempt < 3; ++attempt) {
        int x = size + random.nextInt(2);
        int y = size + random.nextInt(2);
        int z = size + random.nextInt(2);
        float radius = (x + y + z) * 0.333f + 0.5f;
        BlockPosIterator* positions = BlockPos::between(pos.offset(-x, -y, -z), pos.offset(x, y, z));
        while (positions->hasNext()) {
            BlockPos candidate = *positions->next();
            if (candidate.distSqr(pos) <= radius * radius)
                level->setBlock(candidate, m_block->defaultBlockState(), 4, false);
        }
        delete positions;
        pos = pos.offset(-(size + 1) + random.nextInt(2 + size * 2), -random.nextInt(2),
                         -(size + 1) + random.nextInt(2 + size * 2));
    }
    return true;
}
