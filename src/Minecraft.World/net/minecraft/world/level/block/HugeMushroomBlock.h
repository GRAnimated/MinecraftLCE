#pragma once

#include "net/minecraft/world/level/block/Block.h"

class HugeMushroomBlock : public Block {
public:
    HugeMushroomBlock(Material*, const MaterialColor*, Block*);

    static void blockStaticCtor();
};
