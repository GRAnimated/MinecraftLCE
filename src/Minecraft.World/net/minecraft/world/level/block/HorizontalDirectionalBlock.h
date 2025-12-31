#pragma once

#include "net/minecraft/core/Direction.h"
#include "net/minecraft/world/level/block/Block.h"
#include "net/minecraft/world/level/block/state/EnumProperty.h"

class HorizontalDirectionalBlock : public Block {
public:
    static void blockStaticCtor();

    static EnumProperty<Direction::Axis*>* AXIS;
};
