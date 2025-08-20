#pragma once

#include "net/minecraft/world/level/block/Block.h"

class ChestBlock : public Block {
public:
    ChestBlock(bool trapped);

    static void blockStaticCtor();
};
