#pragma once

#include "net/minecraft/world/level/block/FlowerBlock.h"
#include "net/minecraft/world/level/levelgen/feature/Feature.h"

class FlowerFeature : public Feature {
public:
    FlowerFeature(FlowerBlock*, FlowerBlock::Flower*);

    ~FlowerFeature() override;
    bool place(Level* level, Random& random, const BlockPos& pos) override;

    void* m_field10;
    void* m_field18;
};
