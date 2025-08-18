#pragma once

#include "net/minecraft/world/level/block/Block.h"

class StairBlock : public Block {
public:
    StairBlock(const BlockState* state);

    static void blockStaticCtor();
};
