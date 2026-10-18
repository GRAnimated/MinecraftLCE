#pragma once

#include "net/minecraft/world/level/levelgen/feature/Feature.h"
#include "types.h"

class Block;

class HugeMushroomFeature : public Feature {
public:
    HugeMushroomFeature();
    HugeMushroomFeature(Block*);
    ~HugeMushroomFeature() override = default;
    bool place(Level*, Random&, const BlockPos&) override;

private:
    Block* m_type;
};

ASSERT_SIZEOF(HugeMushroomFeature, 0x18)
