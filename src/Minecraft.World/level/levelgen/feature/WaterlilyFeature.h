#pragma once

#include "Minecraft.World/level/levelgen/feature/Feature.h"

class WaterlilyFeature : public Feature {
public:
    WaterlilyFeature();

    virtual bool place(Level* level, Random& random, const BlockPos& pos) override;
};
