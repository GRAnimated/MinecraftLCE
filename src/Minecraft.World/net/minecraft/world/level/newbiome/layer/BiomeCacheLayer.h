#pragma once

#include "net/minecraft/world/level/newbiome/layer/Layer.h"

class BiomeCacheLayer : public Layer {
public:
    BiomeCacheLayer(long long seed, std::shared_ptr<Layer> parent, int xzSize, unsigned char biomeScale,
                    int centreXChunk, int centreZChunk);

    arrayWithLength<int> getArea(int x, int y, int width, int height) override;

    int mXScale;
    int mYScale;
    int mWorldSize;
    arrayWithLength<unsigned char> mParentArea;
};
