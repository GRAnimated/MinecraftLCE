#pragma once

#include "net/minecraft/world/level/block/HorizontalDirectionalBlock.h"
#include "net/minecraft/world/level/block/PlanksBlock.h"

class FenceGateBlock : public HorizontalDirectionalBlock {
public:
    FenceGateBlock(const std::wstring& type, PlanksBlock::Variant* variant);
};
