#include "net/minecraft/world/level/biome/MesaBiome.h"

#include "NX/Platform.h"
#include "net/minecraft/client/Minecraft.h"
#include "net/minecraft/client/color/ColourTable.h"
#include "net/minecraft/util/Mth.h"
#include "net/minecraft/world/Random.h"
#include "net/minecraft/world/item/DyeColor.h"
#include "net/minecraft/world/level/Level.h"
#include "net/minecraft/world/level/block/Blocks.h"
#include "net/minecraft/world/level/block/ColoredBlock.h"
#include "net/minecraft/world/level/block/DirtBlock.h"
#include "net/minecraft/world/level/block/SandBlock.h"
#include "net/minecraft/world/level/levelgen/ChunkPrimer.h"
#include "net/minecraft/world/level/levelgen/feature/TreeFeature.h"
#include "net/minecraft/world/level/levelgen/synth/PerlinSimplexNoise.h"
#include "net/minecraft/world/level/material/Material.h"
#include <cmath>

Biome::LegacyBlockData MesaBiome::COARSE_DIRT;
Biome::LegacyBlockData MesaBiome::GRASS;
Biome::LegacyBlockData MesaBiome::HARDENED_CLAY;
Biome::LegacyBlockData MesaBiome::STAINED_HARDENED_CLAY;
Biome::LegacyBlockData MesaBiome::ORANGE_CLAY;
Biome::LegacyBlockData MesaBiome::RED_SAND;

void MesaBiome::staticCtor() {
    COARSE_DIRT = LegacyBlockData(
        3, Blocks::DIRT->convertBlockStateToLegacyData(
               Blocks::DIRT->defaultBlockState()->setValue(DirtBlock::VARIANT, DirtBlock::Variant::COARSE)));
    GRASS = LegacyBlockData(2,
                            Blocks::GRASS->convertBlockStateToLegacyData(Blocks::GRASS->defaultBlockState()));
    HARDENED_CLAY = LegacyBlockData(172, Blocks::HARDENED_CLAY->convertBlockStateToLegacyData(
                                             Blocks::HARDENED_CLAY->defaultBlockState()));
    STAINED_HARDENED_CLAY = LegacyBlockData(159, Blocks::STAINED_HARDENED_CLAY->convertBlockStateToLegacyData(
                                                     Blocks::STAINED_HARDENED_CLAY->defaultBlockState()));
    ORANGE_CLAY = LegacyBlockData(159, Blocks::STAINED_HARDENED_CLAY->convertBlockStateToLegacyData(
                                           Blocks::STAINED_HARDENED_CLAY->defaultBlockState()->setValue(
                                               ColoredBlock::COLOR, DyeColor::ORANGE)));
    RED_SAND = LegacyBlockData(
        12, Blocks::SAND->convertBlockStateToLegacyData(
                Blocks::SAND->defaultBlockState()->setValue(SandBlock::VARIANT, SandBlock::Variant::RED)));
}

MesaBiome::MesaBiome(EBiomeIDs id, bool bryce, bool forest, BiomeProperties* properties)
    : Biome(id, properties) {
    m_bryce = bryce;
    m_forest = forest;
    m_clayBands = nullptr;
    m_seed = 0;
    m_pillarNoise = nullptr;
    m_pillarRoofNoise = nullptr;
    m_clayBandsOffsetNoise = nullptr;
    m_passiveMobs.clear();
    m_grass = RED_SAND;
    m_dirt = STAINED_HARDENED_CLAY;
    delete m_biomeDecorator;
    m_biomeDecorator = new MesaDecorator();
    m_biomeDecorator->m_treeCount = -999;
    m_biomeDecorator->m_deadBushCount = 20;
    m_biomeDecorator->m_reedCount = 3;
    m_biomeDecorator->m_cactusCount = 5;
    m_biomeDecorator->m_flowerCount = 0;
    m_passiveMobs.clear();
    if (forest)
        m_biomeDecorator->m_treeCount = 5;
}

MesaBiome::~MesaBiome() {
    delete m_pillarNoise;
    delete m_pillarRoofNoise;
    delete m_clayBandsOffsetNoise;
    delete[] m_clayBands;
}

