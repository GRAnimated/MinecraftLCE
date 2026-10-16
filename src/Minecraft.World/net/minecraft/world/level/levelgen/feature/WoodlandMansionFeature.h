#pragma once

#include "net/minecraft/world/level/levelgen/feature/StructureFeature.h"

class GenericOverworldLevelSource;
class SuperflatConfig;

class WoodlandMansionFeature : public StructureFeature {
public:
    WoodlandMansionFeature(GenericOverworldLevelSource*);
    WoodlandMansionFeature(GenericOverworldLevelSource*, SuperflatConfig*);

    static void staticCtor();

    char m_filler[0x40];
};

ASSERT_SIZEOF(WoodlandMansionFeature, 0xA8)
