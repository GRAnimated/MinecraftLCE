#pragma once

#include "net/minecraft/world/level/newbiome/layer/Layer.h"

class AddEdgeLayer : public Layer {
public:
    enum Mode : int { COOL_WARM, HEAT_ICE, SPECIAL };

    AddEdgeLayer(long long seed, std::shared_ptr<Layer> parent, Mode mode);

    arrayWithLength<int> coolWarm(int x, int y, int width, int height);
    arrayWithLength<int> heatIce(int x, int y, int width, int height);
    arrayWithLength<int> introduceSpecial(int x, int y, int width, int height);

    arrayWithLength<int> getArea(int x, int y, int width, int height) override;

    Mode mMode;
};
