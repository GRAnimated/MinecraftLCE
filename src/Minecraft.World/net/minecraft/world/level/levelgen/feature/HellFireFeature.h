#pragma once

#include "Minecraft.World/level/levelgen/feature/Feature.h"

class HellFireFeature : public Feature {
public:
    HellFireFeature();

    virtual bool place(Level* level, Random& random, const BlockPos& pos) override;
};
