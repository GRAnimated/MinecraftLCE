#include "net/minecraft/world/level/levelgen/OverworldLevelSource.h"

#include "NX/Platform.h"
#include "net/minecraft/util/Mth.h"
#include "net/minecraft/world/entity/MobCategory.h"
#include "net/minecraft/world/level/Level.h"
#include "net/minecraft/world/level/biome/Biome.h"
#include "net/minecraft/world/level/biome/BiomeSource.h"
#include "net/minecraft/world/level/block/Blocks.h"
#include "net/minecraft/world/level/chunk/LevelChunk.h"
#include "net/minecraft/world/level/levelgen/ChunkPrimer.h"
#include "net/minecraft/world/level/levelgen/CustomizableSourceSettings.h"
#include "net/minecraft/world/level/levelgen/feature/CanyonFeature.h"
#include "net/minecraft/world/level/levelgen/feature/LakeFeature.h"
#include "net/minecraft/world/level/levelgen/feature/LargeCaveFeature.h"
#include "net/minecraft/world/level/levelgen/feature/MineShaftFeature.h"
#include "net/minecraft/world/level/levelgen/feature/MonsterRoomFeature.h"
#include "net/minecraft/world/level/levelgen/feature/OceanMonumentFeature.h"
#include "net/minecraft/world/level/levelgen/feature/RandomScatteredLargeFeature.h"
#include "net/minecraft/world/level/levelgen/feature/StrongholdFeature.h"
#include "net/minecraft/world/level/levelgen/feature/VillageFeature.h"
#include "net/minecraft/world/level/levelgen/feature/WoodlandMansionFeature.h"
#include "net/minecraft/world/level/levelgen/synth/PerlinNoise.h"
#include "net/minecraft/world/level/levelgen/synth/PerlinSimplexNoise.h"
#include "net/minecraft/world/level/storage/LevelData.h"

OverworldLevelSource::OverworldLevelSource(Level* level, long long seed, bool generateStructures,
                                           SuperflatConfig* sourceSettings) {
    m_size = level->getLevelData()->getXZSize();
    level->getLevelData()->fillMoatValues(&m_isClassicMoat, &m_isSmallMoat, &m_isMediumMoat);

    m_level = level;
    m_shouldGenerateStructures = generateStructures;
    m_generatorType = level->getLevelData()->getGeneratorType();

    m_caveFeature = new LargeCaveFeature();
    m_strongholdFeature = new StrongholdFeature();
    m_villageFeature = new VillageFeature(level->getLevelData()->getXZSize());
    m_mineshaftFeature = new MineShaftFeature();
    m_randomScatteredLargeFeature = new RandomScatteredLargeFeature();
    m_canyonFeature = new CanyonFeature();
    m_oceanMonumentFeature = new OceanMonumentFeature();
    m_woodlandMansionFeature = new WoodlandMansionFeature(this);
    m_random = Random(seed);
    m_random2 = Random(seed);
    m_minLimitPerlinNoise = new PerlinNoise(&m_random, 16);
    m_maxLimitPerlinNoise = new PerlinNoise(&m_random, 16);
    m_mainNoise = new PerlinNoise(&m_random, 8);
    m_surfaceNoise = new PerlinSimplexNoise(&m_random, 4);
    m_scaleNoise = new PerlinNoise(&m_random, 10);
    m_depthNoise = new PerlinNoise(&m_random, 16);
    m_qword78 = nullptr;
    m_qword80 = nullptr;
    m_field88 = new PerlinNoise(&m_random, 8);

    for (int i = -2; i <= 2; ++i) {
        for (int j = -2; j <= 2; ++j) {
            float f = 10.0f / sqrtf((float)(i * i + j * j) + 0.2f);
            m_biomeWeights[i + 2 + (j + 2) * 5] = f;
        }
    }

    m_oceanBlock = Blocks::WATER->defaultBlockState();

    CustomizableSourceSettings::Builder* builder;

    if (!sourceSettings) {
        builder = new CustomizableSourceSettings::Builder();
        m_sourceSettings = new CustomizableSourceSettings(builder);

    } else {
        builder = CustomizableSourceSettings::Builder::fromString(sourceSettings);
        m_sourceSettings = builder->build();
        if (m_sourceSettings->m_useLavaOceans)
            m_oceanBlock = Blocks::LAVA->defaultBlockState();
        else
            m_oceanBlock = Blocks::WATER->defaultBlockState();

        level->setSeaLevel(m_sourceSettings->m_seaLevel);
    }

    delete builder;
}

