#pragma once

#include "net/minecraft/world/level/newbiome/layer/Layer.h"

class RiverMixerLayer : public Layer {
public:
    RiverMixerLayer(long long seed, std::shared_ptr<Layer> parent, std::shared_ptr<Layer> secondParent);

    arrayWithLength<int> getArea(int x, int y, int width, int height) override;
    void init(long long l) override;

    std::shared_ptr<Layer> mParent1;
    std::shared_ptr<Layer> mSecondParent;
};
