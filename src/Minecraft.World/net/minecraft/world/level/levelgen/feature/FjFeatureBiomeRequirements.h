#pragma once

#include <vector>

class Biome;

class FjFeatureBiomeRequirements {
public:
    FjFeatureBiomeRequirements();
    FjFeatureBiomeRequirements(const std::vector<Biome*>* a2, unsigned int a3, const std::vector<Biome*>* a4,
                               unsigned int a5);

    const std::vector<Biome*>* mBiomes0;
    unsigned int field_8;
    const std::vector<Biome*>* mBiomes1;
    unsigned int field_1A;
};
