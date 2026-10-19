#pragma once

#include "net/minecraft/world/level/block/Block.h"

class ColoredBlock : public Block {
public:
    static Property* COLOR;
    ColoredBlock(Material*);

    static void blockStaticCtor();
};
