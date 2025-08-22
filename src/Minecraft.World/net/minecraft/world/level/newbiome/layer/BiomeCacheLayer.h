#pragma once

#include "net/minecraft/world/level/newbiome/layer/Layer.h"

class BiomeCacheLayer : public Layer {
public:
    BiomeCacheLayer(long long seed, std::shared_ptr<Layer> childLayer, int, unsigned int biomeScale, int,
                    int);

    arrayWithLength<int> getArea(int i, int j, int k, int l) override;
};
