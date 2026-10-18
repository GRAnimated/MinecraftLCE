#include "net/minecraft/world/level/biome/Biome.h"

#include "net/minecraft/world/Random.h"
#include "net/minecraft/world/level/biome/BiomeDecorator.h"
#include "net/minecraft/world/level/levelgen/feature/BigTreeFeature.h"
#include "net/minecraft/world/level/levelgen/feature/TallgrassFeature.h"
#include "net/minecraft/world/level/levelgen/feature/TreeFeature.h"

BiomeDecorator* Biome::createDecorator() {
    return new BiomeDecorator();
}

Feature* Biome::getTreeFeature(Random& random) {
    if (random.nextInt(10) == 0)
        return new BigTreeFeature(false);
    return new TreeFeature(false);
}

Feature* Biome::getGrassFeature(Random&) {
    return new TallgrassFeature(TallGrassBlock::Variant::GRASS);
}

void Biome::decorate(Level* level, Random& random, const BlockPos& pos) {
    m_biomeDecorator->decorate(level, random, this, pos);
}
