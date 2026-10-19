#include "net/minecraft/world/level/levelgen/feature/CanyonFeature.h"

#include "NX/Platform.h"
#include "net/minecraft/client/CMinecraftApp.h"
#include "net/minecraft/core/MutableBlockPos.h"
#include "net/minecraft/util/Mth.h"
#include "net/minecraft/world/level/Level.h"
#include "net/minecraft/world/level/biome/Biome.h"
#include "net/minecraft/world/level/block/Blocks.h"
#include "net/minecraft/world/level/block/state/BlockState.h"
#include "net/minecraft/world/level/levelgen/ChunkPrimer.h"

// name guessed
// NON_MATCHING | score: 31717 (lower is better)
void CanyonFeature::addTunnel(long long seed, int chunkX, int chunkZ, ChunkPrimer* primer, double x, double y,
                              double z, float width, float yaw, float pitch, int startStep, int endStep,
                              double verticalScale) {
    MemSect(49);
    Random random(seed);
    MemSect(0);
    if (endStep <= 0) {
        int range = m_radius * 16 - 16;
        endStep = range - random.nextInt(range / 4);
    }

    float heightWidth = 1.0f;
    for (int i = 0; i < 128; i++) {
        if (i == 0 || random.nextInt(3) == 0) {
            float first = random.nextFloat();
            heightWidth = first * random.nextFloat() + 1.0f;
        }
        m_widths[i] = heightWidth * heightWidth;
    }

    bool room = startStep == -1;
    int step = room ? endStep / 2 : startStep;
    float pitchVelocity = 0.0f;
    float yawVelocity = 0.0f;
    double centerX = chunkX * 16 + 8;
    double centerZ = chunkZ * 16 + 8;
    double reach = width + 2.0f + 16.0f;

    for (; step < endStep; step++) {
        double radius = 1.5 + Mth::sin(step * Mth::PI / endStep) * width;
        double radiusY = radius * verticalScale;
        radius *= double(random.nextFloat()) * 0.25 + 0.75;
        radiusY *= double(random.nextFloat()) * 0.25 + 0.75;
        float cosPitch = Mth::cos(pitch);
        float sinPitch = Mth::sin(pitch);
        x += cosPitch * Mth::cos(yaw);
        y += sinPitch;
        z += cosPitch * Mth::sin(yaw);

        float pitchRandom1 = random.nextFloat();
        float pitchRandom2 = random.nextFloat();
        float pitchRandom3 = random.nextFloat();
        float yawRandom1 = random.nextFloat();
        float yawRandom2 = random.nextFloat();
        float yawRandom3 = random.nextFloat();

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
                                const BlockState* state = primer->getState(ix, iy, iz);
                                if (state->getBlock() == Blocks::FLOWING_WATER
                                    || state->getBlock() == Blocks::WATER) {
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
                    MutableBlockPos pos;
                    Biome::LegacyBlockData lava(10, Blocks::FLOWING_LAVA->convertBlockStateToLegacyData(
                                                        Blocks::FLOWING_LAVA->defaultBlockState()));
                    Biome::LegacyBlockData air(0, 0);
                    for (int ix = minX; ix < maxX; ix++) {
                        double localX = (ix + chunkX * 16 + 0.5 - x) / radius;
                        for (int iz = minZ; iz < maxZ; iz++) {
                            double localZ = (iz + chunkZ * 16 + 0.5 - z) / radius;
                            double horizontal = localX * localX + localZ * localZ;
                            if (horizontal >= 1.0)
                                continue;

                            bool surface = false;
                            for (int iy = maxY - 1; iy >= minY; iy--) {
                                double localY = (iy + 0.5 - y) / radiusY;
                                if (horizontal * m_widths[iy] + localY * localY / 6.0 >= 1.0)
                                    continue;

                                const BlockState* state = primer->getState(ix, iy, iz);
                                surface = surface || state->getBlock() == Blocks::GRASS;
                                if (state->getBlock() != Blocks::STONE && state->getBlock() != Blocks::DIRT
                                    && state->getBlock() != Blocks::GRASS)
                                    continue;

                                int packed = (ix << 11) | (iz << 7) | iy;
                                if (iy - 1 < 10) {
                                    primer->setBlockAndData(packed, lava.m_id, lava.m_data);
                                } else {
                                    primer->setBlockAndData(packed, air.m_id, air.m_data);
                                    if (surface) {
                                        if (primer->getState(ix, iy - 1, iz)->getBlock() == Blocks::DIRT) {
                                            pos.set(ix + chunkX * 16, 0, iz + chunkZ * 16);
                                            Biome* biome = m_level->getBiome(pos);
                                            primer->setBlockAndData(packed - 1, biome->m_grass.m_id,
                                                                    biome->m_grass.m_data);
                                        }
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

        pitch = pitch * 0.7f + pitchVelocity * 0.05f;
        yaw += yawVelocity * 0.05f;
        float pitchChange = (pitchRandom1 - pitchRandom2) * pitchRandom3;
        pitchVelocity = pitchVelocity * 0.8f + pitchChange + pitchChange;
        yawVelocity = yawVelocity * 0.5f + (yawRandom1 - yawRandom2) * yawRandom3 * 4.0f;
    }
}

// name guessed
void CanyonFeature::addFeature(Level*, int sourceX, int sourceZ, int chunkX, int chunkZ,
                               ChunkPrimer* primer) {
    if (m_random.nextInt(50) != 0)
        return;

    double x = sourceX * 16 + m_random.nextInt(16);
    double y = m_random.nextInt(m_random.nextInt(40) + 8) + 20;
    double z = sourceZ * 16 + m_random.nextInt(16);
    int markerX = int(x * 0.0625);
    int markerZ = int(y * 0.0625);
    float yaw = m_random.nextFloat() * Mth::PI * 2.0f;
    float pitch = (m_random.nextFloat() - 0.5f) * 2.0f * 0.125f;
    float firstWidth = m_random.nextFloat() * 2.0f;
    float width = (firstWidth + m_random.nextFloat()) * 2.0f;
    addTunnel(m_random.nextLong(), chunkX, chunkZ, primer, x, y, z, width, yaw, pitch, 0, 0, 3.0);
    // The reference registers X/Y here, although the marker service accepts X/Z.
    CConsoleMinecraftApp::sInstance.addGeneratedFeature(4, markerX, markerZ);
}
