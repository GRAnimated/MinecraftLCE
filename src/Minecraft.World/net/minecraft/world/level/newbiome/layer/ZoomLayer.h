#pragma once

#include "net/minecraft/world/level/newbiome/layer/Layer.h"

class ZoomLayer : public Layer {
public:
    static std::shared_ptr<Layer> zoom(long long seed, std::shared_ptr<Layer> layer, int i);

    ZoomLayer(long long seed, std::shared_ptr<Layer> childLayer);

    arrayWithLength<int> getArea(int i, int j, int k, int l) override;
};
