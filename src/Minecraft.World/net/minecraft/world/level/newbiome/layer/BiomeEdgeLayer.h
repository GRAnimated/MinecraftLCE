#pragma once

#include "net/minecraft/world/level/newbiome/layer/Layer.h"

class BiomeEdgeLayer : public Layer {
public:
    BiomeEdgeLayer(long long seed, std::shared_ptr<Layer> parent);

    bool checkEdge(arrayWithLength<int> array0, arrayWithLength<int> array1, int i, int j, int k, int l,
                   int m, int n);
    bool checkEdgeStrict(arrayWithLength<int> array0, arrayWithLength<int> array1, int i, int j, int k, int l,
                         int m, int n);
    bool isValidTemperatureEdge(int biomeId0, int biomeId1);

    arrayWithLength<int> getArea(int x, int y, int width, int height) override;
};
