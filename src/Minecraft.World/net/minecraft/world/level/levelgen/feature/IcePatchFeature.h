#pragma once

#include "net/minecraft/world/level/levelgen/feature/Feature.h"

class Block;
class IcePatchFeature : public Feature {
public:
    IcePatchFeature(int radius);
    bool place(Level*, Random&, const BlockPos&) override;

private:
    Block* m_block;
    int m_radius;
};
