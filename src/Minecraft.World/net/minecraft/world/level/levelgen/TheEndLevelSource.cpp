#include "net/minecraft/world/level/levelgen/TheEndLevelSource.h"

#include "net/minecraft/util/Mth.h"
#include "net/minecraft/world/Random.h"
#include "net/minecraft/world/level/Level.h"
#include "net/minecraft/world/level/biome/BiomeSource.h"
#include "net/minecraft/world/level/block/Blocks.h"
#include "net/minecraft/world/level/block/state/BlockState.h"
#include "net/minecraft/world/level/chunk/LevelChunk.h"
#include "net/minecraft/world/level/levelgen/ChunkPrimer.h"
#include "net/minecraft/world/level/levelgen/feature/EndCityFeature.h"
#include "net/minecraft/world/level/levelgen/feature/EndIslandFeature.h"
#include "net/minecraft/world/level/levelgen/synth/PerlinNoise.h"
#include "net/minecraft/world/level/levelgen/synth/SimplexNoise.h"
#include "net/minecraft/world/level/material/GasMaterial.h"
#include "net/minecraft/world/level/material/Material.h"
#include <cmath>
#include <cstdlib>

// The names of these shared End constants are inferred; their Switch addresses are retained in the plan.
extern int endIslandCenters[5][2];
extern BlockPos endTerrainSpawn;
extern const std::wstring endCityFeatureName;
extern int endBiomeId(Biome*);
extern void endGenerateChorusPlant(Level*, BlockPos, Random*, int);

int endIslandDistance(int x, int z, const int* center) {
    int dx = std::abs(x - center[0]);
    int dz = std::abs(z - center[1]);
    return dx < dz ? dz : dx;
}

const int* endNearestIsland(int x, int z) {
    const int* nearest = endIslandCenters[0];
    unsigned distance = endIslandDistance(x, z, nearest);
    for (int i = 1; i < 5; ++i) {
        unsigned nextDistance = endIslandDistance(x, z, endIslandCenters[i]);
        if (nextDistance < distance) {
            distance = nextDistance;
            nearest = endIslandCenters[i];
        }
    }
    return nearest;
}

double endDistanceToSpawn(const Vec3i* pos, int x, int y, int z) {
    double dx = pos->getX() - x;
    double dy = pos->getY() - y;
    double dz = pos->getZ() - z;
    return std::sqrt(dx * dx + dy * dy + dz * dz);
}

TheEndLevelSource::TheEndLevelSource(Level* level, bool generateStructures, long long seed,
                                     const BlockPos& spawn) {
    m_size = 268;
    m_endCity = new EndCityFeature(this);
    m_random = new Random(seed);
    m_decorationRandom = new Random(seed);
    m_minLimitNoise = new PerlinNoise(m_random, 16);
    m_maxLimitNoise = new PerlinNoise(m_random, 16);
    m_mainNoise = new PerlinNoise(m_random, 8);
    m_scaleNoise = new PerlinNoise(m_random, 10);
    m_depthNoise = new PerlinNoise(m_random, 16);
    m_level = level;
    m_generateStructures = generateStructures;
    m_spawn = spawn;
    m_islandNoise = new SimplexNoise(m_random);
    m_islandFeature = new EndIslandFeature();
}

TheEndLevelSource::~TheEndLevelSource() {
    delete m_endCity;
    delete m_random;
    delete m_decorationRandom;
    delete m_minLimitNoise;
    delete m_maxLimitNoise;
    delete m_mainNoise;
    delete m_scaleNoise;
    delete m_depthNoise;
    delete m_islandNoise;
    delete m_islandFeature;
}

bool TheEndLevelSource::fjIslandCheck(int x, int z) {
    return fjIslandProximity(x, z) < 3.0;
}

