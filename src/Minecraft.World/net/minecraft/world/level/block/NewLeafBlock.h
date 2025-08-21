#pragma once

#include "net/minecraft/world/level/block/LeafBlock.h"

class NewLeafBlock : public LeafBlock {
public:
    NewLeafBlock();

    static void blockStaticCtor();
};
