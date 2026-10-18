#pragma once

#include "net/minecraft/world/level/levelgen/feature/LargeFeature.h"
#include "types.h"

class CanyonFeature : public LargeFeature {
public:
    CanyonFeature() = default;
    void addFeature(Level*, int, int, int, int, ChunkPrimer*) override;
    void addTunnel(long long, int, int, ChunkPrimer*, double, double, double, float, float, float, int, int,
                   double);

    float m_widths[128];
    char m_padding[0xe00];
};

ASSERT_SIZEOF(CanyonFeature, 0x1030)
