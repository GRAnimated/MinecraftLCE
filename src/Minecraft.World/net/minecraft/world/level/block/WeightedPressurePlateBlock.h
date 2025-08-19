#pragma once

#include "net/minecraft/world/level/block/BasePressurePlateBlock.h"

class WeightedPressurePlateBlock : public BasePressurePlateBlock {
public:
    WeightedPressurePlateBlock(const std::wstring&, Material*, int, const MaterialColor*);
};
