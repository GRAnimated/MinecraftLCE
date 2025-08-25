#pragma once

#include "net/minecraft/world/level/levelgen/feature/StructureFeature.h"

class StrongholdFeature : public StructureFeature {
public:
    StrongholdFeature();

    char filler[0x48];
};

ASSERT_SIZEOF(StrongholdFeature, 0xB0)
