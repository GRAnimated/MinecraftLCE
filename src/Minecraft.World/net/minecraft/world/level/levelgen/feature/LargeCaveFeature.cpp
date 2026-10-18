#include "net/minecraft/world/level/levelgen/feature/LargeCaveFeature.h"

#include "net/minecraft/core/MutableBlockPos.h"
#include "net/minecraft/util/Mth.h"
#include "net/minecraft/world/level/Level.h"
#include "net/minecraft/world/level/biome/Biome.h"
#include "net/minecraft/world/level/block/Blocks.h"
#include "net/minecraft/world/level/block/LiquidBlock.h"
#include "net/minecraft/world/level/levelgen/ChunkPrimer.h"
#include "net/minecraft/world/level/material/LiquidMaterial.h"

// NON_MATCHING
void LargeCaveFeature::addTunnel(long long seed, int chunkX, int chunkZ, ChunkPrimer* primer, double x,
                                 double y, double z, float width, float yaw, float pitch, int startStep,
                                 int endStep, double verticalScale) {
    Random random(seed);
    if (endStep <= 0) {
        int range = m_radius * 16 - 16;
        endStep = range - random.nextInt(range / 4);
    }

    bool room = startStep == -1;
    int step = room ? endStep / 2 : startStep;
    int branchStep = random.nextInt(endStep / 2) + endStep / 4;
    bool steep = random.nextInt(6) == 0;
    float pitchVelocity = 0.0f;
    float yawVelocity = 0.0f;
    double centerX = chunkX * 16 + 8;
    double centerZ = chunkZ * 16 + 8;
    double reach = width + 2.0f + 16.0f;

    for (; step < endStep; step++) {
        double radius = 1.5 + Mth::sin(step * Mth::PI / endStep) * width;
        double radiusY = radius * verticalScale;
        float cosPitch = Mth::cos(pitch);
        float sinPitch = Mth::sin(pitch);
        x += cosPitch * Mth::cos(yaw);
        y += sinPitch;
        z += cosPitch * Mth::sin(yaw);

        pitch = (steep ? 0.92f : 0.7f) * pitch + pitchVelocity * 0.1f;
        yaw += yawVelocity * 0.1f;
        float pitchRandom1 = random.nextFloat();
        float pitchRandom2 = random.nextFloat();
        float pitchRandom3 = random.nextFloat();
        float yawRandom1 = random.nextFloat();
        float yawRandom2 = random.nextFloat();
        float yawRandom3 = random.nextFloat();

        if (!room && endStep > 0 && step == branchStep && width > 1.0f) {
            long long leftSeed = random.nextLong();
            float leftWidth = random.nextFloat() * 0.5f + 0.5f;
            addTunnel(leftSeed, chunkX, chunkZ, primer, x, y, z, leftWidth, yaw - Mth::PI / 2.0f,
                      pitch / 3.0f, step, endStep, 1.0);
            long long rightSeed = random.nextLong();
            float rightWidth = random.nextFloat() * 0.5f + 0.5f;
            addTunnel(rightSeed, chunkX, chunkZ, primer, x, y, z, rightWidth, yaw + Mth::PI / 2.0f,
                      pitch / 3.0f, step, endStep, 1.0);
            return;
        }

        if (room || random.nextInt(4) != 0) {
            double dx = x - centerX;
            double dz = z - centerZ;
            double remaining = endStep - step;
            if (dx * dx + dz * dz - remaining * remaining > reach * reach)
                return;

            if (x >= centerX - 16.0 - radius * 2.0 && z >= centerZ - 16.0 - radius * 2.0
                && x <= centerX + 16.0 + radius * 2.0 && z <= centerZ + 16.0 + radius * 2.0) {
                int minX = Mth::floor(x - radius) - chunkX * 16 - 1;
                int maxX = Mth::floor(x + radius) - chunkX * 16 + 1;
                int minY = Mth::floor(y - radiusY) - 1;
                int maxY = Mth::floor(y + radiusY) + 1;
                int minZ = Mth::floor(z - radius) - chunkZ * 16 - 1;
                int maxZ = Mth::floor(z + radius) - chunkZ * 16 + 1;
                if (minX < 0)
                    minX = 0;
                if (maxX > 16)
                    maxX = 16;
                if (minY < 1)
                    minY = 1;
                if (maxY > 120)
                    maxY = 120;
                if (minZ < 0)
                    minZ = 0;
                if (maxZ > 16)
                    maxZ = 16;

                bool water = false;
                for (int ix = minX; ix < maxX && !water; ix++) {
                    for (int iz = minZ; iz < maxZ && !water; iz++) {
                        for (int iy = maxY + 1; iy >= minY - 1; iy--) {
                            if (iy >= 0 && iy < 128) {
                                int id = primer->getBlockId((ix << 11) | (iz << 7) | iy);
                                if (id == 8 || id == 9) {
                                    water = true;
                                    break;
                                }
                                if (iy != minY - 1 && ix != minX && ix != maxX - 1 && iz != minZ
                                    && iz != maxZ - 1)
                                    iy = minY;
                            }
                        }
                    }
                }

                if (!water) {
                    MutableBlockPos pos(0, 0, 0);
                    Biome::LegacyBlockData lava(
                        11, Blocks::LAVA->convertBlockStateToLegacyData(Blocks::LAVA->defaultBlockState()));
                    Biome::LegacyBlockData air(0, 0);
                    for (int ix = minX; ix < maxX; ix++) {
                        double localX = (ix + chunkX * 16 + 0.5 - x) / radius;
                        for (int iz = minZ; iz < maxZ; iz++) {
                            double localZ = (iz + chunkZ * 16 + 0.5 - z) / radius;
                            if (localX * localX + localZ * localZ >= 1.0)
                                continue;

                            bool surface = false;
                            for (int iy = maxY - 1; iy >= minY; iy--) {
                                double localY = (iy + 0.5 - y) / radiusY;
                                if (localY <= -0.7
                                    || localZ * localZ + localX * localX + localY * localY >= 1.0)
                                    continue;

                                int packed = (ix << 11) | (iz << 7) | iy;
                                int id = primer->getBlockId(packed);
                                int above = primer->getBlockId(packed + 1);
                                if (id == 2 || id == 110)
                                    surface = true;
                                if (!canReplaceBlock(id, above))
                                    continue;

                                if (iy - 1 < 10) {
                                    primer->setBlockAndData(packed, lava.m_id, lava.m_data);
                                } else {
                                    primer->setBlockAndData(packed, air.m_id, air.m_data);
                                    if (surface && primer->getBlockId(packed - 1) == 3) {
                                        pos.set(ix + chunkX * 16, 0, iz + chunkZ * 16);
                                        Biome* biome = m_level->getBiome(pos);
                                        Block* block = Block::byId(biome->m_grass.m_id);
                                        int data = block->convertBlockStateToLegacyData(
                                            block->defaultBlockState());
                                        primer->setBlockAndData(packed - 1, biome->m_grass.m_id, data);
                                    }
                                }
                            }
                        }
                    }
                    if (room)
                        return;
                }
            }
        }

        float pitchChange = (pitchRandom1 - pitchRandom2) * pitchRandom3;
        pitchVelocity = pitchVelocity * 0.9f + pitchChange + pitchChange;
        yawVelocity = yawVelocity * 0.75f + (yawRandom1 - yawRandom2) * yawRandom3 * 4.0f;
    }
}

