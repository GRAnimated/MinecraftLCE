#include "net/minecraft/world/level/levelgen/NetherFlatLevelSource.h"

#include "NX/Platform.h"
#include "net/minecraft/client/CMinecraftApp.h"
#include "net/minecraft/world/ArrayWithLength.h"
#include "net/minecraft/world/Random.h"
#include "net/minecraft/world/level/Level.h"
#include "net/minecraft/world/level/biome/Biome.h"
#include "net/minecraft/world/level/block/Blocks.h"
#include "net/minecraft/world/level/chunk/LevelChunk.h"
#include "net/minecraft/world/level/levelgen/ChunkPrimer.h"
#include "net/minecraft/world/level/levelgen/feature/HellFireFeature.h"
#include "net/minecraft/world/level/levelgen/feature/LightGemFeature.h"
#include "net/minecraft/world/level/storage/LevelData.h"

NetherFlatLevelSource::NetherFlatLevelSource(Level* level, bool isGenerateMapFeatures, long long seed) {
    int xzSize = level->getLevelData()->getXZSize();
    int hellScale = level->getLevelData()->getHellScale();
    mSize = ceil((float)xzSize / hellScale);
    mLevel = level;
    mIsGenerateMapFeatures = isGenerateMapFeatures;
    mSeed = new Random(seed);
    mRandom = new Random(seed);
}

NetherFlatLevelSource::~NetherFlatLevelSource() {
    delete mSeed;
    delete mRandom;
}

void NetherFlatLevelSource::prepareHeights(int x, int z, ChunkPrimer* primer) {
    for (int cX = 0; cX < 16; cX++) {
        for (int cZ = 0; cZ < 16; cZ++) {
            for (int cY = 0; cY < 16; cY++) {
                const BlockState* block = Blocks::AIR->defaultBlockState();
                if (cY <= 6)
                    block = Blocks::NETHERRACK->defaultBlockState();
                primer->setState((cX << 11) | (cZ << 7) | cY, block);
            }
        }
    }
}

// NON_MATCHING
void NetherFlatLevelSource::buildSurfaces(int x, int z, ChunkPrimer* primer) {
    const BlockState* bedrock = Blocks::BEDROCK->defaultBlockState();

    for (int chunkX = 0; chunkX < 16; ++chunkX) {
        for (int chunkZ = 0; chunkZ < 16; ++chunkZ) {
            for (int y = 127; y >= 0; --y) {
                int adjusted = (chunkZ * 16 + chunkX) * 128 + y;

                bool unk = false;

                if (chunkX <= -adjusted / 2) {
                    if (chunkX > mRandom->nextInt(4) && x < -mSize / 2) {
                        primer->setState((y << 11) | (chunkX << 7) | chunkZ, bedrock);
                        unk = true;
                    }
                }

                if (chunkZ <= -adjusted / 2) {
                    if (chunkX - mRandom->nextInt(4) <= 0 || z < -mSize / 2) {
                        primer->setState((y << 11) | (chunkX << 7) | chunkZ, bedrock);
                        unk = true;
                    }
                }

                if (chunkX <= -adjusted / 2 - 1) {
                    if (mRandom->nextInt(4) + chunkX > 14 || x > mSize / 2) {
                        primer->setState((y << 11) | (chunkX << 7) | chunkZ, bedrock);
                        unk = true;
                    }
                }

                if (chunkZ <= -adjusted / 2 - 1) {
                    if (mRandom->nextInt(4) + chunkX > 14 || z > mSize / 2) {
                        primer->setState((y << 11) | (chunkX << 7) | chunkZ, bedrock);
                        unk = true;
                    }
                }

                if (!unk) {
                    if (y >= 127 - mRandom->nextInt(5)) {
                        primer->setState((y << 11) | (chunkX << 7) | chunkZ, bedrock);
                    } else if (y <= 0 + mRandom->nextInt(5)) {
                        primer->setState((y << 11) | (chunkX << 7) | chunkZ, bedrock);
                    }
                }
            }
        }
    }
}

