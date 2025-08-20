#pragma once

#include "net/minecraft/world/level/block/FlowerBlock.h"

class RedFlowerBlock : public FlowerBlock {
public:
    RedFlowerBlock();

    FlowerBlock::FlowerCategory* getFlowerCategory() override;

    // NOTE: unsure if these virtuals are meant to be in FlowerBlock instead
    bool isBonemealSuccess(Level*, Random*, const BlockPos&, const BlockState*) override;
    bool isValidBonemealTarget(Level*, const BlockPos&, const BlockState*, bool) override;
    void performBonemeal(Level*, Random*, const BlockPos&, const BlockState*) override;
};
