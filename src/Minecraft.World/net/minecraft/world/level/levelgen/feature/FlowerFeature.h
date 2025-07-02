#pragma once

#include "net/minecraft/world/level/block/FlowerBlock.h"
#include "net/minecraft/world/level/levelgen/feature/Feature.h"

class FlowerFeature : public Feature {
public:
    FlowerFeature(FlowerBlock*, FlowerBlock::Flower*);

    virtual ~FlowerFeature() override;
    virtual bool place(Level* level, Random& random, const BlockPos& pos) override;

    void* field_10;
    void* field_18;
};
