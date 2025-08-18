#pragma once

#include "RotatedPillarBlock.h"

class BoneBlock : public RotatedPillarBlock {
public:
    BoneBlock();

    Direction::Axis* getAxis(const BlockState*) override;
};
