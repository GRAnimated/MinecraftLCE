#pragma once

#include "net/minecraft/world/level/block/LeafBlock.h"
#include "net/minecraft/world/level/block/PlanksBlock.h"
#include "net/minecraft/world/level/block/state/EnumProperty.h"

class NewLeafBlock : public LeafBlock {
public:
    static EnumProperty<PlanksBlock::Variant*>* VARIANT;
    NewLeafBlock();

    static void blockStaticCtor();
};
