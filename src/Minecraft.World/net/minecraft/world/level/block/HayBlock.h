#pragma once

#include "net/minecraft/world/level/block/RotatedPillarBlock.h"

class HayBlock : public RotatedPillarBlock {
public:
    HayBlock();

    Direction::Axis* getAxis(const BlockState*) override;
};