int MesaBiome::getBaseClass() {
    return _MESA;
}
Feature* MesaBiome::getTreeFeature(Random&) {
    return new TreeFeature(false);
}
unsigned int MesaBiome::getGrassColor(const BlockPos*) {
    return Minecraft::GetInstance()->getColourTable()->getColour(Grass_Mesa);
}
unsigned int MesaBiome::getFoliageColor(const BlockPos*) {
    return Minecraft::GetInstance()->getColourTable()->getColour(Foliage_Mesa);
}

void MesaBiome::MesaDecorator::decorateOres(Level* level, Random& random) {
    BiomeDecorator::decorateOres(level, random);
    decorateDepthSpan(level, random, 20, m_gold, 32, 80);
}

void MesaBiome::generateBands(long long seed) {
    delete[] m_clayBands;
    m_clayBands = new LegacyBlockData[64];
    for (int i = 0; i < 64; ++i)
        m_clayBands[i] = HARDENED_CLAY;
    Random random(seed);
    // Rebuilding this cache replaces the noise pointer without deleting the old one in the original.
    m_clayBandsOffsetNoise = new PerlinSimplexNoise(&random, 1);
    for (int i = 0; i < 64; ++i) {
        i += random.nextInt(5) + 1;
        if (i < 64)
            m_clayBands[i] = ORANGE_CLAY;
    }

    LegacyBlockData clay(159, Blocks::STAINED_HARDENED_CLAY->convertBlockStateToLegacyData(
                                  Blocks::STAINED_HARDENED_CLAY->defaultBlockState()->setValue(
                                      ColoredBlock::COLOR, DyeColor::YELLOW)));
    int count = random.nextInt(4) + 2;
    for (int i = 0; i < count; ++i) {
        int width = random.nextInt(3) + 1;
        int start = random.nextInt(64);
        for (int j = 0; j < width && start + j < 64; ++j)
            m_clayBands[start + j] = clay;
    }
    clay = LegacyBlockData(159, Blocks::STAINED_HARDENED_CLAY->convertBlockStateToLegacyData(
                                    Blocks::STAINED_HARDENED_CLAY->defaultBlockState()->setValue(
                                        ColoredBlock::COLOR, DyeColor::BROWN)));
    count = random.nextInt(4) + 2;
    for (int i = 0; i < count; ++i) {
        int width = random.nextInt(3) + 2;
        int start = random.nextInt(64);
        for (int j = 0; j < width && start + j < 64; ++j)
            m_clayBands[start + j] = clay;
    }
    clay = LegacyBlockData(159, Blocks::STAINED_HARDENED_CLAY->convertBlockStateToLegacyData(
                                    Blocks::STAINED_HARDENED_CLAY->defaultBlockState()->setValue(
                                        ColoredBlock::COLOR, DyeColor::RED)));
    count = random.nextInt(4) + 2;
    for (int i = 0; i < count; ++i) {
        int width = random.nextInt(3) + 1;
        int start = random.nextInt(64);
        for (int j = 0; j < width && start + j < 64; ++j)
            m_clayBands[start + j] = clay;
    }
    clay = LegacyBlockData(159, Blocks::STAINED_HARDENED_CLAY->convertBlockStateToLegacyData(
                                    Blocks::STAINED_HARDENED_CLAY->defaultBlockState()->setValue(
                                        ColoredBlock::COLOR, DyeColor::SILVER)));
    LegacyBlockData white(159, Blocks::STAINED_HARDENED_CLAY->convertBlockStateToLegacyData(
                                   Blocks::STAINED_HARDENED_CLAY->defaultBlockState()->setValue(
                                       ColoredBlock::COLOR, DyeColor::WHITE)));
    count = random.nextInt(3) + 3;
    int start = 0;
    for (int i = 0; i < count; ++i) {
        start += random.nextInt(16) + 4;
        if (start < 64) {
            m_clayBands[start] = white;
            if (start > 1 && random.nextBoolean())
                m_clayBands[start - 1] = clay;
            if (start < 63 && random.nextBoolean())
                m_clayBands[start + 1] = clay;
        }
    }
}

Biome::LegacyBlockData MesaBiome::getBand(int x, int y, int) {
    // The Switch implementation samples X for both noise coordinates.
    int offset = static_cast<int>(Mth::round(m_clayBandsOffsetNoise->getValue(x / 512.0, x / 512.0) * 2.0));
    return m_clayBands[(y + offset + 64) % 64];
}

