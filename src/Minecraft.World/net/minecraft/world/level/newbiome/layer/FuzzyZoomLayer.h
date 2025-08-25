#pragma once

#include "net/minecraft/world/level/newbiome/layer/ZoomLayer.h"

class FuzzyZoomLayer : public ZoomLayer {
public:
    FuzzyZoomLayer(long long seed, std::shared_ptr<Layer> parent);

    int modeOrRandom(int x, int y, int width, int height) override;
};