double TheEndLevelSource::fjIslandProximity(int x, int z) {
    const int* island = endNearestIsland(x, z);
    if (island == endIslandCenters[0])
        return 12.0;
    double dx = (double)x + 0.5 - island[0];
    double dz = (double)z + 0.5 - island[1];
    dx = std::fabs(dx);
    dz = std::fabs(dz);
    return dx < dz ? dz : dx;
}

float TheEndLevelSource::getIslandHeightValue(int x, int z, int offsetX, int offsetZ) {
    const int* island = endNearestIsland(x, z);
    if (island == endIslandCenters[0]) {
        float dx = (float)x + (float)x + (float)offsetX;
        float dz = (float)z + (float)z + (float)offsetZ;
        return std::sqrt(dx * dx + dz * dz) * -9.0f + 100.0f;
    }
    int dx = x * 2 + offsetX;
    int dz = z * 2 + offsetZ;
    float height = std::sqrt((float)(dx * dx + dz * dz)) * -8.0f + 100.0f;
    if (height > 80.0f)
        height = 80.0f;
    if (height <= -100.0f)
        height = -100.0f;
    for (int ix = -4; ix <= 4; ++ix) {
        for (int iz = -4; iz <= 4; ++iz) {
            if (fjIslandCheck(x + ix, z + iz)) {
                double ax = std::fabs((double)(x + ix));
                double az = std::fabs((double)(z + iz));
                int scale = (int)(ax * 3439.0 + az * 147.0) % 6 + 18;
                int nx = offsetX - ix * 2;
                int nz = offsetZ - iz * 2;
                float candidate = 100.0f - std::sqrt((float)(nx * nx + nz * nz)) * (float)scale;
                if (candidate > 80.0f)
                    candidate = 80.0f;
                if (candidate <= -100.0f)
                    candidate = -100.0f;
                if (candidate > height)
                    height = candidate;
            }
        }
    }
    return height;
}

arrayWithLength<double> TheEndLevelSource::getHeights(arrayWithLength<double> result, int x, int y, int z,
                                                      int width, int height, int depth) {
    if (!result.m_data)
        result = arrayWithLength<double>(width * height * depth, true);
    arrayWithLength<double> main, low, high, scale, detail, unused1, unused2;
    scale = m_scaleNoise->getRegion(scale, x, z, width, depth, 1.121, 1.121, 0.5);
    detail = m_depthNoise->getRegion(detail, x, z, width, depth, 200.0, 200.0, 0.5);
    main = m_mainNoise->getRegion(main, x, y, z, width, height, depth, 17.110300000000002, 4.277575000000001,
                                  17.110300000000002);
    low = m_minLimitNoise->getRegion(low, x, y, z, width, height, depth, 1368.824, 684.412, 1368.824);
    high = m_maxLimitNoise->getRegion(high, x, y, z, width, height, depth, 1368.824, 684.412, 1368.824);
    unsigned index = 0;
    for (int ix = 0; ix < width; ++ix) {
        for (int iz = 0; iz < depth; ++iz) {
            float island = getIslandHeightValue(x / 2, z / 2, ix, iz);
            if (island > 80.0f)
                island = 80.0f;
            if (island <= -100.0f)
                island = -100.0f;
            for (int iy = 0; iy < height; ++iy, ++index) {
                double a = low[index] / 512.0;
                double b = high[index] / 512.0;
                double blend = (main[index] / 10.0 + 1.0) * 0.5;
                double density = a;
                // Unordered comparisons take the interpolation branch in the Switch routine.
                if (!(blend < 0.0)) {
                    density = b;
                    if (!(blend > 1.0))
                        density = a + (b - a) * blend;
                }
                density = (double)island + (density - 8.0);
                if (iy > height / 2 - 2) {
                    double falloff = Mth::clamp((double)((float)(iy - (height / 2 - 2)) / 64.0f), 0.0, 1.0);
                    density = density * (1.0 - falloff) + falloff * -3000.0;
                }
                if (iy < 8) {
                    double falloff = (double)((float)(8 - iy) / 7.0f);
                    density = (1.0 - falloff) * density + falloff * -30.0;
                }
                double distance
                    = endDistanceToSpawn(&endTerrainSpawn, (ix + x) * 8, (iy + y) * 4, (iz + z) * 8);
                double spawnBlend = Mth::clamp((19.0 - distance) / 16.0, 0.0, 1.0);
                double spawnDensity = endTerrainSpawn.getY() < ((iy + y) * 4 | 1) ? -50.0 : 50.0;
                result[index] = density * (1.0 - spawnBlend) + spawnBlend * spawnDensity;
            }
        }
    }
    delete[] main.m_data;
    delete[] low.m_data;
    delete[] high.m_data;
    delete[] scale.m_data;
    delete[] detail.m_data;
    delete[] unused1.m_data;
    delete[] unused2.m_data;
    return result;
}

