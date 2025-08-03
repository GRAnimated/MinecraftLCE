#pragma once

#include "net/minecraft/world/level/block/TransparentBlock.h"
#include "net/minecraft/world/level/block/state/BooleanProperty.h"

class LeafBlock : public TransparentBlock {
public:
    static bool isLeaves(Block*);

    void setFancy(bool);

    static BooleanProperty* CHECK_DECAY;
};
