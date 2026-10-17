#pragma once

#include "net/minecraft/world/level/block/LeafBlock.h"
#include "net/minecraft/world/level/block/PlanksBlock.h"

class OldLeafBlock : public LeafBlock {
public:
    static EnumProperty<PlanksBlock::Variant*>* VARIANT;
    OldLeafBlock();

    static void blockStaticCtor();
};
