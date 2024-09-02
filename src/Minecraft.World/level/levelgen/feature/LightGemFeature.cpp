#include "Minecraft.World/level/levelgen/feature/LightGemFeature.h"

#include "Minecraft.Core/BlockPos.h"
#include "Minecraft.Core/Direction.h"
#include "Minecraft.World/Random.h"
#include "Minecraft.World/level/Level.h"
#include "Minecraft.World/level/block/Blocks.h"
#include "Minecraft.World/level/block/state/BlockState.h"
#include "Minecraft.World/level/material/Material.h"

LightGemFeature::LightGemFeature() : Feature(false) {}

// NON_MATCHING
bool LightGemFeature::place(Level* level, Random& random, const BlockPos& pos) {
    if (!level->isEmptyBlock(pos)) {
        return false;
    }
    if (level->getBlockState(pos.above())->getBlock() != Blocks::NETHERRACK) {
        return false;
    }
    level->setBlock(pos, Blocks::GLOWSTONE->defaultBlockState(), 2, false);

    for (int i = 0; i < 1500; i++) {
        int random1 = random.nextInt(8) - random.nextInt(8);
        int random2 = -random.nextInt(12);
        int random3 = random.nextInt(8) - random.nextInt(8);

        BlockPos randomPos = pos.offset(random1, random2, random3);

        if (!(level->getBlockState(randomPos)->getMaterial() == (Material*)Material::AIR))
            continue;

        Direction* directions = Direction::DIRECTIONS[0];
        if (directions != Direction::END) {
            int glowstoneCount = 0;
            while (true) {
                Direction* test = directions++;
                if (level->getBlockState(randomPos.relative(test))->getBlock() == Blocks::GLOWSTONE) {
                    glowstoneCount++;
                }

                if (glowstoneCount > 1) {
                    break;
                }

                if (test == Direction::END) {
                    if (glowstoneCount == 1) {
                        level->setBlock(randomPos, Blocks::GLOWSTONE->defaultBlockState(), 2, false);
                    }
                }
            }
        }
    }
    return true;
}
