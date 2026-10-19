#include "net/minecraft/world/level/levelgen/NetherLevelSource.h"

#include "NX/Platform.h"
#include "net/minecraft/client/CMinecraftApp.h"
#include "net/minecraft/core/BlockPos.h"
#include "net/minecraft/util/Mth.h"
#include "net/minecraft/world/entity/MobCategory.h"
#include "net/minecraft/world/level/Level.h"
#include "net/minecraft/world/level/block/Blocks.h"
#include "net/minecraft/world/level/block/Bush.h"
#include "net/minecraft/world/level/chunk/LevelChunk.h"
#include "net/minecraft/world/level/levelgen/ChunkPrimer.h"
#include "net/minecraft/world/level/levelgen/feature/BushFeature.h"
#include "net/minecraft/world/level/levelgen/feature/HellFireFeature.h"
#include "net/minecraft/world/level/levelgen/feature/HellPortalFeature.h"
#include "net/minecraft/world/level/levelgen/feature/HellSpringFeature.h"
#include "net/minecraft/world/level/levelgen/feature/LargeHellCaveFeature.h"
#include "net/minecraft/world/level/levelgen/feature/LightGemFeature.h"
#include "net/minecraft/world/level/levelgen/feature/NetherBridgeFeature.h"
#include "net/minecraft/world/level/levelgen/feature/OreFeature.h"
#include "net/minecraft/world/level/levelgen/synth/PerlinNoise.h"
#include "net/minecraft/world/level/material/Material.h"
#include "net/minecraft/world/level/storage/LevelData.h"
#include <cmath>

class FjNetherrackBlockPred : public Predicate<const Biome::LegacyBlockData&> {
public:
    bool apply(const Biome::LegacyBlockData&) const override;
    ~FjNetherrackBlockPred() override;
};

// name guessed
// NON_MATCHING | score: 1525 (lower is better)
bool FjNetherrackBlockPred::apply(const Biome::LegacyBlockData& block) const {
    static int id = Block::getId(Blocks::NETHERRACK);
    return block.m_id == id;
}
// name guessed
// NON_MATCHING | score: 200 (lower is better)
FjNetherrackBlockPred::~FjNetherrackBlockPred() {}
const std::wstring NetherLevelSource::FORTRESS_NAME = L"Fortress";  // name guessed
const FjNetherrackBlockPred NetherLevelSource::NETHERRACK_PREDICATE;

NetherLevelSource::NetherLevelSource(Level* level, bool generateStructures, long long seed) {
    int size = level->getLevelData()->getXZSize();
    int hellScale = level->getLevelData()->getHellScale();
    m_size = static_cast<int>(std::ceil(static_cast<float>(size) / hellScale));
    m_level = level;
    m_generateStructures = generateStructures;
    m_random = Random(seed);
    m_populationRandom = Random(seed);
    m_minLimitNoise = new PerlinNoise(&m_random, 16);
    m_maxLimitNoise = new PerlinNoise(&m_random, 16);
    m_mainNoise = new PerlinNoise(&m_random, 8);
    m_soulSandNoise = new PerlinNoise(&m_random, 4);
    m_surfaceNoise = new PerlinNoise(&m_random, 4);
    m_scaleNoise = new PerlinNoise(&m_random, 10);
    m_depthNoise = new PerlinNoise(&m_random, 16);
    level->setSeaLevel(63);
    m_fire = new HellFireFeature();
    m_glowstone = new LightGemFeature();
    m_portal = new HellPortalFeature();
    m_quartz = new OreFeature(Blocks::QUARTZ_ORE->defaultBlockState(), 14, &NETHERRACK_PREDICATE);
    m_magma = new OreFeature(Blocks::MAGMA->defaultBlockState(), 33, &NETHERRACK_PREDICATE);
    m_enclosedLava = new HellSpringFeature(Blocks::FLOWING_LAVA, true);
    m_openLava = new HellSpringFeature(Blocks::FLOWING_LAVA, false);
    m_brownMushroom = new BushFeature(static_cast<Bush*>(Blocks::BROWN_MUSHROOM));
    m_redMushroom = new BushFeature(static_cast<Bush*>(Blocks::RED_MUSHROOM));
    m_fortress = new NetherBridgeFeature();
    m_caves = new LargeHellCaveFeature();
}

