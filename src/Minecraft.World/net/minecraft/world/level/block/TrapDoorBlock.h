#pragma once

#include "net/minecraft/world/level/block/Block.h"

class TrapDoorBlock : public Block {
public:
    TrapDoorBlock(Material*);

    static void blockStaticCtor();
};
