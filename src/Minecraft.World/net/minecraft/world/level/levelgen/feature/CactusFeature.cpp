#include "net/minecraft/world/level/levelgen/feature/CactusFeature.h"

#include "net/minecraft/core/BlockPos.h"
#include "net/minecraft/world/Random.h"
#include "net/minecraft/world/level/Level.h"
#include "net/minecraft/world/level/block/Blocks.h"
#include "net/minecraft/world/level/block/CactusBlock.h"

bool CactusFeature::place(Level* level, Random& random, const BlockPos& pos) {
    for (int attempt = 0; attempt < 10; ++attempt) {
        BlockPos candidate
            = pos.offset(random.nextInt(8) - random.nextInt(8), random.nextInt(4) - random.nextInt(4),
                         random.nextInt(8) - random.nextInt(8));
        if (level->isEmptyBlock(candidate)) {
            int height = 1 + random.nextInt(random.nextInt(3) + 1);
            for (int y = 0; y < height; ++y) {
                if (static_cast<CactusBlock*>(Blocks::CACTUS)->canSurvive(level, candidate))
                    level->setBlock(candidate.above(y), Blocks::CACTUS->defaultBlockState(), 2, false);
            }
        }
    }
    return true;
}
