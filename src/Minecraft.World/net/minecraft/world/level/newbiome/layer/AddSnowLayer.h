#pragma once

#include "net/minecraft/world/level/newbiome/layer/Layer.h"

class AddSnowLayer : public Layer {
public:
    AddSnowLayer(long long seed, std::shared_ptr<Layer> parent);

    arrayWithLength<int> getArea(int x, int y, int width, int height) override;
};