OverworldLevelSource::~OverworldLevelSource() {
    delete m_caveFeature;
    delete m_strongholdFeature;
    delete m_villageFeature;
    delete m_mineshaftFeature;
    delete m_randomScatteredLargeFeature;
    delete m_canyonFeature;
    delete m_oceanMonumentFeature;
    delete m_woodlandMansionFeature;
    delete m_minLimitPerlinNoise;
    delete m_maxLimitPerlinNoise;
    delete m_mainNoise;
    delete m_surfaceNoise;
    delete m_scaleNoise;
    delete m_depthNoise;
    delete m_qword78;
    delete m_qword80;
    delete m_field88;
    delete m_sourceSettings;
    delete m_qword120.m_data;
}

float OverworldLevelSource::getHeightFalloff(int chunkX, int chunkZ, int* distance) {
    int size = m_size * 16;
    int nearestDist = distanceToEdge(32.0f, 0, chunkX, chunkZ, size);

    MoatCheck moatChecks[] = {{m_isClassicMoat, 864}, {m_isSmallMoat, 1024}, {m_isMediumMoat, 3072}};

    for (auto& check : moatChecks) {
        if (check.m_enabled && size > check.m_limit) {
            int d = distanceToEdge(32.0f, nearestDist, chunkX, chunkZ, check.m_limit);
            if (d < nearestDist) {
                nearestDist = d;
            }
        }
    }

    float result = 0.0f;
    if (nearestDist < 32) {
        result = (32 - nearestDist) * 0.03125f * 128.0f;
    }

    *distance = nearestDist;
    return result;
}

// NON_MATCHING | Score: 1630 (lower is better)
int OverworldLevelSource::distanceToEdge(float a, int, int x, int z, int size) {
    int halfSize = size / 2;

    int minCoord = -halfSize;
    int maxCoord = halfSize - 1;

    Vec3* topLeft = Vec3::newTemp(minCoord, 0.0f, minCoord);
    Vec3* topRight = Vec3::newTemp(maxCoord, 0.0f, minCoord);
    Vec3* bottomLeft = Vec3::newTemp(minCoord, 0.0f, maxCoord);
    Vec3* bottomRight = Vec3::newTemp(maxCoord, 0.0f, maxCoord);

    float leftBound = minCoord - a;
    float rightBound = minCoord + a;

    float distance = a;

    bool inLeftBand = (x > leftBound) && (x < rightBound);
    bool inRightBand = (!inLeftBand) && (x > (maxCoord - a)) && (x < (maxCoord + a));

    if (inLeftBand || inRightBand) {
        Vec3* p = Vec3::newTemp(x, 0.0f, z);
        Vec3* edgeStart = (x < 1) ? topLeft : topRight;
        Vec3* edgeEnd = (x < 1) ? bottomLeft : bottomRight;

        distance = p->distanceToSegment(edgeStart, edgeEnd);
    }

    if (((z > leftBound) && (z < rightBound)) || ((z > (maxCoord - a)) && (z < (maxCoord + a)))) {
        Vec3* p = Vec3::newTemp(x, 0.0f, z);
        Vec3* edgeStart = (z < 1) ? topLeft : topRight;
        Vec3* edgeEnd = (z < 1) ? bottomLeft : bottomRight;

        float verticalDistance = p->distanceToSegment(edgeStart, edgeEnd);

        if (verticalDistance < distance) {
            distance = verticalDistance;
        }
    }

    return distance;
}

