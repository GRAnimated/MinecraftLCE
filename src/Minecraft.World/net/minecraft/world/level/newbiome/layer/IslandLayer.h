#pragma once

#include "net/minecraft/world/level/newbiome/layer/Layer.h"

class IslandLayer : public Layer {
public:
    IslandLayer(long long seed);

    arrayWithLength<int> getArea(int x, int y, int width, int height) override;
};
