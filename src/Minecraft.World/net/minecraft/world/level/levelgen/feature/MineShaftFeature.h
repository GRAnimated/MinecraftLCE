#pragma once

#include "net/minecraft/world/level/levelgen/feature/StructureFeature.h"

class MineShaftFeature : public StructureFeature {
public:
    MineShaftFeature();

    char m_filler[0x8];
};

ASSERT_SIZEOF(MineShaftFeature, 0x70)