void TheEndLevelSource::prepareHeights(int x, int z, ChunkPrimer* primer) {
    arrayWithLength<double> heights;
    heights = getHeights(heights, x * 2, 0, z * 2, 3, 33, 3);
    for (int ix = 0; ix < 2; ++ix) {
        for (int iz = 0; iz < 2; ++iz) {
            for (int iy = 0; iy < 32; ++iy) {
                int i00 = (ix * 3 + iz) * 33 + iy;
                int i01 = (ix * 3 + iz + 1) * 33 + iy;
                int i10 = ((ix + 1) * 3 + iz) * 33 + iy;
                int i11 = ((ix + 1) * 3 + iz + 1) * 33 + iy;
                double a = heights[i00], b = heights[i01], c = heights[i10], d = heights[i11];
                double da = (heights[i00 + 1] - a) * 0.25;
                double db = (heights[i01 + 1] - b) * 0.25;
                double dc = (heights[i10 + 1] - c) * 0.25;
                double dd = (heights[i11 + 1] - d) * 0.25;
                for (int dy = 0; dy < 4; ++dy) {
                    double p = a, q = b;
                    double dp = (c - a) * 0.125, dq = (d - b) * 0.125;
                    for (int dx = 0; dx < 8; ++dx) {
                        double value = p, step = (q - p) * 0.125;
                        for (int dz = 0; dz < 8; ++dz) {
                            const BlockState* state = Blocks::AIR->defaultBlockState();
                            if (value > 0.0)
                                state = Blocks::END_STONE->defaultBlockState();
                            primer->setState(ix * 8 + dx, iy * 4 + dy, iz * 8 + dz, state);
                            value += step;
                        }
                        p += dp;
                        q += dq;
                    }
                    a += da;
                    b += db;
                    c += dc;
                    d += dd;
                }
            }
        }
    }
    delete[] heights.m_data;
}

void TheEndLevelSource::buildSurfaces(ChunkPrimer* primer) {
    for (int x = 0; x < 16; ++x) {
        for (int z = 0; z < 16; ++z) {
            const BlockState* top = Blocks::END_STONE->defaultBlockState();
            const BlockState* filler = Blocks::END_STONE->defaultBlockState();
            int remaining = -1;
            for (int y = 127; y >= 0; --y) {
                const BlockState* state = primer->getState(x, y, z);
                if (state->getBlock()->getMaterial() == Material::AIR) {
                    remaining = -1;
                } else if (state->getBlock() == Blocks::STONE) {
                    if (remaining == -1) {
                        primer->setState(x, y, z, top);
                        remaining = 1;
                    } else if (remaining > 0) {
                        primer->setState(x, y, z, filler);
                        --remaining;
                    }
                }
            }
        }
    }
}

