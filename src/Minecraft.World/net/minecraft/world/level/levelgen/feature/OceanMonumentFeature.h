#pragma once

#include "net/minecraft/world/level/levelgen/feature/LargeFeature.h"

class OceanMonumentFeature : public LargeFeature {
public:
    OceanMonumentFeature();

    char filler[0x70];
};

ASSERT_SIZEOF(OceanMonumentFeature, 0xA0)
