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
        bool enabled;
        int limit;
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

    Random mRandom;
    Random mRandom2;
    PerlinNoise* mMinLimitPerlinNoise;
    PerlinNoise* mMaxLimitPerlinNoise;
    PerlinNoise* mMainNoise;
    PerlinSimplexNoise* mSurfaceNoise;
    PerlinNoise* mScaleNoise;
    PerlinNoise* mDepthNoise;
    PerlinNoise* qword_78;  // unknown type
    PerlinNoise* qword_80;  // unknown type
    PerlinNoise* field_88;
    Level* mLevel;
    bool mShouldGenerateStructures;
    LevelType* mGeneratorType;
    float mBiomeWeights[25];
    CustomizableSourceSettings* mSourceSettings;
    const BlockState* mOceanBlock;
    arrayWithLength<float> qword_120;
    LargeCaveFeature* mCaveFeature;
    StrongholdFeature* mStrongholdFeature;
    VillageFeature* mVillageFeature;
    MineShaftFeature* mMineshaftFeature;
    RandomScatteredLargeFeature* mRandomScatteredLargeFeature;
    CanyonFeature* mCanyonFeature;
    OceanMonumentFeature* mOceanMonumentFeature;
    WoodlandMansionFeature* mWoodlandMansionFeature;
};

ASSERT_SIZEOF(OverworldLevelSource, 0x170)
