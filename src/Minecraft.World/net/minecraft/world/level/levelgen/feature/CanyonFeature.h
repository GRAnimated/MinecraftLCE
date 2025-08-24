#pragma once

#include "net/minecraft/world/level/levelgen/feature/LargeFeature.h"

class CanyonFeature : public LargeFeature {
public:
    char filler[0x1000];
};

ASSERT_SIZEOF(CanyonFeature, 0x1030)
