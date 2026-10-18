#include "net/minecraft/world/level/biome/SavannaBiome.h"

#include "net/minecraft/core/BlockPos.h"
#include "net/minecraft/world/Random.h"
#include "net/minecraft/world/eINSTANCEOF.h"
#include "net/minecraft/world/level/Level.h"
#include "net/minecraft/world/level/biome/BiomeDecorator.h"
#include "net/minecraft/world/level/levelgen/feature/DoublePlantFeature.h"
#include "net/minecraft/world/level/levelgen/feature/SavannaTreeFeature.h"
#include "net/minecraft/world/level/levelgen/feature/TreeFeature.h"

SavannaBiome::SavannaBiome(EBiomeIDs id, BiomeProperties* properties) : Biome(id, properties) {
    m_passiveMobs.push_back(new MobSpawnerData(eHorse, 1, 2, 6));
    m_passiveMobs.push_back(new MobSpawnerData(eDonkey, 1, 1, 1));
    if (getDepth() > 1.1f)
        m_passiveMobs.push_back(new MobSpawnerData(eLlama, 8, 4, 4));
    m_biomeDecorator->m_treeCount = 1;
    m_biomeDecorator->m_flowerCount = 4;
    m_biomeDecorator->m_grassCount = 20;
}

int SavannaBiome::getBaseClass() {
    return _SAVANNA;
}

Feature* SavannaBiome::getTreeFeature(Random& random) {
    if (random.nextInt(5) > 0)
        return new SavannaTreeFeature(false);
    return new TreeFeature(false);
}

void SavannaBiome::decorate(Level* level, Random& random, const BlockPos& pos) {
    DOUBLE_PLANT_FEATURE->setNextPlantType(DoublePlantBlock::Variant::GRASS);
    for (int i = 0; i < 7; ++i) {
        int x = random.nextInt(16) + 8;
        int z = random.nextInt(16) + 8;
        int height = level->getHeightmapPos(pos.offset(x, 0, z)).getY();
        int y = random.nextInt(height + 32);
        DOUBLE_PLANT_FEATURE->place(level, random, pos.offset(x, y, z));
    }
    Biome::decorate(level, random, pos);
}
