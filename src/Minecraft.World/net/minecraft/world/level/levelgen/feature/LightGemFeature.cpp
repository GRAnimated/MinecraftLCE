#include "net/minecraft/world/level/levelgen/feature/LightGemFeature.h"

#include "net/minecraft/core/BlockPos.h"
#include "net/minecraft/core/Direction.h"
#include "net/minecraft/world/Random.h"
#include "net/minecraft/world/level/Level.h"
#include "net/minecraft/world/level/block/Blocks.h"
#include "net/minecraft/world/level/block/state/BlockState.h"
#include "net/minecraft/world/level/material/Material.h"

LightGemFeature::LightGemFeature() : Feature(false) {}

bool LightGemFeature::place(Level* level, Random& random, const BlockPos& pos) {
    if (!level->isEmptyBlock(pos)) {
        return false;
    }
    if (level->getBlockState(pos.above())->getBlock() != Blocks::NETHERRACK) {
        return false;
    }
    level->setBlock(pos, Blocks::GLOWSTONE->defaultBlockState(), 2, false);

    for (int i = 0; i < 1500; i++) {
        BlockPos randomPos = pos.offset(random.nextInt(8) - random.nextInt(8), -random.nextInt(12),
                                        random.nextInt(8) - random.nextInt(8));

        if (level->getBlockState(randomPos)->getMaterial() == (Material*)Material::AIR) {
            int glowstoneCount = 0;

            for (auto it = Direction::VALUES.begin(); it != Direction::VALUES.end(); ++it) {
                const Direction* direction = *it;
                if (level->getBlockState(randomPos.relative(direction))->getBlock() == Blocks::GLOWSTONE)
                    glowstoneCount++;

                if (glowstoneCount > 1) {
                    break;
                }
            }
            if (glowstoneCount == 1) {
                level->setBlock(randomPos, Blocks::GLOWSTONE->defaultBlockState(), 2, false);
            }
        }
    }
    return true;
}
