#pragma once

#include "net/minecraft/core/BlockPos.h"
class Level;
class Block;

class BlockBehaviours {
public:
    virtual void triggerEvent(Level*, const BlockPos&, int, int) const = 0;
    virtual void neighborChanged(Level*, const BlockPos&, Block*, const BlockPos&) const = 0;
};
