#pragma once
#include "Minecraft.World/level/block/Block.h"

class StainedHardenedClayBlock : public Block {
public:
    static MaterialColor *sTerracottaColors;

    static void staticCtor();
};