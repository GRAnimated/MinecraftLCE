#include "net/minecraft/world/level/biome/RiverBiome.h"

// name guessed
RiverBiome::RiverBiome(EBiomeIDs id, BiomeProperties* properties) : Biome(id, properties) {
    m_passiveMobs.clear();
    m_chickens.clear();
    m_fieldD8.clear();
}

// name guessed
int RiverBiome::getBaseClass() {
    return _RIVER;
}
