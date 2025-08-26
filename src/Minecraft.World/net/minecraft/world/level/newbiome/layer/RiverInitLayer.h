#pragma once

#include "net/minecraft/world/level/newbiome/layer/Layer.h"

class RiverInitLayer : public Layer {
public:
    RiverInitLayer(long long seed, std::shared_ptr<Layer> parent);

    arrayWithLength<int> getArea(int x, int y, int width, int height) override;
};