LevelChunk* NetherFlatLevelSource::createChunk(int x, int z) {
    mSeed->setSeed(0x4F9939F508LL * x + 0x1EF1565BD5LL * z);

    void* ids = XPhysicalAlloc(0x8000, 0xFFFFFFFFFFFFFFFFLL, 0x1000uLL, 4u);
    XMemSet128(ids, 0, 0x8000u);
    arrayWithLength<uchar> blockIds((uchar*)ids, 0x8000u);

    void* data = XPhysicalAlloc(0x4000, 0xFFFFFFFFFFFFFFFFLL, 0x1000uLL, 4u);
    XMemSet128(data, 0, 0x4000u);
    arrayWithLength<uchar> blockData((uchar*)data, 0x4000);

    ChunkPrimer primer = ChunkPrimer(false, blockIds, blockData);
    prepareHeights(x, z, &primer);
    buildSurfaces(x, z, &primer);

    LevelChunk* chunk = new LevelChunk(mLevel, &primer, x, z);

    XPhysicalFree(ids);
    XPhysicalFree(data);

    return chunk;
}

// NON_MATCHING
void NetherFlatLevelSource::postProcess(int x, int z) {
    inPostProcessStep = true;

    Random* r = mRandom;
    Level* l = mLevel;

    int testX = 16 * x;
    int testZ = 16 * z;

    long long seed = l->getSeed();
    r->setSeed(seed);

    long seed1 = mRandom->nextLong() | 1;
    long seed2 = mRandom->nextLong() | 1;

    long long v16 = x * seed1 + z * seed2 ^ seed;

    mRandom->setSeed(v16);

    int v11 = mRandom->nextInt(10);
    int v12 = mRandom->nextInt(v11 + 1) + 1;

    if (v12 > 0) {
        for (int i = 0; i < v12; ++i) {
            int posX = mRandom->nextInt(16) + (testX | 8);
            int posY = mRandom->nextInt(120) + 4;
            int posZ = mRandom->nextInt(16) + (testZ | 8);

            HellFireFeature feature;
            feature.place(mLevel, *mRandom, BlockPos(posX, posY, posZ));
        }
    }

    int v31 = mRandom->nextInt(mRandom->nextInt(10) + 1);

    for (int i = 0; i < v31; i++) {
        int posX = mRandom->nextInt(16) + (testX | 8);
        int posY = mRandom->nextInt(120) + 4;
        int posZ = mRandom->nextInt(16) + (testZ | 8);

        LightGemFeature feature;
        feature.place(mLevel, *mRandom, BlockPos(posX, posY, posZ));
    }

    inPostProcessStep = false;
    CConsoleMinecraftApp::sInstance.processSchematics(mLevel->getChunk(x, z));
}

void NetherFlatLevelSource::lightChunk(LevelChunk* chunk) {
    return chunk->recalcHeightmap();
}

bool NetherFlatLevelSource::postProcessLoadedChunk(LevelChunk* chunk, int x, int z) {
    return false;
}

std::vector<Biome::MobSpawnerData>* NetherFlatLevelSource::getMobsAt(MobCategory* category,
                                                                     const BlockPos& pos) {
    Biome* biome = mLevel->getBiome(pos);
    if (biome)
        return biome->getMobs(category);

    return nullptr;
}

BlockPos* NetherFlatLevelSource::findNearestMapFeature(Level* level, const std::wstring& name,
                                                       const BlockPos& pos, bool flag) {
    return nullptr;
}

void NetherFlatLevelSource::recreateLogicStructuresForChunk(LevelChunk* chunk, int x, int z) {
    return;
}

bool NetherFlatLevelSource::isPosInFeature(Level* level, const std::wstring& name, const BlockPos& pos) {
    return false;
}
