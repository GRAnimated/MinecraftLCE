#pragma once

#include "net/minecraft/world/level/block/DoublePlantBlock.h"
#include "net/minecraft/world/level/levelgen/feature/Feature.h"

class DoublePlantFeature : public Feature {
public:
    DoublePlantFeature();
    ~DoublePlantFeature() override;
    void setNextPlantType(DoublePlantBlock::Variant*);
    bool place(Level*, Random&, const BlockPos&) override;

private:
    DoublePlantBlock::Variant* m_type;
};

ASSERT_SIZEOF(DoublePlantFeature, 0x18)
