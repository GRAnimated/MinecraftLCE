#pragma once

#include "net/minecraft/world/level/block/RotatedPillarBlock.h"

class RotatedPillarBlockImpl : public RotatedPillarBlock {
public:
    RotatedPillarBlockImpl(Material*);
    RotatedPillarBlockImpl(Material*, const MaterialColor*);

    RotatedPillarBlockImpl* setIconTopName(const std::wstring& name);

    Direction::Axis* getAxis(const BlockState*) override;
};
