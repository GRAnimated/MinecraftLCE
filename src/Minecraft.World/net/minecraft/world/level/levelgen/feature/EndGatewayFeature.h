#pragma once

#include "net/minecraft/world/level/levelgen/feature/Feature.h"
#include "types.h"

class EndGatewayFeature : public Feature {
public:
    explicit EndGatewayFeature(int portalNumber);
    bool place(Level*, Random&, const BlockPos&) override;

private:
    int m_portalNumber;
};

ASSERT_SIZEOF(EndGatewayFeature, 0x10)