void OverworldLevelSource::buildSurfaces(int chunkX, int chunkZ, ChunkPrimer* primer,
                                         arrayWithLength<Biome*> biomes) {
    arrayWithLength<double> noiseRegion(16 * 16, true);

    PIXBeginNamedEvent(0.0, "Getting noise region");

    noiseRegion
        = m_surfaceNoise->getRegion(noiseRegion, chunkX * 16, chunkZ * 16, 16, 16, 0.0625, 0.0625, 1.0);

    PIXEndNamedEvent();

    for (int x = 0; x < 16; x++) {
        for (int z = 0; z < 16; z++) {
            Biome* biome = biomes[z + x * 16];
            {
                std::wstring biomeName = biome->getName(false);
                PIXBeginNamedEvent(0.0, "Building surface for biome %ls", biomeName.c_str());
            }

            biome->buildSurfaceAt(m_level, m_random, primer, chunkX * 16 + x, chunkZ * 16 + z,
                                  noiseRegion[z + x * 16]);

            PIXEndNamedEvent();
        }
    }

    delete noiseRegion.m_data;
}

LevelChunk* OverworldLevelSource::createChunk(int chunkX, int chunkZ) {
    m_random.setSeed(341873128712 * chunkX + 132897987541 * chunkZ);

    PIXBeginNamedEvent(0.0, "Setting up primer");
    void* ids = XPhysicalAlloc(0x8000, 0xFFFFFFFFFFFFFFFF, 0x1000, 4);
    XMemSet128(ids, 0, 0x8000);
    arrayWithLength<uchar> blockIds((uchar*)ids, 0x8000u);
    void* data = XPhysicalAlloc(0x4000, 0xFFFFFFFFFFFFFFFF, 0x1000, 4);
    XMemSet128(data, 0, 0x4000);
    arrayWithLength<uchar> blockData((uchar*)data, 0x4000);
    ChunkPrimer primer = ChunkPrimer(false, blockIds, blockData);
    PIXEndNamedEvent();

    PIXBeginNamedEvent(0.0, "Preparing heights");
    prepareHeights(chunkX, chunkZ, &primer);
    PIXEndNamedEvent();

    PIXBeginNamedEvent(0.0, "Getting biome block");
    arrayWithLength<Biome*> biomes;
    m_level->getBiomeSource()->getBiomeBlock(biomes, 16 * chunkX, 16 * chunkZ, 16, 16, true);
    PIXEndNamedEvent();

    PIXBeginNamedEvent(0.0, "Building surfaces");
    buildSurfaces(chunkX, chunkZ, &primer, biomes);
    PIXEndNamedEvent();

    delete biomes.m_data;

    if (m_sourceSettings->m_useCaves) {
        PIXBeginNamedEvent(0.0, "Applying caves");
        m_caveFeature->apply(m_level, chunkX, chunkZ, &primer);
        PIXEndNamedEvent();
    }

    if (m_sourceSettings->m_byte52) {
        PIXBeginNamedEvent(0.0, "Applying ravines");
        m_canyonFeature->apply(m_level, chunkX, chunkZ, &primer);
        PIXEndNamedEvent();
    }

    if (m_shouldGenerateStructures) {
        if (m_sourceSettings->m_useMineshafts) {
            PIXBeginNamedEvent(0.0, "Applying mineshafts");
            m_mineshaftFeature->apply(m_level, chunkX, chunkZ, &primer);
            PIXEndNamedEvent();
        }
        if (m_sourceSettings->m_useVillages) {
            PIXBeginNamedEvent(0.0, "Applying villages");
            m_villageFeature->apply(m_level, chunkX, chunkZ, &primer);
            PIXEndNamedEvent();
        }
        if (m_sourceSettings->m_useStrongholds) {
            PIXBeginNamedEvent(0.0, "Applying strongholds");
            m_strongholdFeature->apply(m_level, chunkX, chunkZ, &primer);
            PIXEndNamedEvent();
        }
        if (m_sourceSettings->m_useScatteredFeatures) {
            PIXBeginNamedEvent(0.0, "Applying scatterd features");
            m_randomScatteredLargeFeature->apply(m_level, chunkX, chunkZ, &primer);
            PIXEndNamedEvent();
        }
        if (m_sourceSettings->m_useOceanMonuments) {
            PIXBeginNamedEvent(0.0, "Applying ocean monuments");
            m_oceanMonumentFeature->apply(m_level, chunkX, chunkZ, &primer);
            PIXEndNamedEvent();
        }
        if (m_sourceSettings->m_useWoodlandMansions) {
            PIXBeginNamedEvent(0.0, "Applying woodland mansions");
            m_woodlandMansionFeature->apply(m_level, chunkX, chunkZ, &primer);
            PIXEndNamedEvent();
        }
    }

    PIXBeginNamedEvent(0.0, "Creating chunk");
    LevelChunk* chunk = new LevelChunk(m_level, &primer, chunkX, chunkZ);
    PIXEndNamedEvent();

    XPhysicalFree(ids);
    XPhysicalFree(data);

    return chunk;
}

