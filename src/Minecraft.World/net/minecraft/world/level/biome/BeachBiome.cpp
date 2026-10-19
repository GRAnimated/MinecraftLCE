#include "net/minecraft/world/level/biome/BeachBiome.h"

#include "net/minecraft/world/level/biome/BiomeDecorator.h"
#include "net/minecraft/world/level/block/Block.h"
#include "net/minecraft/world/level/block/Blocks.h"

// name guessed
BeachBiome::BeachBiome(EBiomeIDs id, BiomeProperties* properties) : Biome(id, properties) {
    m_passiveMobs.clear();
    m_chickens.clear();
    m_grass
        = LegacyBlockData(12, Blocks::SAND->convertBlockStateToLegacyData(Blocks::SAND->defaultBlockState()));
    m_dirt
        = LegacyBlockData(12, Blocks::SAND->convertBlockStateToLegacyData(Blocks::SAND->defaultBlockState()));
    m_biomeDecorator->m_treeCount = -999;
    m_biomeDecorator->m_deadBushCount = 0;
    m_biomeDecorator->m_reedCount = 0;
    m_biomeDecorator->m_cactusCount = 0;
}

// name guessed
int BeachBiome::getBaseClass() {
    return _BEACH;
}
