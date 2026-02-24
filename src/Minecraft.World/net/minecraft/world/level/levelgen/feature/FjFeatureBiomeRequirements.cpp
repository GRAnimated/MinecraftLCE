#include "net/minecraft/world/level/levelgen/feature/FjFeatureBiomeRequirements.h"

FjFeatureBiomeRequirements::FjFeatureBiomeRequirements() {
    m_biomes0 = nullptr;
    m_field8 = 0;
    m_biomes1 = nullptr;
    m_field1A = 0;
}

FjFeatureBiomeRequirements::FjFeatureBiomeRequirements(const std::vector<Biome*>* a2, unsigned int a3,
                                                       const std::vector<Biome*>* a4, unsigned int a5) {
    m_biomes0 = a2;
    m_field8 = a3;
    m_biomes1 = a4;
    m_field1A = a5;
}