void OverworldLevelSource::lightChunk(LevelChunk* chunk) {
    chunk->recalcHeightmap();
}

void OverworldLevelSource::getHeights(int posX, int posY, int posZ, arrayWithLength<Biome*>& biomes,
                                      arrayWithLength<double>& heightmap) {
    arrayWithLength<double> mainNoise;
    arrayWithLength<double> minLimitNoise;
    arrayWithLength<double> maxLimitNoise;
    arrayWithLength<double> depthNoise;
    arrayWithLength<double> unk;
    arrayWithLength<double> unk2;

    float coordinateScale = m_sourceSettings->m_coordinateScale;
    float heightScale = m_sourceSettings->m_heightScale;

    depthNoise = m_depthNoise->getRegion(depthNoise, posX, posZ, 5, 5, m_sourceSettings->m_depthNoiseScaleX,
                                         m_sourceSettings->m_depthNoiseScaleZ,
                                         m_sourceSettings->m_depthNoiseScaleExponent);

    mainNoise = m_mainNoise->getRegion(mainNoise, posX, posY, posZ, 5, 17, 5,
                                       coordinateScale / m_sourceSettings->m_ainNoiseScaleX,
                                       heightScale / m_sourceSettings->m_ainNoiseScaleY,
                                       coordinateScale / m_sourceSettings->m_ainNoiseScaleZ);

    minLimitNoise = m_minLimitPerlinNoise->getRegion(minLimitNoise, posX, posY, posZ, 5, 17, 5,
                                                     coordinateScale, heightScale, coordinateScale);

    maxLimitNoise = m_maxLimitPerlinNoise->getRegion(maxLimitNoise, posX, posY, posZ, 5, 17, 5,
                                                     coordinateScale, heightScale, coordinateScale);

    int i = 0;
    int j = 0;

    for (int x = 0; x < 5; ++x) {
        for (int z = 0; z < 5; ++z) {
            float weightedScale = 0.0f;
            float weightedDepth = 0.0f;
            float totalWeight = 0.0f;
            Biome* b = biomes[x + 2 + (z + 2) * 10];

            for (int xo = -2; xo <= 2; ++xo) {
                for (int zo = -2; zo <= 2; ++zo) {
                    Biome* b2 = biomes[x + xo + 2 + (z + zo + 2) * 10];

                    float depth = m_sourceSettings->m_biomeDepthOffset
                                  + (b2->getDepth() * m_sourceSettings->m_biomeDepthWeight);

                    float scale = m_sourceSettings->m_biomeScaleOffset
                                  + (b2->getScale() * m_sourceSettings->m_biomeScaleWeight);

                    if (m_generatorType == LevelType::AMPLIFIED && depth > 0.0f) {
                        depth = depth * 2.0f + 1.0f;
                        scale = scale * 4.0f + 1.0f;
                    }

                    float weight = m_biomeWeights[(xo + 2) + (zo + 2) * 5] / (depth + 2.0f);
                    if (b2->getDepth() > b->getDepth()) {
                        weight *= 0.5f;
                    }

                    weightedScale += scale * weight;
                    weightedDepth += depth * weight;
                    totalWeight += weight;
                }
            }

            weightedScale /= totalWeight;
            weightedDepth /= totalWeight;

            weightedScale = weightedScale * 0.9f + 0.1f;
            weightedDepth = (weightedDepth * 4.0f - 1.0f) / 8.0f;

            double dn = depthNoise[j] / 8000.0;
            if (dn < 0.0) {
                dn = -dn * 0.3;
            }
            dn = dn * 3.0 - 2.0;

            if (dn < 0.0) {
                dn = dn * 0.5;
                if (dn < -1.0)
                    dn = -1.0;
                dn = dn / 1.4;
                dn *= 0.5;
            } else {
                if (dn > 1.0)
                    dn = 1.0;
                dn = dn * 0.125;
            }

            ++j;

            double baseSize = weightedDepth;
            double d9 = weightedScale;
            baseSize = baseSize + dn * 0.2;
            baseSize = baseSize * m_sourceSettings->m_baseSize / 8.0;
            double baseHeight = m_sourceSettings->m_baseSize + baseSize * 4.0;

            for (int y = 0; y < 17; ++y) {
                double yOffset = (y - baseHeight) * m_sourceSettings->m_stretchY * 128.0 / 128.0 / d9;

                if (yOffset < 0.0) {
                    yOffset *= 4.0;
                }

                double minNoiseVal = minLimitNoise[i] / m_sourceSettings->m_upperLimitScale;
                double maxNoiseVal = maxLimitNoise[i] / m_sourceSettings->m_lowerLimitScale;
                double mainNoiseVal = mainNoise[i] / 10.0 + 1.0;

                double lerped = Mth::clampedLerp(minNoiseVal, maxNoiseVal, mainNoiseVal * 0.5) - yOffset;

                if (y > 13) {
                    double fade = (y - 13) / 3.0f;
                    lerped = lerped * (1.0 - fade) - 10.0 * fade;
                }

                heightmap[i] = lerped;
                ++i;
            }
        }
    }

    delete[] mainNoise.m_data;
    delete[] minLimitNoise.m_data;
    delete[] maxLimitNoise.m_data;
    delete[] depthNoise.m_data;
    delete[] unk.m_data;
    delete[] unk2.m_data;
}

