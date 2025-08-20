#pragma once

#include "net/minecraft/world/level/block/Block.h"

class StainedGlassBlock : public Block {
public:
    StainedGlassBlock(Material*);

    static void blockStaticCtor();
};
