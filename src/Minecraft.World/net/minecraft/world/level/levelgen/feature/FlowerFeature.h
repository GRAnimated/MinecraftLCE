#pragma once

#include "net/minecraft/world/level/block/FlowerBlock.h"
#include "net/minecraft/world/level/levelgen/feature/Feature.h"

class FlowerFeature : public Feature {
public:
    FlowerFeature(FlowerBlock*, FlowerBlock::Flower*);

    bool place(Level* level, Random& random, const BlockPos& pos) override;
    void setFlower(FlowerBlock*, FlowerBlock::Flower*);

    FlowerBlock* m_flower;
    const BlockState* m_state;
};
