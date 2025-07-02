#pragma once

#include "Minecraft.World/level/levelgen/ChunkGenerator.h"

class TheEndLevelSource : public ChunkGenerator {
public:
    TheEndLevelSource(Level*, bool, long long, const BlockPos&);
    virtual ~TheEndLevelSource();
    virtual LevelChunk* createChunk(int, int) override;
    virtual void postProcess(int, int) override;
    virtual bool postProcessLoadedChunk(LevelChunk*, int, int) override;
    virtual void getMobsAt(MobCategory*, const BlockPos&) override;
    virtual void* findNearestMapFeature(Level*, const std::wstring&, const BlockPos&, bool) override;
    virtual void recreateLogicStructuresForChunk(LevelChunk*, int, int) override;
    virtual bool isPosInFeature(Level*, const std::wstring&, const BlockPos&) override;
};