#pragma once

#include "Minecraft.World/ArrayWithLength.h"
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
    virtual void getMobsAt(MobCategory*, const BlockPos&) override;
    virtual void* findNearestMapFeature(Level*, const std::wstring&, const BlockPos&, bool) override;
    virtual void recreateLogicStructuresForChunk(LevelChunk*, int, int) override;
    virtual bool isPosInFeature(Level*, const std::wstring&, const BlockPos&) override;
    virtual void lightChunk(LevelChunk*) override;
    void prepareHeights(int, int, ChunkPrimer*);
    void getHeights(int, int, int, arrayWithLength<Biome*>&, arrayWithLength<double>&);
    void buildSurfaces(int, int, ChunkPrimer*, arrayWithLength<Biome*>);

    char unk[0x90 - 0x8];
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
