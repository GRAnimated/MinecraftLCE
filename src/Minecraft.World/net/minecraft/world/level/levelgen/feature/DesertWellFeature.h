#pragma once

#include "net/minecraft/world/level/block/state/properties/AbstractProperty.h"
#include "net/minecraft/world/level/levelgen/feature/Feature.h"
#include "types.h"

class DesertWellFeature : public Feature {
public:
    DesertWellFeature();
    static void staticCtor();
    bool place(Level*, Random&, const BlockPos&) override;

    static Predicate<const BlockState*>* SAND_PREDICATE;
    const BlockState* m_slab;
    const BlockState* m_sandstone;
    const BlockState* m_water;
};

ASSERT_SIZEOF(DesertWellFeature, 0x28)
