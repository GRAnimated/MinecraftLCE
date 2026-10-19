#include "net/minecraft/world/level/biome/OceanBiome.h"

// name guessed
OceanBiome::OceanBiome(EBiomeIDs id, BiomeProperties* properties) : Biome(id, properties) {
    m_passiveMobs.clear();
    m_chickens.clear();
    m_fieldD8.clear();
}

// name guessed
int OceanBiome::getBaseClass() {
    return _OCEAN;
}

// name guessed
int OceanBiome::getTemperatureCategory() {
    return 0;
}
