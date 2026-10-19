#pragma once

#include "net/minecraft/world/level/block/Block.h"

class BooleanProperty;

class SpongeBlock : public Block {
public:
    SpongeBlock();
    static BooleanProperty* WET;
};
