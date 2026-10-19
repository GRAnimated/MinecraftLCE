#include "net/minecraft/world/level/biome/MushroomIslandBiome.h"

#include "net/minecraft/world/eINSTANCEOF.h"
#include "net/minecraft/world/level/biome/BiomeDecorator.h"
#include "net/minecraft/world/level/block/Block.h"
#include "net/minecraft/world/level/block/Blocks.h"

// name guessed
MushroomIslandBiome::MushroomIslandBiome(EBiomeIDs id, BiomeProperties* properties) : Biome(id, properties) {
    m_biomeDecorator->m_treeCount = -100;
    m_biomeDecorator->m_flowerCount = -100;
    m_biomeDecorator->m_grassCount = -100;
    m_biomeDecorator->m_mushroomCount = 1;
    m_biomeDecorator->m_hugeMushroomCount = 1;
    m_grass = LegacyBlockData(
        110, Blocks::MYCELIUM->convertBlockStateToLegacyData(Blocks::MYCELIUM->defaultBlockState()));
    m_hostileMobs.clear();
    m_passiveMobs.clear();
    m_chickens.clear();
    m_fieldD8.clear();
    m_aquaticMobs.clear();
    m_fieldF0.push_back(new MobSpawnerData(eMushroomCow, 8, 4, 8));
}

// name guessed
int MushroomIslandBiome::getBaseClass() {
    return _MUSHROOM_ISLAND;
}
