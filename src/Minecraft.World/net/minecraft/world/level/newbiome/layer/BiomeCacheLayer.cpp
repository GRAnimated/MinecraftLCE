#include "net/minecraft/world/level/newbiome/layer/BiomeCacheLayer.h"

#include "net/minecraft/world/level/newbiome/layer/IntCache.h"
#include <cmath>

BiomeCacheLayer::BiomeCacheLayer(long long seed, std::shared_ptr<Layer> parent, int xzSize,
                                 unsigned char biomeScale, int centreXChunk, int centreZChunk)
    : Layer((int)seed) {
    mParent = parent;
    mParentArea = {};
    mWorldSize = (int)((xzSize & 0xFFFFFFF) << 2);

    int pow = (int)std::pow(2, (double)biomeScale);
    int aa = (centreXChunk * pow) << 2;
    int bb = (centreZChunk * pow) << 2;
    mXScale = aa - (int)(mWorldSize / 2);
    mYScale = bb - (int)(mWorldSize / 2);
}

// NON_MATCHING | Score: 2939 (Lower is better)
arrayWithLength<int> BiomeCacheLayer::getArea(int x, int y, int width, int height) {
    mParentArea = {static_cast<unsigned int>(mWorldSize * mWorldSize), true};
    arrayWithLength<int> parentArea = mParent->getArea(mXScale, mYScale, mWorldSize, mWorldSize);

    for (int m = 0; m < mParentArea.length; m++) {
        mParentArea[m] = parentArea.get(m);
    }

    arrayWithLength<int> area = IntCache::allocate(width * height);

    int p = x - mXScale;
    int o = y - mYScale;
    for (int m = 0; m < height; m++) {
        for (int n = 0; n < width; n++) {
            int a = mWorldSize - 1;
            int b = mWorldSize - 1;

            if (p < a) {
                a = p;
            }

            if (m + o < b) {
                b = m + o;
            }

            area[n + m * width] = mParentArea[(a & ~(a >> 31)) + (b & ~(b >> 31)) * mWorldSize];
        }
    }

    return area;
}
