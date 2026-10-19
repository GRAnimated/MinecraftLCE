#include "net/minecraft/world/level/levelgen/feature/IceSpikeFeature.h"

#include "net/minecraft/core/BlockPos.h"
#include "net/minecraft/util/Mth.h"
#include "net/minecraft/world/Random.h"
#include "net/minecraft/world/level/Level.h"
#include "net/minecraft/world/level/block/Blocks.h"
#include "net/minecraft/world/level/material/Material.h"
#include <cstdlib>

// name guessed
bool IceSpikeFeature::place(Level* level, Random& random, const BlockPos& origin) {
    BlockPos pos = origin;
    while (level->isEmptyBlock(pos) && pos.getY() > 2)
        pos = pos.below();
    if (level->getBlockState(pos)->getBlock() != Blocks::SNOW)
        return false;
    pos = pos.above(random.nextInt(4));
    int height = random.nextInt(4) + 7;
    int radius = height / 4 + random.nextInt(2);
    if (radius > 1 && random.nextInt(60) == 0)
        pos = pos.above(random.nextInt(30) + 10);
    for (int y = 0; y < height; ++y) {
        float width = (1.0f - static_cast<float>(y) / height) * static_cast<float>(radius);
        int extent = Mth::ceil(width);
        for (int x = -extent; x <= extent; ++x) {
            float dx = static_cast<float>(Mth::abs(x)) - 0.25f;
            for (int z = -extent; z <= extent; ++z) {
                float dz = static_cast<float>(Mth::abs(z)) - 0.25f;
                if ((x == 0 && z == 0) || !(dx * dx + dz * dz > width * width)) {
                    if ((x != -extent && x != extent && z != -extent && z != extent)
                        || !(random.nextFloat() > 0.75f)) {
                        const BlockState* state = level->getBlockState(pos.offset(x, y, z));
                        Block* block = state->getBlock();
                        if (state->getMaterial() == Material::AIR || block == Blocks::DIRT
                            || block == Blocks::SNOW || block == Blocks::ICE)
                            setBlock(level, pos.offset(x, y, z), Blocks::PACKED_ICE->defaultBlockState());
                        if (y != 0 && extent > 1) {
                            state = level->getBlockState(pos.offset(x, -y, z));
                            block = state->getBlock();
                            if (state->getMaterial() == Material::AIR || block == Blocks::DIRT
                                || block == Blocks::SNOW || block == Blocks::ICE)
                                setBlock(level, pos.offset(x, -y, z),
                                         Blocks::PACKED_ICE->defaultBlockState());
                        }
                    }
                }
            }
        }
    }
    int rootRadius = radius - 1;
    if (rootRadius < 0)
        rootRadius = 0;
    else if (rootRadius > 1)
        rootRadius = 1;
    for (int x = -rootRadius; x <= rootRadius; ++x) {
        for (int z = -rootRadius; z <= rootRadius; ++z) {
            BlockPos root = pos.offset(x, -1, z);
            int remaining = 50;
            if (std::abs(x) == 1 && std::abs(z) == 1)
                remaining = random.nextInt(5);
            while (root.getY() > 50) {
                const BlockState* state = level->getBlockState(root);
                Block* block = state->getBlock();
                if (state->getMaterial() != Material::AIR && block != Blocks::DIRT && block != Blocks::SNOW
                    && block != Blocks::ICE && block != Blocks::PACKED_ICE)
                    break;
                setBlock(level, root, Blocks::PACKED_ICE->defaultBlockState());
                root = root.below();
                if (--remaining <= 0) {
                    root = root.below(random.nextInt(5) + 1);
                    remaining = random.nextInt(5);
                }
            }
        }
    }
    return true;
}
