#pragma once

#include "net/minecraft/world/level/levelgen/feature/LargeFeature.h"
#include "types.h"

class StructureFeature : public LargeFeature {
public:
    char filler[0x38];
};

ASSERT_SIZEOF(StructureFeature, 0x68)
