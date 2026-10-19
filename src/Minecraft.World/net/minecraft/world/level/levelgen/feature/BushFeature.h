#pragma once

#include "net/minecraft/world/level/levelgen/feature/Feature.h"
#include "types.h"

class Bush;

class BushFeature : public Feature {
public:
    BushFeature(Bush*);
    ~BushFeature() override;
    bool place(Level*, Random&, const BlockPos&) override;

private:
    Bush* m_bush;
};

ASSERT_SIZEOF(BushFeature, 0x18)
