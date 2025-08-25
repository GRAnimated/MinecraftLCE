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
    mSize = level->getLevelData()->getXZSize();
    level->getLevelData()->fillMoatValues(&mIsClassicMoat, &mIsSmallMoat, &mIsMediumMoat);

    mLevel = level;
    mShouldGenerateStructures = generateStructures;
    mGeneratorType = level->getLevelData()->getGeneratorType();

    mCaveFeature = new LargeCaveFeature();
    mStrongholdFeature = new StrongholdFeature();
    mVillageFeature = new VillageFeature(level->getLevelData()->getXZSize());
    mMineshaftFeature = new MineShaftFeature();
    mRandomScatteredLargeFeature = new RandomScatteredLargeFeature();
    mCanyonFeature = new CanyonFeature();
    mOceanMonumentFeature = new OceanMonumentFeature();
    mWoodlandMansionFeature = new WoodlandMansionFeature(this);
    mRandom = Random(seed);
    mRandom2 = Random(seed);
    mMinLimitPerlinNoise = new PerlinNoise(&mRandom, 16);
    mMaxLimitPerlinNoise = new PerlinNoise(&mRandom, 16);
    mMainNoise = new PerlinNoise(&mRandom, 8);
    mSurfaceNoise = new PerlinSimplexNoise(&mRandom, 4);
    mScaleNoise = new PerlinNoise(&mRandom, 10);
    mDepthNoise = new PerlinNoise(&mRandom, 16);
    qword_78 = nullptr;
    qword_80 = nullptr;
    field_88 = new PerlinNoise(&mRandom, 8);

    for (int i = -2; i <= 2; ++i) {
        for (int j = -2; j <= 2; ++j) {
            float f = 10.0f / sqrtf((float)(i * i + j * j) + 0.2f);
            mBiomeWeights[i + 2 + (j + 2) * 5] = f;
        }
    }

    mOceanBlock = Blocks::WATER->defaultBlockState();

    CustomizableSourceSettings::Builder* builder;

    if (!sourceSettings) {
        builder = new CustomizableSourceSettings::Builder();
        mSourceSettings = new CustomizableSourceSettings(builder);

    } else {
        builder = CustomizableSourceSettings::Builder::fromString(sourceSettings);
        mSourceSettings = builder->build();
        if (mSourceSettings->useLavaOceans)
            mOceanBlock = Blocks::LAVA->defaultBlockState();
        else
            mOceanBlock = Blocks::WATER->defaultBlockState();

        level->setSeaLevel(mSourceSettings->seaLevel);
    }

    delete builder;
}

OverworldLevelSource::~OverworldLevelSource() {
    delete mCaveFeature;
    delete mStrongholdFeature;
    delete mVillageFeature;
    delete mMineshaftFeature;
    delete mRandomScatteredLargeFeature;
    delete mCanyonFeature;
    delete mOceanMonumentFeature;
    delete mWoodlandMansionFeature;
    delete mMinLimitPerlinNoise;
    delete mMaxLimitPerlinNoise;
    delete mMainNoise;
    delete mSurfaceNoise;
    delete mScaleNoise;
    delete mDepthNoise;
    delete qword_78;
    delete qword_80;
    delete field_88;
    delete mSourceSettings;
    delete qword_120.data;
}

