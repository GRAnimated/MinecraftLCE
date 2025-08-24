#pragma once

#include "net/minecraft/world/level/levelgen/feature/StructureFeature.h"

class RandomScatteredLargeFeature : public StructureFeature {
public:
    RandomScatteredLargeFeature();

    char filler[0x20];
};

ASSERT_SIZEOF(RandomScatteredLargeFeature, 0x88)
