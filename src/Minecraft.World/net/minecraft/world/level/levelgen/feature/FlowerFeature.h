#pragma once

#include "Minecraft.World/level/block/FlowerBlock.h"
#include "Minecraft.World/level/levelgen/feature/Feature.h"

class FlowerFeature : public Feature {
public:
    FlowerFeature(FlowerBlock*, FlowerBlock::Flower*);

    virtual ~FlowerFeature() override;
    virtual bool place(Level* level, Random& random, const BlockPos& pos) override;

    void* field_10;
    void* field_18;
};
