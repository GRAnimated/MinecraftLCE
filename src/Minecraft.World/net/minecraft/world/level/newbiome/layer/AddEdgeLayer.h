#pragma once

#include "net/minecraft/world/level/newbiome/layer/Layer.h"

class AddEdgeLayer : public Layer {
public:
    enum Type : int { COOL_WARM, HEAT_ICE, SPECIAL };

    AddEdgeLayer(long long seed, std::shared_ptr<Layer> childLayer, Type type);

    arrayWithLength<int> getArea(int i, int j, int k, int l) override;
};
