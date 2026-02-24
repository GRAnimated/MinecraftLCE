#pragma once

#include <vector>

class Biome;

class FjFeatureBiomeRequirements {
public:
    FjFeatureBiomeRequirements();
    FjFeatureBiomeRequirements(const std::vector<Biome*>* a2, unsigned int a3, const std::vector<Biome*>* a4,
                               unsigned int a5);

    const std::vector<Biome*>* m_biomes0;
    unsigned int m_field8;
    const std::vector<Biome*>* m_biomes1;
    unsigned int m_field1A;
};
