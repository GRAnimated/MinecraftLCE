#pragma once

#include "net/minecraft/world/level/block/Bush.h"

class TallGrassBlock : public Bush {
public:
    class Variant {
    public:
        static Variant* GRASS;
        static Variant* FERN;
    };

    TallGrassBlock();

    static void blockStaticCtor();

    static Property* TYPE;
};
