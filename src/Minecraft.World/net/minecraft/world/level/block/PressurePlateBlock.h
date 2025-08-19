#pragma once

#include "net/minecraft/world/level/block/BasePressurePlateBlock.h"

class PressurePlateBlock : public BasePressurePlateBlock {
public:
    enum Sensitivity {
        WOOD,
        STONE,
    };

    PressurePlateBlock(const std::wstring&, Material*, PressurePlateBlock::Sensitivity);
};
