#pragma once

#include "net/minecraft/world/level/block/LiquidBlock.h"
#include "net/minecraft/world/level/material/Material.h"

class DynamicLiquidBlock : public LiquidBlock {
public:
    DynamicLiquidBlock(Material* material);
};
