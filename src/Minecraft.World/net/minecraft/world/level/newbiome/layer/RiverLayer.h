#pragma once

#include "net/minecraft/world/level/newbiome/layer/Layer.h"

class RiverLayer : public Layer {
public:
    RiverLayer(long long seed, std::shared_ptr<Layer> parent);

    int riverFilter(int id);

    arrayWithLength<int> getArea(int x, int y, int width, int height) override;
};
