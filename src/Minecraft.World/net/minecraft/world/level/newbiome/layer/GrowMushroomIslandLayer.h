#pragma once

#include "net/minecraft/world/level/newbiome/layer/Layer.h"

class GrowMushroomIslandLayer : public Layer {
public:
    GrowMushroomIslandLayer(long long seed, std::shared_ptr<Layer> parent);

    arrayWithLength<int> getArea(int x, int y, int width, int height) override;
};