void OverworldLevelSource::postProcess(int chunkX, int chunkZ) {
    ChunkGenerator::inPostProcessStep = true;

    BlockPos origin(chunkX * 16, 0, chunkZ * 16);
    Biome* biome = m_level->getBiome(origin.offset(16, 0, 16));

    m_random2.setSeed(m_level->getSeed());

    long long t1 = m_random2.nextLong() / 2 * 2 + 1;
    long long t2 = m_random2.nextLong() / 2 * 2 + 1;

    long long mixed = t1 * chunkX + t2 * chunkZ;
    m_random2.setSeed(mixed ^ m_level->getSeed());

    ChunkPos chunkPos(chunkX, chunkZ);

    PIXBeginNamedEvent(0.0, "Structure postprocessing");

    bool villageFlag = false;

    if (m_shouldGenerateStructures) {
        if (m_sourceSettings->m_useMineshafts) {
            m_mineshaftFeature->postProcess(m_level, m_random2, &chunkPos);
        }

        if (m_sourceSettings->m_useVillages) {
            villageFlag = m_villageFeature->postProcess(m_level, m_random2, &chunkPos);
        }

        if (m_sourceSettings->m_useStrongholds) {
            m_strongholdFeature->postProcess(m_level, m_random2, &chunkPos);
        }

        if (m_sourceSettings->m_useScatteredFeatures) {
            m_randomScatteredLargeFeature->postProcess(m_level, m_random2, &chunkPos);
        }

        if (m_sourceSettings->m_useOceanMonuments) {
            m_oceanMonumentFeature->postProcess(m_level, m_random2, &chunkPos);
        }

        if (m_sourceSettings->m_useWoodlandMansions) {
            m_woodlandMansionFeature->postProcess(m_level, m_random2, &chunkPos);
        }
    }

    PIXEndNamedEvent();

    PIXBeginNamedEvent(0.0, "Lakes");

    if (biome != Biome::DESERT && biome != Biome::DESERT_HILLS) {
        if (m_sourceSettings->m_useWaterLakes) {
            if (!villageFlag && m_random2.nextInt(m_sourceSettings->m_waterLakeChance) == 0) {
                int rx = m_random2.nextInt(16) + 8;
                int ry = m_random2.nextInt(128);
                int rz = m_random2.nextInt(16) + 8;

                LakeFeature(Blocks::WATER).place(m_level, m_random2, origin.offset(rx, ry, rz));
            }
        }
    }
    PIXEndNamedEvent();

    PIXBeginNamedEvent(0.0, "Lava");
    if (!villageFlag && m_random2.nextInt(m_sourceSettings->m_lavaLakeChance / 10) == 0
        && m_sourceSettings->m_useLavaLakes) {
        int rx = m_random2.nextInt(16) + 8;
        int maxY = m_random2.nextInt(120);
        int ry = m_random2.nextInt(maxY + 8);
        int rz = m_random2.nextInt(16) + 8;

        if (ry < m_level->getSeaLevel() || m_random2.nextInt(m_sourceSettings->m_lavaLakeChance / 8) == 0) {
            LakeFeature(Blocks::LAVA).place(m_level, m_random2, origin.offset(rx, ry, rz));
        }
    }

    PIXEndNamedEvent();

    PIXBeginNamedEvent(0.0, "Monster rooms");
    if (m_sourceSettings->m_useDungeons) {
        MonsterRoomFeature dungeonGen;
        if (m_sourceSettings->m_dungeonChance >= 1) {
            for (int i = 0; i < m_sourceSettings->m_dungeonChance; ++i) {
                int rx = m_random2.nextInt(16) + 8;
                int ry = m_random2.nextInt(128);
                int rz = m_random2.nextInt(16) + 8;
                dungeonGen.place(m_level, m_random2, origin.offset(rx, ry, rz));
            }
        }
    }
    PIXEndNamedEvent();

    PIXBeginNamedEvent(0.0, "Biome decorate");
    biome->decorate(m_level, m_random2, BlockPos(chunkX * 16, 0, chunkZ * 16));
    PIXEndNamedEvent();

    PIXBeginNamedEvent(0.0, "Post process mobs");
    PIXEndNamedEvent();

    PIXBeginNamedEvent(0.0, "Update ice and snow");

    origin = origin.offset(8, 0, 8);
    for (int x = 0; x < 16; x++) {
        for (int z = 0; z < 16; z++) {
            BlockPos top = m_level->getTopRainBlockPos(origin.offset(x, 0, z));
            BlockPos below = top.below();

            if (m_level->shouldFreezeIgnoreNeighbors(below)) {
                m_level->setBlock(below, Blocks::ICE->defaultBlockState(), 2, 0);
            }

            if (m_level->shouldSnow(top, true)) {
                m_level->setBlock(top, Blocks::SNOW_LAYER->defaultBlockState(), 2, 0);
            }
        }
    }

    PIXEndNamedEvent();

    ChunkGenerator::inPostProcessStep = false;
}

