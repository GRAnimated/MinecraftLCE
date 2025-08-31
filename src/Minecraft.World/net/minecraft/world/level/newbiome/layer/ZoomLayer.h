#pragma once

#include "net/minecraft/world/level/newbiome/layer/Layer.h"

class ZoomLayer : public Layer {
public:
    static std::shared_ptr<Layer> zoom(long long seed, std::shared_ptr<Layer> layer, int i);

    ZoomLayer(long long seed, std::shared_ptr<Layer> parent);

    arrayWithLength<int> getArea(int x, int y, int width, int height) override;
};