LevelChunk* TheEndLevelSource::createChunk(int x, int z) {
    m_random->setSeed((long long)x * 341873128712LL + (long long)z * 132897987541LL);
    arrayWithLength<unsigned char> ids(65536, true), data(32768, true);
    ChunkPrimer primer(true, ids, data);
    m_level->getBiomeSource()->getBiomeBlock(m_biomes, x << 4, z << 4, 16, 16, true);
    prepareHeights(x, z, &primer);
    buildSurfaces(&primer);
    if (m_generateStructures)
        m_endCity->apply(m_level, x, z, &primer);
    LevelChunk* chunk = new LevelChunk(m_level, &primer, x, z);
    arrayWithLength<unsigned char> biomes = chunk->getBiomes();
    for (unsigned i = 0; i < biomes.m_length; ++i)
        biomes[i] = endBiomeId(m_biomes.get(i));
    chunk->recalcHeightmap();
    return chunk;
}

void TheEndLevelSource::postProcess(int x, int z) {
    inPostProcessStep = true;
    BlockPos origin(x << 4, 0, z << 4);
    m_decorationRandom->setSeed(m_level->getSeed());
    long long a = m_decorationRandom->nextLong();
    if (a < 0)
        ++a;
    long long b = m_decorationRandom->nextLong();
    if (b < 0)
        ++b;
    m_decorationRandom->setSeed((x * (a | 1) + z * (b | 1)) ^ m_level->getSeed());
    if (m_generateStructures) {
        ChunkPos chunk(x, z);
        m_endCity->postProcess(m_level, *m_decorationRandom, &chunk);
    }
    m_level->getBiome(origin.offset(16, 0, 16))->decorate(m_level, *m_decorationRandom, origin);
    if (fjIslandCheck(x, z)) {
        if (getIslandHeightValue(x, z, 1, 1) < -20.0f && m_decorationRandom->nextInt(14) == 0) {
            int dx = m_decorationRandom->nextInt(16) + 8;
            int dy = m_decorationRandom->nextInt(16) + 55;
            int dz = m_decorationRandom->nextInt(16) + 8;
            m_islandFeature->place(m_level, *m_decorationRandom, origin.offset(dx, dy, dz));
            if (m_decorationRandom->nextInt(4) == 0) {
                dx = m_decorationRandom->nextInt(16) + 8;
                dy = m_decorationRandom->nextInt(16) + 55;
                dz = m_decorationRandom->nextInt(16) + 8;
                m_islandFeature->place(m_level, *m_decorationRandom, origin.offset(dx, dy, dz));
            }
        }
        if (getIslandHeightValue(x, z, 1, 1) > 40.0f) {
            int attempts = m_decorationRandom->nextInt(5);
            for (int i = 0; i < attempts; ++i) {
                int dx = m_decorationRandom->nextInt(16) + 8;
                int dz = m_decorationRandom->nextInt(16) + 8;
                int y = m_level->getHeightmapPos(origin.offset(dx, 0, dz)).getY();
                if (y > 0 && m_level->isEmptyBlock(origin.offset(dx, y, dz))
                    && m_level->getBlockState(origin.offset(dx, y - 1, dz))->getBlock() == Blocks::END_STONE)
                    endGenerateChorusPlant(m_level, origin.offset(dx, y, dz), m_decorationRandom, 8);
            }
        }
    }
    inPostProcessStep = false;
}

bool TheEndLevelSource::postProcessLoadedChunk(LevelChunk*, int, int) {
    return false;
}
std::vector<Biome::MobSpawnerData>* TheEndLevelSource::getMobsAt(MobCategory* category, const BlockPos& pos) {
    return m_level->getBiome(pos)->getMobs(category);
}
BlockPos* TheEndLevelSource::findNearestMapFeature(Level* level, const std::wstring& name,
                                                   const BlockPos& pos, bool unexplored) {
    if (endCityFeatureName == name && m_endCity)
        return m_endCity->getNearestGeneratedFeature(level, pos, unexplored);
    return nullptr;
}
bool TheEndLevelSource::isPosInFeature(Level*, const std::wstring& name, const BlockPos& pos) {
    return endCityFeatureName.compare(name) == 0 && m_endCity && m_endCity->isInsideFeature(pos);
}
void TheEndLevelSource::recreateLogicStructuresForChunk(LevelChunk*, int, int) {}
