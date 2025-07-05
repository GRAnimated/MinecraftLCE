#pragma once

#include "Minecraft.Core/BlockPos.h"
class Level;
class Block;

class BlockBehaviours {
public:
    virtual void triggerEvent(Level*, const BlockPos&, int, int) const = 0;
    virtual void neighborChanged(Level*, const BlockPos&, Block*, const BlockPos&) const = 0;
};
