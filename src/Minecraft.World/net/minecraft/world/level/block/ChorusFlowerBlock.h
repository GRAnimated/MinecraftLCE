#pragma once

#include "net/minecraft/world/level/block/Block.h"

class ChorusFlowerBlock : public Block {
public:
    static void generatePlant(Level*, BlockPos, Random*, int);
    ChorusFlowerBlock();
};
