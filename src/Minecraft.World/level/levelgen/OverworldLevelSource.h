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
    ~OverworldLevelSource() override;
    LevelChunk* createChunk(int, int) override;
    void postProcess(int, int) override;
    bool postProcessLoadedChunk(LevelChunk*, int, int) override;
    void getMobsAt(MobCategory*, BlockPos const&) override;
    void* findNearestMapFeature(Level*, std::wstring const&, BlockPos const&, bool) override;
    void recreateLogicStructuresForChunk(LevelChunk*, int, int) override;
    bool isPosInFeature(Level*, std::wstring const&, BlockPos const&) override;
    void lightChunk(LevelChunk*) override;
    void prepareHeights(int, int, ChunkPrimer*) override;
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
    void* qword_128;
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
