#pragma once

#include "net/minecraft/world/level/block/Block.h"

class TallGrassBlock : public Block {
public:
    class Variant {
    public:
        static Variant* GRASS;
    };

    TallGrassBlock();

    static void blockStaticCtor();
};
