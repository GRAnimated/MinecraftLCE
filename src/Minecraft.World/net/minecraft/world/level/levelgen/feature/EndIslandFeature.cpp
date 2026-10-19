#include "net/minecraft/world/level/levelgen/feature/EndIslandFeature.h"

#include "net/minecraft/core/BlockPos.h"
#include "net/minecraft/world/Random.h"
#include "net/minecraft/world/level/block/Block.h"
#include "net/minecraft/world/level/block/Blocks.h"
#include <cmath>

// name guessed
EndIslandFeature::EndIslandFeature() : Feature(false) {}

/** Shrink each successive disk; preserve the original random calls and block-write order.
 */
// name guessed
bool EndIslandFeature::place(Level* level, Random& random, const BlockPos& origin) {
    float radius = (float)random.nextInt(3) + 4.0f;
    for (int y = 0; radius > 0.5f; --y) {
        for (int x = (int)std::floor(-radius); x <= (int)std::ceil(radius); ++x) {
            for (int z = (int)std::floor(-radius); z <= (int)std::ceil(radius); ++z) {
                if ((float)(x * x + z * z) <= (radius + 1.0f) * (radius + 1.0f))
                    setBlock(level, origin.offset(x, y, z), Blocks::END_STONE->defaultBlockState());
            }
        }
        radius -= (float)random.nextInt(2) + 0.5f;
    }
    return true;
}