bool OverworldLevelSource::postProcessLoadedChunk(LevelChunk*, int, int) {
    return false;
}

// NON_MATCHING | Score: 5336 (lower is better)
void OverworldLevelSource::prepareHeights(int chunkX, int chunkZ, ChunkPrimer* primer) {
    // These variables are made into constants by the compiler
    int width = 4;   // every 4th block is sampled in the chunk
    int height = 8;  // chunk gen is 128 blocks tall
    int xSize = width + 1;
    int zSize = width + 1;  // looks nicer to have a separate z size for the heights initializer
    int ySize = height * 2 + 1;

    int seaLevel = m_level->m_seaLevel;
    arrayWithLength<Biome*> biomes;

    PIXBeginNamedEvent(0.0, "Getting raw biome block");
    m_level->getBiomeSource()->getRawBiomeBlock(biomes, chunkX * 4 - 2, chunkZ * 4 - 2, 10, 10);
    PIXEndNamedEvent();

    PIXBeginNamedEvent(0.0, "Get heights");
    arrayWithLength<double> heights(xSize * zSize * ySize, true);  // 425
    getHeights(chunkX * width, 0, chunkZ * width, biomes, heights);
    PIXEndNamedEvent();

    PIXBeginNamedEvent(0.0, "Generating");
    for (int subX = 0; subX < width; subX++) {
        for (int subZ = 0; subZ < width; subZ++) {
            for (int subY = 0; subY < 16; subY++) {
                // + 0 is for padding so these look nicer
                double h00 = heights[((subX + 0) * xSize + (subZ + 0)) * ySize + subY];
                double h10 = heights[((subX + 0) * xSize + (subZ + 1)) * ySize + subY];
                double h01 = heights[((subX + 1) * xSize + (subZ + 0)) * ySize + subY];
                double h11 = heights[((subX + 1) * xSize + (subZ + 1)) * ySize + subY];

                // interpolation steps
                double iy00 = (heights[((subX + 0) * xSize + (subZ + 0)) * ySize + subY + 1] - h00) * 0.125;
                double iy10 = (heights[((subX + 0) * xSize + (subZ + 1)) * ySize + subY + 1] - h10) * 0.125;
                double iy01 = (heights[((subX + 1) * xSize + (subZ + 0)) * ySize + subY + 1] - h01) * 0.125;
                double iy11 = (heights[((subX + 1) * xSize + (subZ + 1)) * ySize + subY + 1] - h11) * 0.125;

                for (int ym = 0; ym < 8; ym++) {
                    double heightAtXZ0 = h00;
                    double heightAtXZ1 = h10;

                    double xiZ0 = (h01 - h00) * 0.25;
                    double xzZ1 = (h11 - h10) * 0.25;

                    for (int xm = 0; xm < width; xm++) {
                        int offset = (xm + width * subX) << 11 | (subZ * width) << 7 | (subY * 8 + ym);
                        int step = 1 << 7;
                        offset -= step;

                        int defaultId = (subY * height + ym < seaLevel) ? 9 : 0;

                        double _h = h00;
                        double _hStep = (heightAtXZ1 - heightAtXZ0) * 0.25;
                        _h -= _hStep;

                        for (int zm = 0; zm < 4; zm++) {
                            int x = subX * width + xm;
                            int y = subY * height + ym;
                            int z = subZ * width + zm;
                            int blockId;
                            int distance;

                            // Falloff at the edge of the world, does not exist in Java Edition
                            if (getHeightFalloff(x, z, &distance) > (_h += _hStep)) {
                                blockId = 1;
                            } else {
                                blockId = defaultId;
                            }

                            if (distance == 0) {
                                int seaLevel = m_level->getSeaLevel();
                                if (y <= seaLevel - 10)
                                    blockId = 1;
                                else if (y < seaLevel)
                                    blockId = 9;
                            }

                            offset += step;
                            primer->setBlockAndData(offset, blockId, 0);
                        }

                        // Move to next x position
                        heightAtXZ0 += xiZ0;
                        heightAtXZ1 += xzZ1;
                    }

                    // Move to next y position
                    h00 += iy00;
                    h10 += iy10;
                    h01 += iy01;
                    h11 += iy11;
                }
            }
        }
    }

    PIXEndNamedEvent();

    delete[] heights.m_data;
    delete[] biomes.m_data;
}

