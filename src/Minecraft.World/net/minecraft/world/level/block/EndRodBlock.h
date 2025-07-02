#pragma once

#include "Minecraft.World/level/block/Block.h"

class EndRodBlock : public Block {
public:
    const AABB* getShapeRod(const BlockState*);
};