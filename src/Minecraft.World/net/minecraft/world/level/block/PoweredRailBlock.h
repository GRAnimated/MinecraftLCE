#pragma once

#include "net/minecraft/world/level/block/BaseRailBlock.h"

class PoweredRailBlock : public BaseRailBlock {
public:
    PoweredRailBlock();

    static void blockStaticCtor();
};
