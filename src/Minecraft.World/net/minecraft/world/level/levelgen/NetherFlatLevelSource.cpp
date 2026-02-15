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
    m_size = ceil((float)xzSize / hellScale);
    m_level = level;
    m_isGenerateMapFeatures = isGenerateMapFeatures;
    m_seed = new Random(seed);
    m_random = new Random(seed);
}

NetherFlatLevelSource::~NetherFlatLevelSource() {
    delete m_seed;
    delete m_random;
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
                    if (chunkX > m_random->nextInt(4) && x < -m_size / 2) {
                        primer->setState((y << 11) | (chunkX << 7) | chunkZ, bedrock);
                        unk = true;
                    }
                }

                if (chunkZ <= -adjusted / 2) {
                    if (chunkX - m_random->nextInt(4) <= 0 || z < -m_size / 2) {
                        primer->setState((y << 11) | (chunkX << 7) | chunkZ, bedrock);
                        unk = true;
                    }
                }

                if (chunkX <= -adjusted / 2 - 1) {
                    if (m_random->nextInt(4) + chunkX > 14 || x > m_size / 2) {
                        primer->setState((y << 11) | (chunkX << 7) | chunkZ, bedrock);
                        unk = true;
                    }
                }

                if (chunkZ <= -adjusted / 2 - 1) {
                    if (m_random->nextInt(4) + chunkX > 14 || z > m_size / 2) {
                        primer->setState((y << 11) | (chunkX << 7) | chunkZ, bedrock);
                        unk = true;
                    }
                }

                if (!unk) {
                    if (y >= 127 - m_random->nextInt(5)) {
                        primer->setState((y << 11) | (chunkX << 7) | chunkZ, bedrock);
                    } else if (y <= 0 + m_random->nextInt(5)) {
                        primer->setState((y << 11) | (chunkX << 7) | chunkZ, bedrock);
                    }
                }
            }
        }
    }
}

LevelChunk* NetherFlatLevelSource::createChunk(int x, int z) {
    m_seed->setSeed(0x4F9939F508LL * x + 0x1EF1565BD5LL * z);

    void* ids = XPhysicalAlloc(0x8000, 0xFFFFFFFFFFFFFFFFLL, 0x1000uLL, 4u);
    XMemSet128(ids, 0, 0x8000u);
    arrayWithLength<uchar> blockIds((uchar*)ids, 0x8000u);

    void* data = XPhysicalAlloc(0x4000, 0xFFFFFFFFFFFFFFFFLL, 0x1000uLL, 4u);
    XMemSet128(data, 0, 0x4000u);
    arrayWithLength<uchar> blockData((uchar*)data, 0x4000);

    ChunkPrimer primer = ChunkPrimer(false, blockIds, blockData);
    prepareHeights(x, z, &primer);
    buildSurfaces(x, z, &primer);

    LevelChunk* chunk = new LevelChunk(m_level, &primer, x, z);

    XPhysicalFree(ids);
    XPhysicalFree(data);

    return chunk;
}

// NON_MATCHING
void NetherFlatLevelSource::postProcess(int x, int z) {
    inPostProcessStep = true;

    Random* r = m_random;
    Level* l = m_level;

    int testX = 16 * x;
    int testZ = 16 * z;

    long long seed = l->getSeed();
    r->setSeed(seed);

    long seed1 = m_random->nextLong() | 1;
    long seed2 = m_random->nextLong() | 1;

    long long v16 = x * seed1 + z * seed2 ^ seed;

    m_random->setSeed(v16);

    int v11 = m_random->nextInt(10);
    int v12 = m_random->nextInt(v11 + 1) + 1;

    if (v12 > 0) {
        for (int i = 0; i < v12; ++i) {
            int posX = m_random->nextInt(16) + (testX | 8);
            int posY = m_random->nextInt(120) + 4;
            int posZ = m_random->nextInt(16) + (testZ | 8);

            HellFireFeature feature;
            feature.place(m_level, *m_random, BlockPos(posX, posY, posZ));
        }
    }

    int v31 = m_random->nextInt(m_random->nextInt(10) + 1);

    for (int i = 0; i < v31; i++) {
        int posX = m_random->nextInt(16) + (testX | 8);
        int posY = m_random->nextInt(120) + 4;
        int posZ = m_random->nextInt(16) + (testZ | 8);

        LightGemFeature feature;
        feature.place(m_level, *m_random, BlockPos(posX, posY, posZ));
    }

    inPostProcessStep = false;
    CConsoleMinecraftApp::sInstance.processSchematics(m_level->getChunk(x, z));
}

void NetherFlatLevelSource::lightChunk(LevelChunk* chunk) {
    return chunk->recalcHeightmap();
}

bool NetherFlatLevelSource::postProcessLoadedChunk(LevelChunk* chunk, int x, int z) {
    return false;
}

std::vector<Biome::MobSpawnerData>* NetherFlatLevelSource::getMobsAt(MobCategory* category,
                                                                     const BlockPos& pos) {
    Biome* biome = m_level->getBiome(pos);
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