NetherLevelSource::~NetherLevelSource() {
    delete m_minLimitNoise;
    delete m_maxLimitNoise;
    delete m_mainNoise;
    delete m_soulSandNoise;
    delete m_surfaceNoise;
    delete m_scaleNoise;
    delete m_depthNoise;
    delete m_fire;
    delete m_glowstone;
    delete m_portal;
    delete m_quartz;
    delete m_magma;
    delete m_enclosedLava;
    delete m_openLava;
    delete m_brownMushroom;
    delete m_redMushroom;
    delete m_fortress;
    delete m_caves;
}

// name guessed
arrayWithLength<double> NetherLevelSource::getHeights(arrayWithLength<double> output, int x, int y, int z,
                                                      int sizeX, int sizeY, int sizeZ) {
    if (!output.m_data)
        output = arrayWithLength<double>(sizeX * sizeY * sizeZ, true);
    arrayWithLength<double> main, lower, upper, scale, depth, unused1, unused2;
    scale = m_scaleNoise->getRegion(scale, x, y, z, sizeX, 1, sizeZ, 1.0, 0.0, 1.0);
    depth = m_depthNoise->getRegion(depth, x, y, z, sizeX, 1, sizeZ, 100.0, 0.0, 100.0);
    main = m_mainNoise->getRegion(main, x, y, z, sizeX, sizeY, sizeZ, 684.412 / 80.0, 2053.236 / 60.0,
                                  684.412 / 80.0);
    lower = m_minLimitNoise->getRegion(lower, x, y, z, sizeX, sizeY, sizeZ, 684.412, 2053.236, 684.412);
    upper = m_maxLimitNoise->getRegion(upper, x, y, z, sizeX, sizeY, sizeZ, 684.412, 2053.236, 684.412);
    arrayWithLength<double> falloff(sizeY, true);
    for (int i = 0; i < sizeY; ++i) {
        falloff[i] = std::cos(static_cast<double>(i * Mth::PI * 6.0f) / sizeY) * 2.0;
        int edge = i;
        if (i > sizeY / 2)
            edge = sizeY - 1 - i;
        if (edge < 4) {
            double distance = 4.0 - edge;
            falloff[i] -= distance * distance * distance * 10.0;
        }
    }
    int index = 0;
    for (int dx = 0; dx < sizeX; ++dx) {
        for (int dz = 0; dz < sizeZ; ++dz) {
            for (int dy = 0; dy < sizeY; ++dy) {
                double vertical = falloff[dy];
                double min = lower[index] / 512.0;
                double max = upper[index] / 512.0;
                double blend = (main[index] / 10.0 + 1.0) * 0.5;
                double value;
                if (blend < 0.0)
                    value = min;
                else if (blend > 1.0)
                    value = max;
                else
                    value = min + (max - min) * blend;
                value -= vertical;
                if (dy > sizeY - 4) {
                    double fade = static_cast<float>(dy - (sizeY - 4)) / 3.0f;
                    value = value * (1.0 - fade) + -10.0 * fade;
                }
                output[index++] = value;
            }
        }
    }
    delete[] main.m_data;
    delete[] lower.m_data;
    delete[] upper.m_data;
    delete[] scale.m_data;
    delete[] depth.m_data;
    delete[] unused1.m_data;
    delete[] unused2.m_data;
    delete[] falloff.m_data;
    return output;
}

