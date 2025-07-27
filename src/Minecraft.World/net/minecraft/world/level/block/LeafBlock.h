#pragma once

#include "net/minecraft/world/level/block/TransparentBlock.h"

class LeafBlock : public TransparentBlock {
public:
    static bool isLeaves(Block*);

    void setFancy(bool);
};