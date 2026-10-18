#pragma once

#include "net/minecraft/world/level/biome/Biome.h"

class IceBiome : public Biome {
public:
    enum EType { DEFAULT = 0, SPIKES = 1 };

    IceBiome(EBiomeIDs id, bool spikes, BiomeProperties* properties);

    int getBaseClass() override;
    float getCreatureProbability() override;
    Feature* getTreeFeature(Random&) override;
    void decorate(Level*, Random&, const BlockPos&) override;

private:
    bool m_spikes;
    Feature* m_spikeFeature;
    Feature* m_patchFeature;
};

ASSERT_SIZEOF(IceBiome, 0x158)
