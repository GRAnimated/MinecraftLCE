#pragma once

#include "net/minecraft/world/ArrayWithLength.h"
#include "net/minecraft/world/Random.h"
#include "net/minecraft/world/level/chunk/ChunkGenerator.h"
#include "net/minecraft/world/level/levelgen/CustomizableSourceSettings.h"
#include "net/minecraft/world/level/levelgen/GenericOverworldLevelSource.h"

#include "types.h"

class Biome;
class ChunkPrimer;
class SuperflatConfig;
class LevelType;
class BlockState;
class LargeCaveFeature;
class LargeFeature;
class PerlinNoise;
class PerlinSimplexNoise;
class StrongholdFeature;
class VillageFeature;
class MineShaftFeature;
class RandomScatteredLargeFeature;
class CanyonFeature;
class OceanMonumentFeature;
class WoodlandMansionFeature;

class OverworldLevelSource : public ChunkGenerator, public GenericOverworldLevelSource {
public:
    struct MoatCheck {
        bool m_enabled;
        int m_limit;
    };

    OverworldLevelSource(Level* level, long long seed, bool generateStructures,
                         SuperflatConfig* sourceSettings);
    ~OverworldLevelSource() override;
    LevelChunk* createChunk(int, int) override;
    void postProcess(int, int) override;
    bool postProcessLoadedChunk(LevelChunk*, int, int) override;
    std::vector<Biome::MobSpawnerData>* getMobsAt(MobCategory*, const BlockPos&) override;
    BlockPos* findNearestMapFeature(Level*, const std::wstring&, const BlockPos&, bool) override;
    void recreateLogicStructuresForChunk(LevelChunk*, int, int) override;
    bool isPosInFeature(Level*, const std::wstring&, const BlockPos&) override;
    void lightChunk(LevelChunk*) override;
    void prepareHeights(int, int, ChunkPrimer*) override;

    void getHeights(int, int, int, arrayWithLength<Biome*>&, arrayWithLength<double>&);
    void buildSurfaces(int, int, ChunkPrimer*, arrayWithLength<Biome*>);
    float getHeightFalloff(int x, int z, int* height);
    static int distanceToEdge(float, int, int x, int z, int size);  // made up name

    Random m_random;
    Random m_random2;
    PerlinNoise* m_minLimitPerlinNoise;
    PerlinNoise* m_maxLimitPerlinNoise;
    PerlinNoise* m_mainNoise;
    PerlinSimplexNoise* m_surfaceNoise;
    PerlinNoise* m_scaleNoise;
    PerlinNoise* m_depthNoise;
    PerlinNoise* m_qword78;  // unknown type
    PerlinNoise* m_qword80;  // unknown type
    PerlinNoise* m_field88;
    Level* m_level;
    bool m_shouldGenerateStructures;
    LevelType* m_generatorType;
    float m_biomeWeights[25];
    CustomizableSourceSettings* m_sourceSettings;
    const BlockState* m_oceanBlock;
    arrayWithLength<float> m_qword120;
    LargeCaveFeature* m_caveFeature;
    StrongholdFeature* m_strongholdFeature;
    VillageFeature* m_villageFeature;
    MineShaftFeature* m_mineshaftFeature;
    RandomScatteredLargeFeature* m_randomScatteredLargeFeature;
    CanyonFeature* m_canyonFeature;
    OceanMonumentFeature* m_oceanMonumentFeature;
    WoodlandMansionFeature* m_woodlandMansionFeature;
};

ASSERT_SIZEOF(OverworldLevelSource, 0x170)
