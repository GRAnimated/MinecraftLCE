#pragma once

#include "net/minecraft/world/level/levelgen/feature/LargeFeature.h"

class CanyonFeature : public LargeFeature {
public:
    char m_filler[0x1000];
};

ASSERT_SIZEOF(CanyonFeature, 0x1030)
