#include "net/minecraft/world/level/biome/StoneBeachBiome.h"

#include "net/minecraft/world/level/biome/BiomeDecorator.h"
#include "net/minecraft/world/level/block/Block.h"
#include "net/minecraft/world/level/block/Blocks.h"

StoneBeachBiome::StoneBeachBiome(EBiomeIDs id, BiomeProperties* properties) : Biome(id, properties) {
    m_passiveMobs.clear();
    m_grass = LegacyBlockData(
        1, Blocks::STONE->convertBlockStateToLegacyData(Blocks::STONE->defaultBlockState()));
    m_dirt = LegacyBlockData(
        1, Blocks::STONE->convertBlockStateToLegacyData(Blocks::STONE->defaultBlockState()));
    m_biomeDecorator->m_treeCount = -999;
    m_biomeDecorator->m_deadBushCount = 0;
    m_biomeDecorator->m_reedCount = 0;
    m_biomeDecorator->m_cactusCount = 0;
}

int StoneBeachBiome::getBaseClass() {
    return _STONE_BEACH;
}
