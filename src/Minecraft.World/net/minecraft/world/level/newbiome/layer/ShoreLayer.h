#pragma once

#include "net/minecraft/world/level/newbiome/layer/Layer.h"

class ShoreLayer : public Layer {
public:
    ShoreLayer(long long seed, std::shared_ptr<Layer> childLayer);

    arrayWithLength<int> getArea(int i, int j, int k, int l) override;
};
