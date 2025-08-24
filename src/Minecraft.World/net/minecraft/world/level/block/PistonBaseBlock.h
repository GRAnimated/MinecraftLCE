#pragma once

#include "net/minecraft/world/level/block/Block.h"

class PistonBaseBlock : public DirectionalBlock {
public:
    PistonBaseBlock(bool sticky);

    static void blockStaticCtor();
};
