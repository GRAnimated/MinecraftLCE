#pragma once

#include "net/minecraft/world/level/block/BonemealableBlock.h"
#include "net/minecraft/world/level/block/Bush.h"

class MushroomBlock : public Bush, public BonemealableBlock {
public:
    MushroomBlock();

    bool isBonemealSuccess(Level*, Random*, const BlockPos&, const BlockState*) override;
    bool isValidBonemealTarget(Level*, const BlockPos&, const BlockState*, bool) override;
    void performBonemeal(Level*, Random*, const BlockPos&, const BlockState*) override;
};
