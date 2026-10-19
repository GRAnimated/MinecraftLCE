#pragma once

#include "net/minecraft/world/level/block/Block.h"

class ChestBlock : public Block {
public:
    ChestBlock(bool trapped);
    const BlockState* reorient(Level*, const BlockPos&, const BlockState*);

    static void blockStaticCtor();
};
