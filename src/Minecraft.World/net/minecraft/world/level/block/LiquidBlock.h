#pragma once

#include "net/minecraft/world/level/block/Block.h"
#include "net/minecraft/world/level/material/Material.h"

class LiquidBlock : public Block {
public:
    LiquidBlock(Material* material);
};
