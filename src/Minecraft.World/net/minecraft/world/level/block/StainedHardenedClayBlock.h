#pragma once

#include "net/minecraft/world/level/block/Block.h"

class StainedHardenedClayBlock : public Block {
public:
    static MaterialColor* sTerracottaColors;
    StainedHardenedClayBlock();

    static void staticCtor();
};
