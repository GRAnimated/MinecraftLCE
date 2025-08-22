#pragma once

#include "net/minecraft/world/level/newbiome/layer/Layer.h"

class RegionHillsLayer : public Layer {
public:
    RegionHillsLayer(long long seed, std::shared_ptr<Layer> childLayer, std::shared_ptr<Layer> childLayer2);

    arrayWithLength<int> getArea(int i, int j, int k, int l) override;
};
