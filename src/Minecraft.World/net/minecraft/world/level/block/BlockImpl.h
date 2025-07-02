#pragma once

#include "net/minecraft/world/level/block/Block.h"

class BlockImpl : public Block {
public:
    BlockImpl(Material* material);
    BlockImpl(Material* material, const MaterialColor* materialColor);
};
