#include "net/minecraft/world/level/biome/OceanBiome.h"

OceanBiome::OceanBiome(EBiomeIDs id, BiomeProperties* properties) : Biome(id, properties) {
    m_passiveMobs.clear();
    m_chickens.clear();
    m_fieldD8.clear();
}

int OceanBiome::getBaseClass() {
    return _OCEAN;
}

int OceanBiome::getTemperatureCategory() {
    return 0;
}
