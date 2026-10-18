#pragma once

#include "net/minecraft/world/level/block/Block.h"

class HugeMushroomBlock : public Block {
public:
    class Variant {
    public:
        static Variant* byData(int);
        static Variant* NORTH_WEST;
        static Variant* NORTH_EAST;
        static Variant* SOUTH_WEST;
        static Variant* SOUTH_EAST;
        static Variant* CENTER;
        static Variant* ALL_INSIDE;
        static Variant* STEM;
    };

    static Property* VARIANT;

    HugeMushroomBlock(Material*, const MaterialColor*, Block*);

    static void blockStaticCtor();
};
