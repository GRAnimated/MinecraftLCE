#pragma once

#include "net/minecraft/world/ArrayWithLength.h"
#include "net/minecraft/world/Random.h"
#include "net/minecraft/world/level/chunk/ChunkGenerator.h"
#include "types.h"

class ChunkPrimer;
class PerlinNoise;
class Feature;
class NetherBridgeFeature;
class LargeHellCaveFeature;
class FjNetherrackBlockPred;

class NetherLevelSource : public ChunkGenerator {
public:
    static const std::wstring FORTRESS_NAME;
    static const FjNetherrackBlockPred NETHERRACK_PREDICATE;

    NetherLevelSource(Level*, bool generateStructures, long long seed);
    ~NetherLevelSource() override;
    LevelChunk* createChunk(int, int) override;
    void postProcess(int, int) override;
    bool postProcessLoadedChunk(LevelChunk*, int, int) override;
    std::vector<Biome::MobSpawnerData*>* getMobsAt(MobCategory*, const BlockPos&) override;
    BlockPos* findNearestMapFeature(Level*, const std::wstring&, const BlockPos&, bool) override;
    void recreateLogicStructuresForChunk(LevelChunk*, int, int) override;
    bool isPosInFeature(Level*, const std::wstring&, const BlockPos&) override;
    void lightChunk(LevelChunk*) override;
    virtual arrayWithLength<double> getHeights(arrayWithLength<double>, int, int, int, int, int, int);

    void prepareHeights(int, int, ChunkPrimer*);
    void buildSurfaces(int, int, ChunkPrimer*);

    Level* m_level;
    bool m_generateStructures;
    Random m_random;
    Random m_populationRandom;
    PerlinNoise* m_minLimitNoise;
    PerlinNoise* m_maxLimitNoise;
    PerlinNoise* m_mainNoise;
    PerlinNoise* m_soulSandNoise;
    PerlinNoise* m_surfaceNoise;
    PerlinNoise* m_scaleNoise;
    PerlinNoise* m_depthNoise;
    Feature* m_fire;
    Feature* m_glowstone;
    Feature* m_portal;
    Feature* m_quartz;
    Feature* m_magma;
    Feature* m_enclosedLava;
    Feature* m_openLava;
    Feature* m_brownMushroom;
    Feature* m_redMushroom;
    NetherBridgeFeature* m_fortress;
    LargeHellCaveFeature* m_caves;
};

ASSERT_SIZEOF(NetherLevelSource, 0xe0)
