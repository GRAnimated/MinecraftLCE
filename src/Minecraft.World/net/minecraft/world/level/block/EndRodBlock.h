#pragma once

#include "net/minecraft/world/level/block/Block.h"

class EndRodBlock : public Block {
public:
    const AABB* getShapeRod(const BlockState*);
};