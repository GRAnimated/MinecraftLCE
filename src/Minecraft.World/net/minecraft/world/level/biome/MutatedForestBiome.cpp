#include "net/minecraft/world/level/biome/MutatedForestBiome.h"

#include "net/minecraft/world/Random.h"
#include "net/minecraft/world/level/levelgen/feature/BirchFeature.h"

MutatedForestBiome::MutatedForestBiome(EBiomeIDs id, BiomeProperties* properties)
    : ForestBiome(id, BIRCH, properties) {}

Feature* MutatedForestBiome::getTreeFeature(Random& random) {
    if (random.nextBoolean())
        return new BirchFeature(false, true);
    return new BirchFeature(false, false);
}
