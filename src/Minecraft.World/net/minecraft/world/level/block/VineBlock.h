#pragma once

#include "net/minecraft/world/level/block/Block.h"

class BooleanProperty;

class VineBlock : public Block {
public:
    static BooleanProperty* EAST;
    static BooleanProperty* WEST;
    static BooleanProperty* SOUTH;
    static BooleanProperty* NORTH;
    VineBlock();
};
