#pragma once

#include "net/minecraft/world/level/levelgen/feature/StructureFeature.h"
#include <vector>

class Biome;

class VillageFeature : public StructureFeature {
public:
    VillageFeature(int);

    static void staticCtor();
    static std::vector<Biome*> ALLOWED_BIOMES;

    char m_filler[0x10];
};

ASSERT_SIZEOF(VillageFeature, 0x78)
