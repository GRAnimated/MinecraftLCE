#include "net/minecraft/world/level/levelgen/feature/LargeHellCaveFeature.h"

#include "net/minecraft/util/Mth.h"
#include "net/minecraft/world/level/block/Blocks.h"
#include "net/minecraft/world/level/block/state/BlockState.h"
#include "net/minecraft/world/level/levelgen/ChunkPrimer.h"

void LargeHellCaveFeature::addRoom(long long seed, int chunkX, int chunkZ, ChunkPrimer* primer, double x,
                                   double y, double z) {
    addTunnel(seed, chunkX, chunkZ, primer, x, y, z, m_random.nextFloat() * 6.0f + 1.0f, 0.0f, 0.0f, -1, -1,
              0.5);
}

void LargeHellCaveFeature::addTunnel(long long seed, int chunkX, int chunkZ, ChunkPrimer* primer, double x,
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

    for (; step < endStep; ++step) {
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

        if (!room && width > 1.0f && step == branchStep) {
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

                bool lava = false;
                for (int ix = minX; ix < maxX && !lava; ++ix) {
                    for (int iz = minZ; iz < maxZ && !lava; ++iz) {
                        for (int iy = maxY + 1; iy >= minY - 1; --iy) {
                            if (iy >= 0 && iy < 128) {
                                const BlockState* state = primer->getState(ix, iy, iz);
                                if (state->getBlock() == Blocks::FLOWING_LAVA
                                    || state->getBlock() == Blocks::LAVA) {
                                    lava = true;
                                    break;
                                }
                                if (iy != minY - 1 && ix != minX && ix != maxX - 1 && iz != minZ
                                    && iz != maxZ - 1)
                                    iy = minY;
                            }
                        }
                    }
                }
                if (!lava) {
                    for (int ix = minX; ix < maxX; ++ix) {
                        double localX = (ix + chunkX * 16 + 0.5 - x) / radius;
                        for (int iz = minZ; iz < maxZ; ++iz) {
                            double localZ = (iz + chunkZ * 16 + 0.5 - z) / radius;
                            for (int iy = maxY - 1; iy >= minY; --iy) {
                                double localY = (iy + 0.5 - y) / radiusY;
                                if (localY > -0.7
                                    && localZ * localZ + localX * localX + localY * localY < 1.0) {
                                    const BlockState* state = primer->getState(ix, iy, iz);
                                    if (state->getBlock() == Blocks::NETHERRACK
                                        || state->getBlock() == Blocks::DIRT
                                        || state->getBlock() == Blocks::GRASS)
                                        primer->setState(ix, iy, iz, Blocks::AIR->defaultBlockState());
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

void LargeHellCaveFeature::addFeature(Level*, int sourceX, int sourceZ, int chunkX, int chunkZ,
                                      ChunkPrimer* primer) {
    int count = m_random.nextInt(m_random.nextInt(m_random.nextInt(10) + 1) + 1);
    if (m_random.nextInt(5) != 0)
        count = 0;
    for (int i = 0; i < count; ++i) {
        double x = sourceX * 16 + m_random.nextInt(16);
        double y = m_random.nextInt(128);
        double z = sourceZ * 16 + m_random.nextInt(16);
        int tunnels = 1;
        if (m_random.nextInt(4) == 0) {
            addRoom(m_random.nextLong(), chunkX, chunkZ, primer, x, y, z);
            tunnels += m_random.nextInt(4);
        }
        for (int j = 0; j < tunnels; ++j) {
            float yaw = m_random.nextFloat() * Mth::PI * 2.0f;
            float pitch = (m_random.nextFloat() - 0.5f) * 2.0f * 0.125f;
            float width = (m_random.nextFloat() * 2.0f + m_random.nextFloat()) * 2.0f;
            addTunnel(m_random.nextLong(), chunkX, chunkZ, primer, x, y, z, width, yaw, pitch, 0, 0, 0.5);
        }
    }
}
