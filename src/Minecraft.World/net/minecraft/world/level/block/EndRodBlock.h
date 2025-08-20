#pragma once

#include "net/minecraft/world/level/block/Block.h"

class EndRodBlock : public Block {
public:
    EndRodBlock();

    const AABB* getShapeRod(const BlockState*);
};