// NON_MATCHING | score: 4375 (lower is better)
void NetherLevelSource::prepareHeights(int chunkX, int chunkZ, ChunkPrimer* primer) {
    int lavaHeight = m_level->getSeaLevel() / 2;
    arrayWithLength<double> density;
    density = getHeights(density, chunkX * 4, 0, chunkZ * 4, 5, 17, 5);
    for (int x = 0; x < 4; ++x) {
        for (int z = 0; z < 4; ++z) {
            for (int y = 0; y < 16; ++y) {
                int a = (x * 5 + z) * 17 + y;
                int b = (x * 5 + z + 1) * 17 + y;
                int c = ((x + 1) * 5 + z) * 17 + y;
                int d = ((x + 1) * 5 + z + 1) * 17 + y;
                double aa = density[a], bb = density[b], cc = density[c], dd = density[d];
                double da = (density[a + 1] - aa) * 0.125;
                double db = (density[b + 1] - bb) * 0.125;
                double dc = (density[c + 1] - cc) * 0.125;
                double de = (density[d + 1] - dd) * 0.125;
                for (int dy = 0; dy < 8; ++dy) {
                    double stepA = (cc - aa) * 0.25;
                    double stepB = (dd - bb) * 0.25;
                    double atA = aa, atB = bb;
                    for (int dx = 0; dx < 4; ++dx) {
                        double step = (atB - atA) * 0.25;
                        double value = atA;
                        for (int dz = 0; dz < 4; ++dz) {
                            const BlockState* state = nullptr;
                            if (y * 8 + dy <= lavaHeight)
                                state = Blocks::LAVA->defaultBlockState();
                            if (value > 0.0)
                                state = Blocks::NETHERRACK->defaultBlockState();
                            primer->setState(x * 4 + dx, y * 8 + dy, z * 4 + dz, state);
                            value += step;
                        }
                        atA += stepA;
                        atB += stepB;
                    }
                    aa += da;
                    bb += db;
                    cc += dc;
                    dd += de;
                }
            }
        }
    }
    delete[] density.m_data;
}

// NON_MATCHING | score: 2790 (lower is better)
void NetherLevelSource::buildSurfaces(int chunkX, int chunkZ, ChunkPrimer* primer) {
    int seaLevel = m_level->getSeaLevel();
    arrayWithLength<double> soul(256, true), gravel(256, true), thickness(256, true);
    soul = m_soulSandNoise->getRegion(soul, chunkX * 16, chunkZ * 16, 0, 16, 16, 1, 0.03125, 0.03125, 1.0);
    gravel
        = m_soulSandNoise->getRegion(gravel, chunkX * 16, 109, chunkZ * 16, 16, 1, 16, 0.03125, 1.0, 0.03125);
    thickness = m_surfaceNoise->getRegion(thickness, chunkX * 16, chunkZ * 16, 0, 16, 16, 1, 0.0625, 0.0625,
                                          0.0625);
    for (int x = 0; x < 16; ++x) {
        for (int z = 0; z < 16; ++z) {
            bool soulSand = soul[x + z * 16] + m_random.nextDouble() * 0.2 > 0.0;
            bool gravelPatch = gravel[x + z * 16] + m_random.nextDouble() * 0.2 > 0.0;
            int depth = static_cast<int>(thickness[x + z * 16] / 3.0 + 3.0 + m_random.nextDouble() * 0.25);
            const BlockState* top = Blocks::NETHERRACK->defaultBlockState();
            const BlockState* filler = Blocks::NETHERRACK->defaultBlockState();
            int remaining = -1;
            for (int y = 127; y >= 0; --y) {
                int index = (x * 16 + z) * 128 + y;
                bool wall = false;
                if (chunkX <= -m_size / 2 && (x <= m_random.nextInt(4) || chunkX < -m_size / 2)) {
                    primer->setState(index, Blocks::BEDROCK->defaultBlockState());
                    wall = true;
                }
                if (chunkZ <= -m_size / 2 && (z <= m_random.nextInt(4) || chunkZ < -m_size / 2)) {
                    primer->setState(index, Blocks::BEDROCK->defaultBlockState());
                    wall = true;
                }
                if (chunkX >= m_size / 2 - 1 && (x + m_random.nextInt(4) >= 15 || chunkX > m_size / 2)) {
                    primer->setState(index, Blocks::BEDROCK->defaultBlockState());
                    wall = true;
                }
                if (chunkZ >= m_size / 2 - 1 && (z + m_random.nextInt(4) >= 15 || chunkZ > m_size / 2)) {
                    primer->setState(index, Blocks::BEDROCK->defaultBlockState());
                } else if (!wall) {
                    if (y >= 127 - m_random.nextInt(5) || y <= m_random.nextInt(5)) {
                        primer->setState(index, Blocks::BEDROCK->defaultBlockState());
                        continue;
                    }
                    const BlockState* state = primer->getState(index);
                    if (!state->getBlock() || state->getBlock()->getMaterial() == Material::AIR) {
                        remaining = -1;
                    } else if (state->getBlock() == Blocks::NETHERRACK) {
                        if (remaining == -1) {
                            if (depth < 1) {
                                top = Blocks::AIR->defaultBlockState();
                                filler = Blocks::NETHERRACK->defaultBlockState();
                            } else if (y >= seaLevel - 3 && y <= seaLevel + 2) {
                                top = Blocks::NETHERRACK->defaultBlockState();
                                filler = Blocks::NETHERRACK->defaultBlockState();
                                if (gravelPatch) {
                                    top = Blocks::GRAVEL->defaultBlockState();
                                    filler = Blocks::NETHERRACK->defaultBlockState();
                                }
                                if (soulSand) {
                                    top = Blocks::SOUL_SAND->defaultBlockState();
                                    filler = Blocks::SOUL_SAND->defaultBlockState();
                                    if (m_random.nextInt(16) == 0) {
                                        int above = (x * 16 + z) * 128 + (y + 1 < 127 ? y + 1 : 127);
                                        if (primer->getState(above)->getBlock() != Blocks::BEDROCK)
                                            primer->setState(above, Blocks::NETHER_WART->defaultBlockState());
                                    }
                                }
                            }
                            if (y <= seaLevel && (!top || top->getMaterial() == Material::AIR))
                                top = Blocks::LAVA->defaultBlockState();
                            remaining = depth;
                            const BlockState* surface = !soulSand && y < seaLevel ? filler : top;
                            if (primer->getState(index)->getBlock() != Blocks::BEDROCK)
                                primer->setState(index, surface);
                        } else if (remaining > 0) {
                            --remaining;
                            if (primer->getState(z, y, x)->getBlock() != Blocks::BEDROCK)
                                primer->setState(z, y, x, filler);
                        }
                    }
                }
            }
        }
    }
    delete[] soul.m_data;
    delete[] gravel.m_data;
    delete[] thickness.m_data;
}

