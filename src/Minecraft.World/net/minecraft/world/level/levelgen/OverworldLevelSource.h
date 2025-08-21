#pragma once

#include "net/minecraft/world/ArrayWithLength.h"
#include "net/minecraft/world/Random.h"
#include "net/minecraft/world/level/chunk/ChunkGenerator.h"
#include "net/minecraft/world/level/levelgen/CustomizableSourceSettings.h"
#include "net/minecraft/world/level/levelgen/GenericOverworldLevelSource.h"

class Biome;
class ChunkPrimer;
class SuperflatConfig;
class LevelType;
class BlockState;
class LargeFeature;

class OverworldLevelSource : public ChunkGenerator, public GenericOverworldLevelSource {
public:
    OverworldLevelSource(Level*, long long, bool, SuperflatConfig*);
    ~OverworldLevelSource() override;
    LevelChunk* createChunk(int, int) override;
    void postProcess(int, int) override;
    bool postProcessLoadedChunk(LevelChunk*, int, int) override;
    void getMobsAt(MobCategory*, const BlockPos&) override;
    void* findNearestMapFeature(Level*, const std::wstring&, const BlockPos&, bool) override;
    void recreateLogicStructuresForChunk(LevelChunk*, int, int) override;
    bool isPosInFeature(Level*, const std::wstring&, const BlockPos&) override;
    void lightChunk(LevelChunk*) override;
    void prepareHeights(int, int, ChunkPrimer*);
    void getHeights(int, int, int, arrayWithLength<Biome*>&, arrayWithLength<double>&);
    void buildSurfaces(int, int, ChunkPrimer*, arrayWithLength<Biome*>);
    float getHeightFalloff(int x, int z, int* height);
    static int unkMethod(float, OverworldLevelSource* src, int x, int z, int size);

    bool mIsLevelClassic;
    bool mIsLevelSmall;
    bool mIsLevelMedium;
    bool mIsLevelLarge;
    int mSize;
    Random rand1;
    Random rand2;
    void* field_48;
    void* field_50;
    void* mMainNoise;
    void* field_60;
    void* field_68;
    void* mDepthNoise;
    long long qword_78;
    long long qword_80;
    void* field_88;
    Level* mLevel;
    char byte_98;
    LevelType* qword_a0;
    float float_a8;
    char gap_AC[100];
    CustomizableSourceSettings mSourceSettings;
    const BlockState* field_118;
    void* qword_120;
    char gap_128[8];
    LargeFeature* mCaveFeature;
    void* field_138;
    void* field_140;
    void* field_148;
    void* field_150;
    LargeFeature* mRavineFeature;
    void* field_160;
    void* field_168;
    void* field_170;
    void* field_178;
};
