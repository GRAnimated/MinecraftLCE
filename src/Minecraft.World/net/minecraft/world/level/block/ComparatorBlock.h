#pragma once

#include "net/minecraft/world/level/block/Block.h"

class ComparatorBlock : public Block {
public:
    ComparatorBlock(bool on);

    static void blockStaticCtor();
};
