#pragma once

#include "net/minecraft/world/level/block/Block.h"

class StemBlock : public Block {
public:
    StemBlock(Block*);

    static void blockStaticCtor();
};
