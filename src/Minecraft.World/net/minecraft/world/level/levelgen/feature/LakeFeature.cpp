#include "net/minecraft/world/level/levelgen/feature/LakeFeature.h"

#include "net/minecraft/client/CMinecraftApp.h"
#include "net/minecraft/core/BlockPos.h"
#include "net/minecraft/world/Random.h"
#include "net/minecraft/world/level/Level.h"
#include "net/minecraft/world/level/biome/Biome.h"
#include "net/minecraft/world/level/block/Blocks.h"
#include "net/minecraft/world/level/block/state/BlockState.h"
#include "net/minecraft/world/level/material/Material.h"
#include <cstring>

LakeFeature::LakeFeature(Block* block) : Feature(false), m_block(block) {}

// NON_MATCHING | score: 5010 (lower is better)
bool LakeFeature::place(Level* level, Random& random, const BlockPos& pos) {
    BlockPos origin = pos.offset(-8, 0, -8);
    while (origin.getY() >= 6 && level->isEmptyBlock(origin))
        origin = origin.below();
    if (origin.getY() < 5)
        return false;
    origin = origin.below(4);

    bool cavity[16 * 16 * 8];
    std::memset(cavity, 0, sizeof(cavity));
    if (CConsoleMinecraftApp::sInstance.getLevelGenerationOptions()) {
        LevelGenerationOptions* options = CConsoleMinecraftApp::sInstance.getLevelGenerationOptions();
        BlockPos lower(origin.getX(), origin.getY(), origin.getZ());
        BlockPos upper(origin.getX() + 16, origin.getY() + 8, origin.getZ() + 16);
        if (options->intersects(lower, upper))
            return false;
    }

    int ellipsoids = random.nextInt(4) + 4;
    for (int i = 0; i < ellipsoids; ++i) {
        double sizeX = random.nextDouble() * 6.0 + 3.0;
        double sizeY = random.nextDouble() * 4.0 + 2.0;
        double sizeZ = random.nextDouble() * 6.0 + 3.0;
        double centerX = sizeX * 0.5 + random.nextDouble() * (16.0 - sizeX - 2.0) + 1.0;
        double centerY = sizeY * 0.5 + random.nextDouble() * (8.0 - sizeY - 4.0) + 2.0;
        double centerZ = sizeZ * 0.5 + random.nextDouble() * (16.0 - sizeZ - 2.0) + 1.0;
        for (int x = 1; x < 15; ++x) {
            double dx = (x - centerX) / (sizeX * 0.5);
            for (int z = 1; z < 15; ++z) {
                double dz = (z - centerZ) / (sizeZ * 0.5);
                for (int y = 1; y < 7; ++y) {
                    double dy = (y - centerY) / (sizeY * 0.5);
                    if (dz * dz + dx * dx + dy * dy < 1.0)
                        cavity[(x * 16 + z) * 8 + y] = true;
                }
            }
        }
    }

    // Validate the complete boundary before the first world write.
    for (int x = 0; x < 16; ++x) {
        for (int z = 0; z < 16; ++z) {
            for (int y = 0; y < 8; ++y) {
                int index = (x * 16 + z) * 8 + y;
                bool boundary = !cavity[index]
                                && ((x < 15 && cavity[index + 128]) || (x > 0 && cavity[index - 128])
                                    || (z < 15 && cavity[index + 8]) || (z > 0 && cavity[index - 8])
                                    || (y < 7 && cavity[index + 1]) || (y > 0 && cavity[index - 1]));
                if (boundary) {
                    Material* material = level->getBlockState(origin.offset(x, y, z))->getMaterial();
                    if (y >= 4) {
                        if (material->isLiquid())
                            return false;
                    } else if (!material->isSolid()
                               && level->getBlockState(origin.offset(x, y, z))->getBlock() != m_block) {
                        return false;
                    }
                }
            }
        }
    }

    for (int x = 0; x < 16; ++x) {
        for (int z = 0; z < 16; ++z) {
            for (int y = 0; y < 8; ++y) {
                if (cavity[(x * 16 + z) * 8 + y])
                    level->setBlock(origin.offset(x, y, z),
                                    (y >= 4 ? Blocks::AIR : m_block)->defaultBlockState(), 2, false);
            }
        }
    }

    for (int x = 0; x < 16; ++x) {
        for (int z = 0; z < 16; ++z) {
            for (int y = 4; y < 8; ++y) {
                if (cavity[(x * 16 + z) * 8 + y]) {
                    BlockPos below = origin.offset(x, y - 1, z);
                    if (level->getBlockState(below)->getBlock() == Blocks::DIRT
                        && level->getBrightness(LightLayer::SKY, origin.offset(x, y, z)) > 0) {
                        // The field at 0x58 is the biome's top-block ID, not its biome ID.
                        Block* top
                            = level->getBiome(below)->m_grass.m_id == 110 ? Blocks::MYCELIUM : Blocks::GRASS;
                        level->setBlock(below, top->defaultBlockState(), 2, false);
                    }
                }
            }
        }
    }

    if (m_block->defaultBlockState()->getMaterial() == Material::LAVA) {
        for (int x = 0; x < 16; ++x) {
            for (int z = 0; z < 16; ++z) {
                for (int y = 0; y < 8; ++y) {
                    int index = (x * 16 + z) * 8 + y;
                    bool boundary = !cavity[index]
                                    && ((x < 15 && cavity[index + 128]) || (x > 0 && cavity[index - 128])
                                        || (z < 15 && cavity[index + 8]) || (z > 0 && cavity[index - 8])
                                        || (y < 7 && cavity[index + 1]) || (y > 0 && cavity[index - 1]));
                    if (boundary && (y < 4 || random.nextInt(2) != 0)
                        && level->getBlockState(origin.offset(x, y, z))->getMaterial()->isSolid()) {
                        level->setBlock(origin.offset(x, y, z), Blocks::STONE->defaultBlockState(), 2, false);
                    }
                }
            }
        }
    }
    if (m_block->defaultBlockState()->getMaterial() == Material::WATER) {
        for (int x = 0; x < 16; ++x) {
            for (int z = 0; z < 16; ++z) {
                if (level->shouldFreezeIgnoreNeighbors(origin.offset(x, 4, z)))
                    level->setBlock(origin.offset(x, 4, z), Blocks::ICE->defaultBlockState(), 2, false);
            }
        }
    }
    return true;
}
