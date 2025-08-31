#include "net/minecraft/world/level/newbiome/layer/SmoothLayer.h"

#include "NX/Platform.h"
#include "net/minecraft/world/level/newbiome/layer/IntCache.h"

SmoothLayer::SmoothLayer(long long seed, std::shared_ptr<Layer> parent) : Layer(seed) {
    mParent = parent;
}

arrayWithLength<int> SmoothLayer::getArea(int x, int y, int width, int height) {
    int m = x - 1;
    int n = y - 1;
    int o = width + 2;
    int p = height + 2;
    arrayWithLength<int> parentArea = mParent->getArea(m, n, o, p);
    PIXBeginNamedEvent(0.0, "SmoothLayer::getArea");
    arrayWithLength<int> area = IntCache::allocate(width * height);

    for (int q = 0; q < height; q++) {
        for (int r = 0; r < width; r++) {
            int s = parentArea[r + 0 + (q + 1) * o];
            int t = parentArea[r + 2 + (q + 1) * o];
            int u = parentArea[r + 1 + (q + 0) * o];
            int v = parentArea[r + 1 + (q + 2) * o];
            int w = parentArea[r + 1 + (q + 1) * o];
            if (s == t && u == v) {
                initRandom(r + x, q + y);
                if (nextRandom(2) == 0) {
                    w = s;
                } else {
                    w = u;
                }
            } else {
                if (s == t) {
                    w = s;
                }

                if (u == v) {
                    w = u;
                }
            }

            area[r + q * width] = w;
        }
    }

    PIXEndNamedEvent();
    return area;
}