std::vector<Biome::MobSpawnerData>* OverworldLevelSource::getMobsAt(MobCategory* category,
                                                                    const BlockPos& pos) {
    Biome* biome = m_level->getBiome(pos);

    if (m_shouldGenerateStructures) {
        if (MobCategory::MONSTER == category || MobCategory::SLIME == category) {
            if (m_randomScatteredLargeFeature->isSwamphut(pos))
                return m_randomScatteredLargeFeature->getSwamphutEnemies();
        }

        if (MobCategory::GUARDIAN == category && m_sourceSettings->m_useOceanMonuments) {
            if (m_oceanMonumentFeature->isInsideBoundingFeature(m_level, pos)) {
                // This seems to inline on Switch Edition?
                // return mOceanMonumentFeature->getEnemies();
                return &m_oceanMonumentFeature->MOB_SPAWNERS;
            }
        }
    }

    return biome->getMobs(category);
}

void OverworldLevelSource::recreateLogicStructuresForChunk(LevelChunk* chunk, int chunkX, int chunkZ) {
    if (m_shouldGenerateStructures) {
        if (m_sourceSettings->m_useMineshafts) {
            m_mineshaftFeature->apply(m_level, chunkX, chunkZ, nullptr);
        }
        if (m_sourceSettings->m_useVillages) {
            m_villageFeature->apply(m_level, chunkX, chunkZ, nullptr);
        }
        if (m_sourceSettings->m_useStrongholds) {
            m_strongholdFeature->apply(m_level, chunkX, chunkZ, nullptr);
        }
        if (m_sourceSettings->m_useScatteredFeatures) {
            m_randomScatteredLargeFeature->apply(m_level, chunkX, chunkZ, nullptr);
        }
        if (m_sourceSettings->m_useOceanMonuments) {
            m_oceanMonumentFeature->apply(m_level, chunkX, chunkZ, nullptr);
        }
        if (m_sourceSettings->m_useWoodlandMansions) {
            m_woodlandMansionFeature->apply(m_level, chunkX, chunkZ, nullptr);
        }
    }
}

