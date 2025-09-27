#include "net/minecraft/world/level/levelgen/feature/FjFeatureBiomeRequirements.h"

FjFeatureBiomeRequirements::FjFeatureBiomeRequirements() {
    mBiomes0 = nullptr;
    field_8 = 0;
    mBiomes1 = nullptr;
    field_1A = 0;
}

FjFeatureBiomeRequirements::FjFeatureBiomeRequirements(const std::vector<Biome*>* a2, unsigned int a3,
                                                       const std::vector<Biome*>* a4, unsigned int a5) {
    mBiomes0 = a2;
    field_8 = a3;
    mBiomes1 = a4;
    field_1A = a5;
}
