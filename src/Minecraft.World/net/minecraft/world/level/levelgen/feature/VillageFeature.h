#pragma once

#include "net/minecraft/world/level/levelgen/feature/StructureFeature.h"

class VillageFeature : public StructureFeature {
public:
    VillageFeature(int);

    static void staticCtor();

    char m_filler[0x10];
};

ASSERT_SIZEOF(VillageFeature, 0x78)
