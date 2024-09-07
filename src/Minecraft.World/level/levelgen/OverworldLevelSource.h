#pragma once

#include "Minecraft.World/Random.h"
#include "Minecraft.World/level/levelgen/ChunkGenerator.h"
#include "Minecraft.World/level/levelgen/GenericOverworldLevelSource.h"

class ChunkPrimer;
class SuperflatConfig;

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

    char unk[0x90 - 0x8];
    Level* level;
    char unk2[0x170 - 0x88];
};