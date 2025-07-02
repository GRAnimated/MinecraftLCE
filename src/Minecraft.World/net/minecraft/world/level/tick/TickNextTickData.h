#pragma once
#include "Minecraft.World/level/block/Block.h"
#include "Minecraft.Core/Vec3i.h"

class TickNextTickData {
public:
    Block* block;
    Vec3i* pos;
};