// NON_MATCHING | Score: 860- (lower is better)
bool OverworldLevelSource::isPosInFeature(Level* level, const std::wstring& featureName,
                                          const BlockPos& pos) {
    if (!m_shouldGenerateStructures) {
        return false;
    }

    if (ChunkGenerator::STRONGHOLD_NAME.compare(featureName) == 0) {
        return m_strongholdFeature && m_strongholdFeature->isInsideFeature(pos);
    }
    if (ChunkGenerator::MANSION_NAME.compare(featureName) == 0) {
        return m_woodlandMansionFeature && m_woodlandMansionFeature->isInsideFeature(pos);
    }
    if (ChunkGenerator::MONUMENT_NAME.compare(featureName) == 0) {
        return m_oceanMonumentFeature && m_oceanMonumentFeature->isInsideFeature(pos);
    }
    if (ChunkGenerator::VILLAGE_NAME.compare(featureName) == 0) {
        return m_villageFeature && m_villageFeature->isInsideFeature(pos);
    }
    if (ChunkGenerator::MINESHAFT_NAME.compare(featureName) == 0) {
        return m_mineshaftFeature && m_mineshaftFeature->isInsideFeature(pos);
    }
    if (ChunkGenerator::TEMPLE_NAME.compare(featureName) == 0) {
        return m_randomScatteredLargeFeature && m_randomScatteredLargeFeature->isInsideFeature(pos);
    }

    return false;
}

BlockPos* OverworldLevelSource::findNearestMapFeature(Level* level, const std::wstring& featureName,
                                                      const BlockPos& pos, bool unk) {
    if (!m_shouldGenerateStructures)
        return nullptr;

    if (ChunkGenerator::STRONGHOLD_NAME == featureName && m_strongholdFeature)
        return m_strongholdFeature->getNearestGeneratedFeature(level, pos, unk);

    if (ChunkGenerator::MANSION_NAME == featureName && m_woodlandMansionFeature)
        return m_woodlandMansionFeature->getNearestGeneratedFeature(level, pos, unk);

    if (ChunkGenerator::MONUMENT_NAME == featureName && m_oceanMonumentFeature)
        return m_oceanMonumentFeature->getNearestGeneratedFeature(level, pos, unk);

    if (ChunkGenerator::VILLAGE_NAME == featureName && m_villageFeature)
        return m_villageFeature->getNearestGeneratedFeature(level, pos, unk);

    if (ChunkGenerator::MINESHAFT_NAME == featureName && m_mineshaftFeature)
        return m_mineshaftFeature->getNearestGeneratedFeature(level, pos, unk);

    if (ChunkGenerator::TEMPLE_NAME == featureName && m_randomScatteredLargeFeature)
        return m_randomScatteredLargeFeature->getNearestGeneratedFeature(level, pos, unk);

    return nullptr;
}
