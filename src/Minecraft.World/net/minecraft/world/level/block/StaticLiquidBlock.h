#pragma once

#include "net/minecraft/world/level/block/LiquidBlock.h"
#include "net/minecraft/world/level/material/Material.h"

class StaticLiquidBlock : public LiquidBlock {
public:
    StaticLiquidBlock(Material* material);
};
