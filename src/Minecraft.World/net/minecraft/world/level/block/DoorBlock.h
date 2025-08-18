#pragma once

#include "net/minecraft/world/level/block/Block.h"

class DoorBlock : public Block {
public:
    DoorBlock(Material*);

    static void blockStaticCtor();
};
