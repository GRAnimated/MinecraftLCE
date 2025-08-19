#pragma once

#include "net/minecraft/world/level/block/SignBlock.h"

class WallSignBlock : public SignBlock {
public:
    WallSignBlock();

    static void blockStaticCtor();
};
