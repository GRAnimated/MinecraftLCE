#pragma once

#include "net/minecraft/core/BlockPos.h"
#include "net/minecraft/world/ArrayWithLength.h"
#include "net/minecraft/world/level/chunk/ChunkGenerator.h"
#include "types.h"

class ChunkPrimer;
class Random;
class PerlinNoise;
class SimplexNoise;
class EndCityFeature;
class EndIslandFeature;

class TheEndLevelSource : public ChunkGenerator {
public:
    TheEndLevelSource(Level*, bool, long long, const BlockPos&);
    ~TheEndLevelSource() override;
    LevelChunk* createChunk(int, int) override;
    void postProcess(int, int) override;
    bool postProcessLoadedChunk(LevelChunk*, int, int) override;
    std::vector<Biome::MobSpawnerData>* getMobsAt(MobCategory*, const BlockPos&) override;
    BlockPos* findNearestMapFeature(Level*, const std::wstring&, const BlockPos&, bool) override;
    void recreateLogicStructuresForChunk(LevelChunk*, int, int) override;
    bool isPosInFeature(Level*, const std::wstring&, const BlockPos&) override;

    void prepareHeights(int, int, ChunkPrimer*);
    arrayWithLength<double> getHeights(arrayWithLength<double>, int, int, int, int, int, int);
    void buildSurfaces(ChunkPrimer*);
    bool fjIslandCheck(int, int);
    double fjIslandProximity(int, int);
    float getIslandHeightValue(int, int, int, int);

    Random* m_random;
    Random* m_decorationRandom;
    PerlinNoise* m_minLimitNoise;
    PerlinNoise* m_maxLimitNoise;
    PerlinNoise* m_mainNoise;
    PerlinNoise* m_scaleNoise;
    PerlinNoise* m_depthNoise;
    Level* m_level;
    bool m_generateStructures;
    BlockPos m_spawn;
    EndCityFeature* m_endCity;
    SimplexNoise* m_islandNoise;
    arrayWithLength<Biome*> m_biomes;
    EndIslandFeature* m_islandFeature;
};

ASSERT_SIZEOF(TheEndLevelSource, 0x88)
