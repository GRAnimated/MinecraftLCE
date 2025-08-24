#pragma once

#include "FallingBlock.h"
#include "net/minecraft/world/level/block/Block.h"

class ConcretePowderBlock : public FallingBlock {
public:
    ConcretePowderBlock();

    static void blockStaticCtor();
};
