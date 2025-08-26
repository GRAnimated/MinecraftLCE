#include "net/minecraft/world/level/newbiome/layer/ZoomLayer.h"

#include "NX/Platform.h"
#include "net/minecraft/core/System.h"
#include "net/minecraft/world/level/newbiome/layer/IntCache.h"

std::shared_ptr<Layer> ZoomLayer::zoom(long long seed, std::shared_ptr<Layer> layer, int i) {
    std::shared_ptr<Layer> finalLayer = layer;

    for (int j = 0; j < i; ++j) {
        finalLayer = static_cast<std::shared_ptr<Layer>>(new ZoomLayer(seed + j, finalLayer));
    }

    return finalLayer;
}

ZoomLayer::ZoomLayer(long long seed, std::shared_ptr<Layer> parent) : Layer(seed) {
    mParent = parent;
}

// NON_MATCHING | Score: 995 (Lower is better)
// There is smth with the "newArea" variable that's causing the score
// to be so high. In IDA and Ghidra, it seems to be some sort of
// pointer/array, but doing so doesn't seem to give the same results.
arrayWithLength<int> ZoomLayer::getArea(int x, int y, int width, int height) {
    int m = x >> 1;
    int n = y >> 1;
    int o = (width >> 1) + 2;
    int p = (height >> 1) + 2;
    arrayWithLength<int> parentArea = mParent->getArea(m, n, o, p);
    PIXBeginNamedEvent(0.0, "ZoomLayer::getArea");
    int q = (o - 1) << 1;
    int r = (p - 1) << 1;
    arrayWithLength<int> area = IntCache::allocate(q * r);

    for (int s = 0; s < p - 1; s++) {
        int t = (s << 1) * q;
        int u = 0;
        int v = parentArea[u + 0 + (s + 0) * o];

        for (int w = parentArea[u + 0 + (s + 1) * o]; u < o - 1; u++) {
            initRandom((u + m) << 1, (s + n) << 1);
            int x1 = parentArea[u + 1 + (s + 0) * o];
            int y1 = parentArea[u + 1 + (s + 1) * o];
            area[t] = v;
            area[t++ + q] = random(v, w);
            area[t] = random(v, x1);
            area[t++ + q] = random(v, x1, w, y1);
            v = x1;
            w = y1;
        }
    }

    arrayWithLength<int> newArea = IntCache::allocate(width * height);

    for (int t = 0; t < height; t++) {
        System::arraycopy(area, (t + (y & 1)) * q + (x & 1), &newArea, t * width, width);
    }

    PIXEndNamedEvent();
    return newArea;
}
