#include "NX/Platform.h"
#include "net/minecraft/world/level/Level.h"
#include "net/minecraft/world/level/biome/Biome.h"
#include "net/minecraft/world/level/biome/BiomeSource.h"
#include "net/minecraft/world/level/block/Blocks.h"
#include "net/minecraft/world/level/chunk/LevelChunk.h"
#include "net/minecraft/world/level/levelgen/ChunkPrimer.h"
#include "net/minecraft/world/level/levelgen/CustomizableSourceSettings.h"
#include "net/minecraft/world/level/levelgen/OverworldLevelSource.h"
#include "net/minecraft/world/level/levelgen/feature/CanyonFeature.h"
#include "net/minecraft/world/level/levelgen/feature/LargeCaveFeature.h"
#include "net/minecraft/world/level/levelgen/feature/MineShaftFeature.h"
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

// NON_MATCHING | Score: 1668 (lower is better)
float OverworldLevelSource::getHeightFalloff(int x, int z, int* distance) {
    bool isClassicMoat = mIsClassicMoat;
    bool isSmallMoat = mIsSmallMoat;
    bool isMediumMoat = mIsMediumMoat;

    int size = 16 * mSize;
    int res = unkMethod(32.0f, 0, x, z, size);
    int t = res;

    if (isClassicMoat && size > 864) {
        int n = unkMethod(32.0f, res, x, z, 864);
        if (n < t)
            t = n;
    }

    if (isSmallMoat && size > 1024) {
        int n = unkMethod(32.0f, res, x, z, 1024);
        if (n < t)
            t = n;
    }

    if (isMediumMoat && size > 3072) {
        int n = unkMethod(32.0f, res, x, z, 3072);
        if (n < t)
            t = n;
    }

    float result = 0.0;

    if (t <= 32) {
        result = (32 - t) * 0.03125f * 128.0f;
    }

    *distance = t;
    return result;
}

int OverworldLevelSource::unkMethod(float a, int b, int x, int z, int size) {
    return (int)(a * (float)(x * x + z * z) / (float)size);
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
    void* ids = XPhysicalAlloc(0x8000, 0xFFFFFFFFFFFFFFFF, 0x1000, 4u);
    XMemSet128(ids, 0, 0x8000);
    arrayWithLength<uchar> blockIds((uchar*)ids, 0x8000u);
    void* data = XPhysicalAlloc(0x4000, 0xFFFFFFFFFFFFFFFF, 0x1000, 4u);
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
        if (mSourceSettings->byte_4E) {
            PIXBeginNamedEvent(0.0, "Applying mineshafts");
            mMineshaftFeature->apply(mLevel, chunkX, chunkZ, &primer);
            PIXEndNamedEvent();
        }
        if (mSourceSettings->byte_4D) {
            PIXBeginNamedEvent(0.0, "Applying villages");
            mVillageFeature->apply(mLevel, chunkX, chunkZ, &primer);
            PIXEndNamedEvent();
        }
        if (mSourceSettings->byte_4C) {
            PIXBeginNamedEvent(0.0, "Applying strongholds");
            mStrongholdFeature->apply(mLevel, chunkX, chunkZ, &primer);
            PIXEndNamedEvent();
        }
        if (mSourceSettings->byte_4F) {
            PIXBeginNamedEvent(0.0, "Applying scatterd features");
            mRandomScatteredLargeFeature->apply(mLevel, chunkX, chunkZ, &primer);
            PIXEndNamedEvent();
        }
        if (mSourceSettings->byte_50) {
            PIXBeginNamedEvent(0.0, "Applying ocean monuments");
            mOceanMonumentFeature->apply(mLevel, chunkX, chunkZ, &primer);
            PIXEndNamedEvent();
        }
        if (mSourceSettings->byte_51) {
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

bool OverworldLevelSource::postProcessLoadedChunk(LevelChunk*, int, int) {
    return false;
}

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
