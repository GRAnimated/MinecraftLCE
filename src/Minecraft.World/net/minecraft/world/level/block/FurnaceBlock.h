#pragma once

#include "net/minecraft/world/level/block/Block.h"

class FurnaceBlock : public Block {
public:
    FurnaceBlock(bool lit);

    static void blockStaticCtor();
};
