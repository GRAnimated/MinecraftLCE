#pragma once

#include "net/minecraft/world/level/newbiome/layer/ZoomLayer.h"

class FuzzyZoomLayer : public ZoomLayer {
public:
    FuzzyZoomLayer(long long seed, std::shared_ptr<Layer> childLayer);
};