bool LargeCaveFeature::canReplaceBlock(int id, int above) {
    switch (id) {
    case 1:    // Stone
    case 2:    // Grass
    case 3:    // Dirt
    case 24:   // Sandstone
    case 78:   // Snow layer
    case 110:  // Mycelium
    case 159:  // Stained hardened clay
    case 172:  // Hardened clay
    case 179:  // Red sandstone
        return true;
    default:
        if (id == 12 || id == 13) {
            Block* block = Block::byId(above);
            return block && block->getMaterial() != Material::WATER;
        }
        return false;
    }
}

void LargeCaveFeature::addRoom(long long seed, int chunkX, int chunkZ, ChunkPrimer* primer, double x,
                               double y, double z) {
    float width = 1.0f + m_random.nextFloat() * 6.0f;
    addTunnel(seed, chunkX, chunkZ, primer, x, y, z, width, 0.0f, 0.0f, -1, -1, 0.5);
}

void LargeCaveFeature::addFeature(Level*, int sourceX, int sourceZ, int chunkX, int chunkZ,
                                  ChunkPrimer* primer) {
    int count = m_random.nextInt(m_random.nextInt(m_random.nextInt(40) + 1) + 1);
    if (m_random.nextInt(15) != 0)
        count = 0;

    for (int i = 0; i < count; i++) {
        double x = sourceX * 16 + m_random.nextInt(16);
        double y = m_random.nextInt(m_random.nextInt(120) + 8);
        double z = sourceZ * 16 + m_random.nextInt(16);
        int tunnels = 1;

        if (m_random.nextInt(4) == 0) {
            addRoom(m_random.nextLong(), chunkX, chunkZ, primer, x, y, z);
            tunnels += m_random.nextInt(4);
        }

        for (int j = 0; j < tunnels; j++) {
            float yaw = m_random.nextFloat() * Mth::PI * 2.0f;
            float pitch = (m_random.nextFloat() - 0.5f) * 2.0f / 8.0f;
            float width = m_random.nextFloat() * 2.0f + m_random.nextFloat();
            if (m_random.nextInt(10) == 0)
                width *= m_random.nextFloat() * m_random.nextFloat() * 3.0f + 1.0f;

            addTunnel(m_random.nextLong(), chunkX, chunkZ, primer, x, y, z, width, yaw, pitch, 0, 0, 1.0);
        }
    }
}
