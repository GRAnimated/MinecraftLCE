#pragma once

#include "net/minecraft/world/level/levelgen/feature/StructureFeature.h"

class GenericOverworldLevelSource;

class WoodlandMansionFeature : public StructureFeature {
public:
    WoodlandMansionFeature(GenericOverworldLevelSource*);

    char filler[0x40];
};

ASSERT_SIZEOF(WoodlandMansionFeature, 0xA8)
