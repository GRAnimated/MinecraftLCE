#pragma once

#include "net/minecraft/world/level/gamemode/minigames/MapGenerator.h"

class LayerGenerator;

class TumbleGenerator : public MapGenerator {
public:
    TumbleGenerator(Random, std::vector<LayerGenerator*>&);

    ~TumbleGenerator() override;
    void StartGeneration(Level* level) override;
    const AABB* GetSpawnArea() const override;
    void CleanUp(Level* level) override;
    const AABB* GetLayerBB(unsigned int layer) override;
    unsigned int GetNumberOfLayers() override;
    void GetLayerExtents(unsigned int layer, float*, float*) override;
    int GetBlockCountOnLayer(unsigned int layer) override;

    char m_fill0x48[0x48];
};
