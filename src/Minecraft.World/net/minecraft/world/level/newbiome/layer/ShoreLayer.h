#pragma once

#include "net/minecraft/world/level/newbiome/layer/Layer.h"

class ShoreLayer : public Layer {
public:
    ShoreLayer(long long seed, std::shared_ptr<Layer> parent);

    void replaceIfNeighborOcean(arrayWithLength<int> array0, arrayWithLength<int> array1, int i, int j, int k,
                                int l, int m);
    bool isJungleCompatible(int biomeId);
    bool isMesa(int biomeId);

    arrayWithLength<int> getArea(int x, int y, int width, int height) override;
};
