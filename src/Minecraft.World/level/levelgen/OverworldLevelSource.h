#pragma once

#include "Minecraft.World/ArrayWithLength.h"
#include "Minecraft.World/Random.h"
#include "Minecraft.World/level/levelgen/ChunkGenerator.h"
#include "Minecraft.World/level/levelgen/CustomizableSourceSettings.h"
#include "Minecraft.World/level/levelgen/GenericOverworldLevelSource.h"

class Biome;
class ChunkPrimer;
class SuperflatConfig;
class LevelType;
class BlockState;
class LargeFeature;

class OverworldLevelSource : public ChunkGenerator, public GenericOverworldLevelSource {
public:


    OverworldLevelSource(Level*, long long, bool, SuperflatConfig*);
    virtual ~OverworldLevelSource() override;
    virtual LevelChunk* createChunk(int, int) override;
    virtual void postProcess(int, int) override;
    virtual bool postProcessLoadedChunk(LevelChunk*, int, int) override;
    virtual void getMobsAt(MobCategory*, BlockPos const&) override;
    virtual void* findNearestMapFeature(Level*, std::wstring const&, BlockPos const&, bool) override;
    virtual void recreateLogicStructuresForChunk(LevelChunk*, int, int) override;
    virtual bool isPosInFeature(Level*, std::wstring const&, BlockPos const&) override;
    virtual void lightChunk(LevelChunk*) override;
    void prepareHeights(int, int, ChunkPrimer*);
    void getHeights(int, int, int, arrayWithLength<Biome*>&, arrayWithLength<double>&);
    void buildSurfaces(int, int, ChunkPrimer*, arrayWithLength<Biome*>);
    float getHeightFalloff(int x, int z, int *height);
    static int unkMethod(float, OverworldLevelSource *src, int x, int z, int size);

    Random rand1;
    Random rand2;
    void *field_48;
    void *field_50;
    void *mMainNoise;
    void *field_60;
    void *field_68;
    void *mDepthNoise;
    long long qword_78;
    long long qword_80;
    void *field_88;
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