LevelChunk* NetherLevelSource::createChunk(int x, int z) {
    m_random.setSeed(341873128712LL * x + 132897987541LL * z);
    void* ids = XPhysicalAlloc(0x8000, -1LL, 0x1000, 4);
    XMemSet128(ids, 0, 0x8000);
    arrayWithLength<uchar> blockIds(static_cast<uchar*>(ids), 0x8000);
    void* data = XPhysicalAlloc(0x4000, -1LL, 0x1000, 4);
    XMemSet128(data, 0, 0x4000);
    arrayWithLength<uchar> blockData(static_cast<uchar*>(data), 0x4000);
    ChunkPrimer primer(false, blockIds, blockData);
    prepareHeights(x, z, &primer);
    buildSurfaces(x, z, &primer);
    m_caves->apply(m_level, x, z, &primer);
    if (m_generateStructures)
        m_fortress->apply(m_level, x, z, &primer);
    LevelChunk* chunk = new LevelChunk(m_level, &primer, x, z);
    chunk->setCheckAllLight();
    XPhysicalFree(ids);
    XPhysicalFree(data);
    return chunk;
}

void NetherLevelSource::lightChunk(LevelChunk* chunk) {
    chunk->recalcHeightmap();
}

// NON_MATCHING | score: 9195 (lower is better)
void NetherLevelSource::postProcess(int x, int z) {
    inPostProcessStep = true;
    BlockPos origin(x * 16, 0, z * 16);
    Biome* biome = m_level->getBiome(origin.offset(16, 0, 16));
    ChunkPos chunk(x, z);
    m_populationRandom.setSeed(m_level->getSeed());
    long long a = m_populationRandom.nextLong() / 2 * 2 + 1;
    long long b = m_populationRandom.nextLong() / 2 * 2 + 1;
    // Both original multipliers use Z; retain that Switch population behavior.
    m_populationRandom.setSeed(
        (static_cast<unsigned long long>(z) * a + static_cast<unsigned long long>(z) * b)
        ^ m_level->getSeed());
    m_fortress->postProcess(m_level, m_populationRandom, &chunk);
    for (int i = 0; i < 8; ++i) {
        int dx = m_populationRandom.nextInt(16) + 8;
        int dy = m_populationRandom.nextInt(120) + 4;
        int dz = m_populationRandom.nextInt(16) + 8;
        m_openLava->place(m_level, m_populationRandom, origin.offset(dx, dy, dz));
    }
    for (int i = 0; i < m_populationRandom.nextInt(m_populationRandom.nextInt(10) + 1) + 1; ++i) {
        int dx = m_populationRandom.nextInt(16) + 8;
        int dy = m_populationRandom.nextInt(120) + 4;
        int dz = m_populationRandom.nextInt(16) + 8;
        m_fire->place(m_level, m_populationRandom, origin.offset(dx, dy, dz));
    }
    for (int i = 0; i < m_populationRandom.nextInt(m_populationRandom.nextInt(10) + 1); ++i) {
        int dx = m_populationRandom.nextInt(16) + 8;
        int dy = m_populationRandom.nextInt(120) + 4;
        int dz = m_populationRandom.nextInt(16) + 8;
        m_glowstone->place(m_level, m_populationRandom, origin.offset(dx, dy, dz));
    }
    for (int i = 0; i < 10; ++i) {
        int dx = m_populationRandom.nextInt(16) + 8;
        int dy = m_populationRandom.nextInt(128);
        int dz = m_populationRandom.nextInt(16) + 8;
        m_portal->place(m_level, m_populationRandom, origin.offset(dx, dy, dz));
    }
    if (m_populationRandom.nextBoolean()) {
        int dx = m_populationRandom.nextInt(16) + 8;
        int dy = m_populationRandom.nextInt(128);
        int dz = m_populationRandom.nextInt(16) + 8;
        m_brownMushroom->place(m_level, m_populationRandom, origin.offset(dx, dy, dz));
    }
    if (m_populationRandom.nextBoolean()) {
        int dx = m_populationRandom.nextInt(16) + 8;
        int dy = m_populationRandom.nextInt(128);
        int dz = m_populationRandom.nextInt(16) + 8;
        m_redMushroom->place(m_level, m_populationRandom, origin.offset(dx, dy, dz));
    }
    for (int i = 0; i < 16; ++i) {
        int dx = m_populationRandom.nextInt(16);
        int dy = m_populationRandom.nextInt(108) + 10;
        int dz = m_populationRandom.nextInt(16);
        m_quartz->place(m_level, m_populationRandom, origin.offset(dx, dy, dz));
    }
    int magmaHeight = m_level->getSeaLevel() / 2 - 4;
    for (int i = 0; i < 4; ++i) {
        int dx = m_populationRandom.nextInt(16);
        int dy = magmaHeight + m_populationRandom.nextInt(10);
        int dz = m_populationRandom.nextInt(16);
        m_magma->place(m_level, m_populationRandom, origin.offset(dx, dy, dz));
    }
    for (int i = 0; i < 16; ++i) {
        int dx = m_populationRandom.nextInt(16);
        int dy = m_populationRandom.nextInt(108) + 10;
        int dz = m_populationRandom.nextInt(16);
        m_enclosedLava->place(m_level, m_populationRandom, origin.offset(dx, dy, dz));
    }
    biome->decorate(m_level, m_populationRandom, BlockPos(x * 16, 0, z * 16));
    inPostProcessStep = false;
    CConsoleMinecraftApp::sInstance.processSchematics(m_level->getChunk(x, z));
}

