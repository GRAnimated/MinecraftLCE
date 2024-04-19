#pragma once

#include "Minecraft.World/level/levelgen/ChunkGenerator.h"

class TheEndLevelSource : public ChunkGenerator {
public:
    TheEndLevelSource(Level*, bool, long long, BlockPos const&);
    virtual ~TheEndLevelSource();
    virtual void createChunk(int, int) override;
    virtual void postProcess(int, int) override;
    virtual void postProcessLoadedChunk(LevelChunk*, int, int) override;
    virtual void getMobsAt(MobCategory*, BlockPos const&) override;
    virtual void findNearestMapFeature(Level*, std::wstring const&, BlockPos const&, bool) override;
    virtual void recreateLogicStructuresForChunk(LevelChunk*, int, int) override;
    virtual void isPosInFeature(Level*, std::wstring const&, BlockPos const&) override;
};