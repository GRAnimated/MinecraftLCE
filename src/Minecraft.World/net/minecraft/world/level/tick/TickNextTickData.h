#pragma once
#include "net/minecraft/core/Vec3i.h"
#include "net/minecraft/world/level/block/Block.h"

class TickNextTickData {
public:
    Block* block;
    Vec3i* pos;
};