bool NetherLevelSource::postProcessLoadedChunk(LevelChunk*, int, int) {
    return false;
}

std::vector<Biome::MobSpawnerData*>* NetherLevelSource::getMobsAt(MobCategory* category,
                                                                  const BlockPos& pos) {
    if (category == MobCategory::MONSTER) {
        if (m_fortress->isInsideFeature(pos))
            return m_fortress->getSpawnList();
        if (m_fortress->isInsideBoundingFeature(m_level, pos)
            && m_level->getBlockState(pos.below())->getBlock() == Blocks::NETHER_BRICK)
            return m_fortress->getSpawnList();
    }
    return m_level->getBiome(pos)->getMobs(category);
}

BlockPos* NetherLevelSource::findNearestMapFeature(Level* level, const std::wstring& name,
                                                   const BlockPos& pos, bool unexplored) {
    if (FORTRESS_NAME == name && m_fortress)
        return m_fortress->getNearestGeneratedFeature(level, pos, unexplored);
    return nullptr;
}

bool NetherLevelSource::isPosInFeature(Level*, const std::wstring& name, const BlockPos& pos) {
    if (FORTRESS_NAME.compare(name) == 0 && m_fortress)
        return m_fortress->isInsideFeature(pos);
    return false;
}

void NetherLevelSource::recreateLogicStructuresForChunk(LevelChunk*, int x, int z) {
    m_fortress->apply(m_level, x, z, nullptr);
}
