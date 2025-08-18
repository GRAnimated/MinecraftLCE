#pragma once

#include "net/minecraft/world/level/block/Block.h"

class WallBlock : public Block {
public:
    WallBlock(Block*);

    static void blockStaticCtor();
};
