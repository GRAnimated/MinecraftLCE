#pragma once

#include "net/minecraft/world/level/block/Block.h"

class TorchBlock : public Block {
public:
    static Property* FACING;
    TorchBlock();

    static void blockStaticCtor();
};
