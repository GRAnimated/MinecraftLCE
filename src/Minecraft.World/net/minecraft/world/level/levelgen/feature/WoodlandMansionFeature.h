#pragma once

#include "net/minecraft/world/level/levelgen/feature/LargeFeature.h"

class GenericOverworldLevelSource;

class WoodlandMansionFeature : public LargeFeature {
public:
    WoodlandMansionFeature(GenericOverworldLevelSource*);

    char filler[0x78];
};

ASSERT_SIZEOF(WoodlandMansionFeature, 0xA8)
