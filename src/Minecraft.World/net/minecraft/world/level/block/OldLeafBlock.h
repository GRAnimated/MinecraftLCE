#pragma once

#include "net/minecraft/world/level/block/LeafBlock.h"

class OldLeafBlock : public LeafBlock {
public:
    OldLeafBlock();

    static void blockStaticCtor();
};
