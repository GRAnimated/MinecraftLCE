#pragma once

#include "net/minecraft/core/BlockSource.h"
#include "net/minecraft/world/level/block/Block.h"

class DirectionProperty;

class DispenserBlock : public Block {
public:
    static DirectionProperty* FACING;

    static void blockStaticCtor();

    static Position* getDispensePosition(BlockSource*);
};
