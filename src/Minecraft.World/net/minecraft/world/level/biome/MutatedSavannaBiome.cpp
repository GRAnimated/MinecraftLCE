#include "net/minecraft/world/level/biome/MutatedSavannaBiome.h"

#include "net/minecraft/world/level/biome/BiomeDecorator.h"
#include "net/minecraft/world/level/block/Blocks.h"
#include "net/minecraft/world/level/block/DirtBlock.h"

MutatedSavannaBiome::MutatedSavannaBiome(EBiomeIDs id, BiomeProperties* properties)
    : SavannaBiome(id, properties) {
    m_biomeDecorator->m_treeCount = 2;
    m_biomeDecorator->m_flowerCount = 2;
    m_biomeDecorator->m_grassCount = 5;
}

void MutatedSavannaBiome::buildSurfaceAt(Level* level, Random& random, ChunkPrimer* primer, int x, int z,
                                         double noise) {
    m_grass = LegacyBlockData(2, 0);
    m_dirt = LegacyBlockData(3, 0);
    if (noise > 1.75) {
        m_grass = STONE;
        m_dirt = STONE;
    } else if (noise > -0.5) {
        m_grass = LegacyBlockData(
            3, Blocks::DIRT->convertBlockStateToLegacyData(Blocks::DIRT->defaultBlockState()->setValue(
                   DirtBlock::VARIANT, DirtBlock::Variant::COARSE)));
    }
    buildSurfaceAtDefault(level, random, primer, x, z, noise);
}

void MutatedSavannaBiome::decorate(Level* level, Random& random, const BlockPos& pos) {
    m_biomeDecorator->decorate(level, random, this, pos);
}
