#pragma once

#include "net/minecraft/world/level/block/BonemealableBlock.h"
#include "net/minecraft/world/level/block/HorizontalDirectionalBlock.h"

class CocoaBlock : public HorizontalDirectionalBlock, public BonemealableBlock {
public:
    CocoaBlock();

    bool isValidBonemealTarget(Level*, const BlockPos&, const BlockState*, bool) override;
    bool isBonemealSuccess(Level*, Random*, const BlockPos&, const BlockState*) override;
    void performBonemeal(Level*, Random*, const BlockPos&, const BlockState*) override;
};