float OverworldLevelSource::getHeightFalloff(int chunkX, int chunkZ, int* distance) {
    int size = mSize * 16;
    int nearestDist = distanceToEdge(32.0f, 0, chunkX, chunkZ, size);

    MoatCheck moatChecks[] = {{mIsClassicMoat, 864}, {mIsSmallMoat, 1024}, {mIsMediumMoat, 3072}};

    for (auto& check : moatChecks) {
        if (check.enabled && size > check.limit) {
            int d = distanceToEdge(32.0f, nearestDist, chunkX, chunkZ, check.limit);
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
        = mSurfaceNoise->getRegion(noiseRegion, chunkX * 16, chunkZ * 16, 16, 16, 0.0625, 0.0625, 1.0);

    PIXEndNamedEvent();

    for (int x = 0; x < 16; x++) {
        for (int z = 0; z < 16; z++) {
            Biome* biome = biomes[z + x * 16];
            {
                std::wstring biomeName = biome->getName(false);
                PIXBeginNamedEvent(0.0, "Building surface for biome %ls", biomeName.c_str());
            }

            biome->buildSurfaceAt(mLevel, mRandom, primer, chunkX * 16 + x, chunkZ * 16 + z,
                                  noiseRegion[z + x * 16]);

            PIXEndNamedEvent();
        }
    }

    delete noiseRegion.data;
}

LevelChunk* OverworldLevelSource::createChunk(int chunkX, int chunkZ) {
    mRandom.setSeed(341873128712 * chunkX + 132897987541 * chunkZ);

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
    mLevel->getBiomeSource()->getBiomeBlock(biomes, 16 * chunkX, 16 * chunkZ, 16, 16, true);
    PIXEndNamedEvent();

    PIXBeginNamedEvent(0.0, "Building surfaces");
    buildSurfaces(chunkX, chunkZ, &primer, biomes);
    PIXEndNamedEvent();

    delete biomes.data;

    if (mSourceSettings->useCaves) {
        PIXBeginNamedEvent(0.0, "Applying caves");
        mCaveFeature->apply(mLevel, chunkX, chunkZ, &primer);
        PIXEndNamedEvent();
    }

    if (mSourceSettings->byte_52) {
        PIXBeginNamedEvent(0.0, "Applying ravines");
        mCanyonFeature->apply(mLevel, chunkX, chunkZ, &primer);
        PIXEndNamedEvent();
    }

    if (mShouldGenerateStructures) {
        if (mSourceSettings->useMineshafts) {
            PIXBeginNamedEvent(0.0, "Applying mineshafts");
            mMineshaftFeature->apply(mLevel, chunkX, chunkZ, &primer);
            PIXEndNamedEvent();
        }
        if (mSourceSettings->useVillages) {
            PIXBeginNamedEvent(0.0, "Applying villages");
            mVillageFeature->apply(mLevel, chunkX, chunkZ, &primer);
            PIXEndNamedEvent();
        }
        if (mSourceSettings->useStrongholds) {
            PIXBeginNamedEvent(0.0, "Applying strongholds");
            mStrongholdFeature->apply(mLevel, chunkX, chunkZ, &primer);
            PIXEndNamedEvent();
        }
        if (mSourceSettings->useScatteredFeatures) {
            PIXBeginNamedEvent(0.0, "Applying scatterd features");
            mRandomScatteredLargeFeature->apply(mLevel, chunkX, chunkZ, &primer);
            PIXEndNamedEvent();
        }
        if (mSourceSettings->useOceanMonuments) {
            PIXBeginNamedEvent(0.0, "Applying ocean monuments");
            mOceanMonumentFeature->apply(mLevel, chunkX, chunkZ, &primer);
            PIXEndNamedEvent();
        }
        if (mSourceSettings->useWoodlandMansions) {
            PIXBeginNamedEvent(0.0, "Applying woodland mansions");
            mWoodlandMansionFeature->apply(mLevel, chunkX, chunkZ, &primer);
            PIXEndNamedEvent();
        }
    }

    PIXBeginNamedEvent(0.0, "Creating chunk");
    LevelChunk* chunk = new LevelChunk(mLevel, &primer, chunkX, chunkZ);
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

    float coordinateScale = mSourceSettings->coordinateScale;
    float heightScale = mSourceSettings->heightScale;

    depthNoise
        = mDepthNoise->getRegion(depthNoise, posX, posZ, 5, 5, mSourceSettings->depthNoiseScaleX,
                                 mSourceSettings->depthNoiseScaleZ, mSourceSettings->depthNoiseScaleExponent);

    mainNoise = mMainNoise->getRegion(
        mainNoise, posX, posY, posZ, 5, 17, 5, coordinateScale / mSourceSettings->mainNoiseScaleX,
        heightScale / mSourceSettings->mainNoiseScaleY, coordinateScale / mSourceSettings->mainNoiseScaleZ);

    minLimitNoise = mMinLimitPerlinNoise->getRegion(minLimitNoise, posX, posY, posZ, 5, 17, 5,
                                                    coordinateScale, heightScale, coordinateScale);

    maxLimitNoise = mMaxLimitPerlinNoise->getRegion(maxLimitNoise, posX, posY, posZ, 5, 17, 5,
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

                    float depth = mSourceSettings->biomeDepthOffset
                                  + (b2->getDepth() * mSourceSettings->biomeDepthWeight);

                    float scale = mSourceSettings->biomeScaleOffset
                                  + (b2->getScale() * mSourceSettings->biomeScaleWeight);

                    if (mGeneratorType == LevelType::AMPLIFIED && depth > 0.0f) {
                        depth = depth * 2.0f + 1.0f;
                        scale = scale * 4.0f + 1.0f;
                    }

                    float weight = mBiomeWeights[(xo + 2) + (zo + 2) * 5] / (depth + 2.0f);
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
            baseSize = baseSize * mSourceSettings->baseSize / 8.0;
            double baseHeight = mSourceSettings->baseSize + baseSize * 4.0;

            for (int y = 0; y < 17; ++y) {
                double yOffset = (y - baseHeight) * mSourceSettings->stretchY * 128.0 / 128.0 / d9;

                if (yOffset < 0.0) {
                    yOffset *= 4.0;
                }

                double minNoiseVal = minLimitNoise[i] / mSourceSettings->upperLimitScale;
                double maxNoiseVal = maxLimitNoise[i] / mSourceSettings->lowerLimitScale;
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

    delete[] mainNoise.data;
    delete[] minLimitNoise.data;
    delete[] maxLimitNoise.data;
    delete[] depthNoise.data;
    delete[] unk.data;
    delete[] unk2.data;
}

void OverworldLevelSource::postProcess(int chunkX, int chunkZ) {
    ChunkGenerator::inPostProcessStep = true;

    BlockPos origin(chunkX * 16, 0, chunkZ * 16);
    Biome* biome = mLevel->getBiome(origin.offset(16, 0, 16));

    mRandom2.setSeed(mLevel->getSeed());

    long long t1 = mRandom2.nextLong() / 2 * 2 + 1;
    long long t2 = mRandom2.nextLong() / 2 * 2 + 1;

    long long mixed = t1 * chunkX + t2 * chunkZ;
    mRandom2.setSeed(mixed ^ mLevel->getSeed());

    ChunkPos chunkPos(chunkX, chunkZ);

    PIXBeginNamedEvent(0.0, "Structure postprocessing");

    bool villageFlag = false;

    if (mShouldGenerateStructures) {
        if (mSourceSettings->useMineshafts) {
            mMineshaftFeature->postProcess(mLevel, mRandom2, &chunkPos);
        }

        if (mSourceSettings->useVillages) {
            villageFlag = mVillageFeature->postProcess(mLevel, mRandom2, &chunkPos);
        }

        if (mSourceSettings->useStrongholds) {
            mStrongholdFeature->postProcess(mLevel, mRandom2, &chunkPos);
        }

        if (mSourceSettings->useScatteredFeatures) {
            mRandomScatteredLargeFeature->postProcess(mLevel, mRandom2, &chunkPos);
        }

        if (mSourceSettings->useOceanMonuments) {
            mOceanMonumentFeature->postProcess(mLevel, mRandom2, &chunkPos);
        }

        if (mSourceSettings->useWoodlandMansions) {
            mWoodlandMansionFeature->postProcess(mLevel, mRandom2, &chunkPos);
        }
    }

    PIXEndNamedEvent();

    PIXBeginNamedEvent(0.0, "Lakes");

    if (biome != Biome::DESERT && biome != Biome::DESERT_HILLS) {
        if (mSourceSettings->useWaterLakes) {
            if (!villageFlag && mRandom2.nextInt(mSourceSettings->waterLakeChance) == 0) {
                int rx = mRandom2.nextInt(16) + 8;
                int ry = mRandom2.nextInt(128);
                int rz = mRandom2.nextInt(16) + 8;

                LakeFeature(Blocks::WATER).place(mLevel, mRandom2, origin.offset(rx, ry, rz));
            }
        }
    }
    PIXEndNamedEvent();

    PIXBeginNamedEvent(0.0, "Lava");
    if (!villageFlag && mRandom2.nextInt(mSourceSettings->lavaLakeChance / 10) == 0
        && mSourceSettings->useLavaLakes) {
        int rx = mRandom2.nextInt(16) + 8;
        int maxY = mRandom2.nextInt(120);
        int ry = mRandom2.nextInt(maxY + 8);
        int rz = mRandom2.nextInt(16) + 8;

        if (ry < mLevel->getSeaLevel() || mRandom2.nextInt(mSourceSettings->lavaLakeChance / 8) == 0) {
            LakeFeature(Blocks::LAVA).place(mLevel, mRandom2, origin.offset(rx, ry, rz));
        }
    }

    PIXEndNamedEvent();

    PIXBeginNamedEvent(0.0, "Monster rooms");
    if (mSourceSettings->useDungeons) {
        MonsterRoomFeature dungeonGen;
        if (mSourceSettings->dungeonChance >= 1) {
            for (int i = 0; i < mSourceSettings->dungeonChance; ++i) {
                int rx = mRandom2.nextInt(16) + 8;
                int ry = mRandom2.nextInt(128);
                int rz = mRandom2.nextInt(16) + 8;
                dungeonGen.place(mLevel, mRandom2, origin.offset(rx, ry, rz));
            }
        }
    }
    PIXEndNamedEvent();

    PIXBeginNamedEvent(0.0, "Biome decorate");
    biome->decorate(mLevel, mRandom2, BlockPos(chunkX * 16, 0, chunkZ * 16));
    PIXEndNamedEvent();

    PIXBeginNamedEvent(0.0, "Post process mobs");
    PIXEndNamedEvent();

    PIXBeginNamedEvent(0.0, "Update ice and snow");

    origin = origin.offset(8, 0, 8);
    for (int x = 0; x < 16; x++) {
        for (int z = 0; z < 16; z++) {
            BlockPos top = mLevel->getTopRainBlockPos(origin.offset(x, 0, z));
            BlockPos below = top.below();

            if (mLevel->shouldFreezeIgnoreNeighbors(below)) {
                mLevel->setBlock(below, Blocks::ICE->defaultBlockState(), 2, 0);
            }

            if (mLevel->shouldSnow(top, true)) {
                mLevel->setBlock(top, Blocks::SNOW_LAYER->defaultBlockState(), 2, 0);
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

    int seaLevel = mLevel->mSeaLevel;
    arrayWithLength<Biome*> biomes;

    PIXBeginNamedEvent(0.0, "Getting raw biome block");
    mLevel->getBiomeSource()->getRawBiomeBlock(biomes, chunkX * 4 - 2, chunkZ * 4 - 2, 10, 10);
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
                                int seaLevel = mLevel->getSeaLevel();
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

    delete[] heights.data;
    delete[] biomes.data;
}

std::vector<Biome::MobSpawnerData>* OverworldLevelSource::getMobsAt(MobCategory* category,
                                                                    const BlockPos& pos) {
    Biome* biome = mLevel->getBiome(pos);

    if (mShouldGenerateStructures) {
        if (MobCategory::MONSTER == category || MobCategory::SLIME == category) {
            if (mRandomScatteredLargeFeature->isSwamphut(pos))
                return mRandomScatteredLargeFeature->getSwamphutEnemies();
        }

        if (MobCategory::GUARDIAN == category && mSourceSettings->useOceanMonuments) {
            if (mOceanMonumentFeature->isInsideBoundingFeature(mLevel, pos)) {
                // This seems to inline on Switch Edition?
                // return mOceanMonumentFeature->getEnemies();
                return &mOceanMonumentFeature->MOB_SPAWNERS;
            }
        }
    }

    return biome->getMobs(category);
}

void OverworldLevelSource::recreateLogicStructuresForChunk(LevelChunk* chunk, int chunkX, int chunkZ) {
    if (mShouldGenerateStructures) {
        if (mSourceSettings->useMineshafts) {
            mMineshaftFeature->apply(mLevel, chunkX, chunkZ, nullptr);
        }
        if (mSourceSettings->useVillages) {
            mVillageFeature->apply(mLevel, chunkX, chunkZ, nullptr);
        }
        if (mSourceSettings->useStrongholds) {
            mStrongholdFeature->apply(mLevel, chunkX, chunkZ, nullptr);
        }
        if (mSourceSettings->useScatteredFeatures) {
            mRandomScatteredLargeFeature->apply(mLevel, chunkX, chunkZ, nullptr);
        }
        if (mSourceSettings->useOceanMonuments) {
            mOceanMonumentFeature->apply(mLevel, chunkX, chunkZ, nullptr);
        }
        if (mSourceSettings->useWoodlandMansions) {
            mWoodlandMansionFeature->apply(mLevel, chunkX, chunkZ, nullptr);
        }
    }
}

// NON_MATCHING | Score: 860- (lower is better)
bool OverworldLevelSource::isPosInFeature(Level* level, const std::wstring& featureName,
                                          const BlockPos& pos) {
    if (!mShouldGenerateStructures) {
        return false;
    }

    if (ChunkGenerator::STRONGHOLD_NAME.compare(featureName) == 0) {
        return mStrongholdFeature && mStrongholdFeature->isInsideFeature(pos);
    }
    if (ChunkGenerator::MANSION_NAME.compare(featureName) == 0) {
        return mWoodlandMansionFeature && mWoodlandMansionFeature->isInsideFeature(pos);
    }
    if (ChunkGenerator::MONUMENT_NAME.compare(featureName) == 0) {
        return mOceanMonumentFeature && mOceanMonumentFeature->isInsideFeature(pos);
    }
    if (ChunkGenerator::VILLAGE_NAME.compare(featureName) == 0) {
        return mVillageFeature && mVillageFeature->isInsideFeature(pos);
    }
    if (ChunkGenerator::MINESHAFT_NAME.compare(featureName) == 0) {
        return mMineshaftFeature && mMineshaftFeature->isInsideFeature(pos);
    }
    if (ChunkGenerator::TEMPLE_NAME.compare(featureName) == 0) {
        return mRandomScatteredLargeFeature && mRandomScatteredLargeFeature->isInsideFeature(pos);
    }

    return false;
}

BlockPos* OverworldLevelSource::findNearestMapFeature(Level* level, const std::wstring& featureName,
                                                      const BlockPos& pos, bool unk) {
    if (!mShouldGenerateStructures)
        return nullptr;

    if (ChunkGenerator::STRONGHOLD_NAME == featureName && mStrongholdFeature)
        return mStrongholdFeature->getNearestGeneratedFeature(level, pos, unk);

    if (ChunkGenerator::MANSION_NAME == featureName && mWoodlandMansionFeature)
        return mWoodlandMansionFeature->getNearestGeneratedFeature(level, pos, unk);

    if (ChunkGenerator::MONUMENT_NAME == featureName && mOceanMonumentFeature)
        return mOceanMonumentFeature->getNearestGeneratedFeature(level, pos, unk);

    if (ChunkGenerator::VILLAGE_NAME == featureName && mVillageFeature)
        return mVillageFeature->getNearestGeneratedFeature(level, pos, unk);

    if (ChunkGenerator::MINESHAFT_NAME == featureName && mMineshaftFeature)
        return mMineshaftFeature->getNearestGeneratedFeature(level, pos, unk);

    if (ChunkGenerator::TEMPLE_NAME == featureName && mRandomScatteredLargeFeature)
        return mRandomScatteredLargeFeature->getNearestGeneratedFeature(level, pos, unk);

    return nullptr;
}
