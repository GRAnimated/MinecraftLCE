#pragma once

#include "net/minecraft/world/level/block/Block.h"

class ClayBlock : public Block {
public:
    ClayBlock();
    ~ClayBlock() override {}

    int getResourceCount(Random*) override;
    Item* getResource(const BlockState* blockState, Random*, int) override;
};
