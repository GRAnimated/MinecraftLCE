#pragma once

#include "net/minecraft/world/level/block/TallGrassBlock.h"
#include "net/minecraft/world/level/levelgen/feature/Feature.h"
#include "types.h"

class TallgrassFeature : public Feature {
public:
    TallgrassFeature(TallGrassBlock::Variant*);
    ~TallgrassFeature() override = default;
    bool place(Level*, Random&, const BlockPos&) override;

private:
    const BlockState* m_state;
};

ASSERT_SIZEOF(TallgrassFeature, 0x18)
