#pragma once

#include "net/minecraft/world/level/levelgen/feature/Feature.h"
#include "types.h"

class EndPodiumFeature : public Feature {
public:
    explicit EndPodiumFeature(bool active);
    bool place(Level*, Random&, const BlockPos&) override;

private:
    bool m_active;
};

ASSERT_SIZEOF(EndPodiumFeature, 0x10)
