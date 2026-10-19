#pragma once

#include "net/minecraft/world/ArrayWithLength.h"
#include "net/minecraft/world/Random.h"
#include "net/minecraft/world/level/chunk/ChunkGenerator.h"
#include "net/minecraft/world/level/levelgen/GenericOverworldLevelSource.h"
#include "types.h"
#include <unordered_map>

class SuperflatConfig;
class BlockState;
class LargeCaveFeature;
class CanyonFeature;
class StructureFeature;
class OceanMonumentFeature;
class LakeFeature;

class FlatLevelSource : public ChunkGenerator, public GenericOverworldLevelSource {
public:
    FlatLevelSource(Level*, long long, bool, SuperflatConfig*);
    ~FlatLevelSource() override;
    LevelChunk* createChunk(int, int) override;
    void postProcess(int, int) override;
    bool postProcessLoadedChunk(LevelChunk*, int, int) override;
    std::vector<Biome::MobSpawnerData*>* getMobsAt(MobCategory*, const BlockPos&) override;
    BlockPos* findNearestMapFeature(Level*, const std::wstring&, const BlockPos&, bool) override;
    void recreateLogicStructuresForChunk(LevelChunk*, int, int) override;
    bool isPosInFeature(Level*, const std::wstring&, const BlockPos&) override;
    void prepareHeights(int, int, ChunkPrimer*) override;
    bool isFlat() override;

private:
    Level* m_level;
    Random m_random;
    Random m_decorationRandom;
    const BlockState* m_layers[256];
    std::unordered_map<std::wstring, StructureFeature*> m_structures;
    LargeCaveFeature* m_caves;
    CanyonFeature* m_canyons;
    bool m_decorations;
    bool m_dungeons;
    LakeFeature* m_lakes;
    LakeFeature* m_lavaLakes;
    OceanMonumentFeature* m_monument;
    arrayWithLength<unsigned char> m_blockIds;
    arrayWithLength<unsigned char> m_blockData;
};

ASSERT_SIZEOF(FlatLevelSource, 0x8c8)