void MesaBiome::buildSurfaceAt(Level* level, Random& random, ChunkPrimer* primer, int x, int z,
                               double noise) {
    PIXBeginNamedEvent(0.0f, "MesaBiome::buildSurfaceAtDefault");
    if (!m_clayBands || m_seed != level->getSeed())
        generateBands(level->getSeed());
    if (!m_pillarNoise || !m_pillarRoofNoise || m_seed != level->getSeed()) {
        // The original uses the previous cached seed and retains this heap Random.
        Random* noiseRandom = new Random(m_seed);
        m_pillarNoise = new PerlinSimplexNoise(noiseRandom, 4);
        m_pillarRoofNoise = new PerlinSimplexNoise(noiseRandom, 1);
    }
    m_seed = level->getSeed();
    int pillarHeight = 0;
    if (m_bryce) {
        int pillarX = (x & ~15) | (z & 15);
        int pillarZ = (z & ~15) | (x & 15);
        double pillar = std::fabs(noise);
        double sample = m_pillarNoise->getValue(pillarX * 0.25, pillarZ * 0.25);
        if (sample < pillar)
            pillar = sample;
        if (pillar > 0.0) {
            double roof = std::fabs(m_pillarRoofNoise->getValue(pillarX / 512.0, pillarZ / 512.0));
            double height = pillar * pillar * 2.5;
            double limit = std::ceil(roof * 50.0) + 14.0;
            if (height > limit)
                height = limit;
            pillarHeight = static_cast<int>(height + 64.0);
        }
    }
    int localX = x & 15;
    int localZ = z & 15;
    LegacyBlockData filler = m_dirt;
    int depth = static_cast<int>(noise / 3.0 + 3.0 + random.nextDouble() * 0.25);
    bool hardened = std::cos(noise / 3.0 * Mth::PI) > 0.0;
    int remaining = -1;
    bool redSand = false;
    int stoneCount = 0;
    for (int y = 127; y >= 0; --y) {
        int index = (localZ << 11) | (localX << 7) | y;
        const BlockState* state = primer->getState(localZ, y, localX);
        Material* material = state->getBlock()->getMaterial();
        if (y < pillarHeight && material == Material::AIR)
            primer->setBlockAndData(index, STONE.m_id, STONE.m_data);
        if (y <= random.nextInt(2) + 1) {
            primer->setBlockAndData(index, BEDROCK.m_id, BEDROCK.m_data);
        } else if (stoneCount < 15 || m_bryce) {
            state = primer->getState(localZ, y, localX);
            if (state->getBlock()->getMaterial() == Material::AIR) {
                remaining = -1;
            } else if (state->getBlock() == Blocks::STONE) {
                if (remaining == -1) {
                    if (depth < 1)
                        filler = STONE;
                    else if (y >= 59 && y <= 64)
                        filler = m_dirt;
                    remaining = depth + (y > 63 ? y - 63 : 0);
                    redSand = false;
                    if (y >= 62) {
                        if (m_forest && y > 86 + depth * 2) {
                            const LegacyBlockData& surface = hardened ? COARSE_DIRT : GRASS;
                            primer->setBlockAndData(index, surface.m_id, surface.m_data);
                        } else if (y > 66 + depth) {
                            LegacyBlockData surface;
                            if (y >= 64 && y <= 127)
                                surface = hardened ? HARDENED_CLAY : getBand(x, y, z);
                            else
                                surface = ORANGE_CLAY;
                            primer->setBlockAndData(index, surface.m_id, surface.m_data);
                        } else {
                            primer->setBlockAndData(index, m_grass.m_id, m_grass.m_data);
                            redSand = true;
                        }
                    } else {
                        primer->setBlockAndData(index, filler.m_id, filler.m_data);
                        if (filler.m_id == 159) {
                            primer->setBlockAndData(index, ORANGE_CLAY.m_id, ORANGE_CLAY.m_data);
                            filler.m_id = 159;
                        }
                    }
                } else if (remaining > 0) {
                    --remaining;
                    LegacyBlockData band = redSand ? ORANGE_CLAY : getBand(x, y, z);
                    primer->setBlockAndData(index, band.m_id, band.m_data);
                }
                ++stoneCount;
            }
        }
    }
    PIXEndNamedEvent();
}
