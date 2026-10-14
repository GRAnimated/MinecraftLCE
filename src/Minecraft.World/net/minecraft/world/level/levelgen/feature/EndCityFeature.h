#pragma once

#include "net/minecraft/world/level/levelgen/feature/StructureFeature.h"

class TheEndLevelSource;

// Constructor and specialized virtual methods remain unreconstructed.
class EndCityFeature : public StructureFeature {
public:
    explicit EndCityFeature(TheEndLevelSource*);
    TheEndLevelSource* m_source;
};
ASSERT_SIZEOF(EndCityFeature, 0x70)
