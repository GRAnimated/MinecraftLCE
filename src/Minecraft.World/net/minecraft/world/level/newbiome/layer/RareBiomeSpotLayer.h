#pragma once

#include "net/minecraft/world/level/newbiome/layer/Layer.h"

class RareBiomeSpotLayer : public Layer {
public:
    RareBiomeSpotLayer(long long seed, std::shared_ptr<Layer> childLayer);

    arrayWithLength<int> getArea(int i, int j, int k, int l) override;
};
