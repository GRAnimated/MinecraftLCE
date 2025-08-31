#pragma once

#include "net/minecraft/world/level/newbiome/layer/Layer.h"

class RegionHillsLayer : public Layer {
public:
    RegionHillsLayer(long long seed, std::shared_ptr<Layer> parent, std::shared_ptr<Layer> secondParent);

    arrayWithLength<int> getArea(int x, int y, int width, int height) override;

    std::shared_ptr<Layer> mSecondParent;
};
