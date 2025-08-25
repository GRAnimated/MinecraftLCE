#include "net/minecraft/world/level/newbiome/layer/AddIslandLayer.h"

#include "NX/Platform.h"
#include "net/minecraft/world/level/newbiome/layer/IntCache.h"

AddIslandLayer::AddIslandLayer(long long seed, std::shared_ptr<Layer> parent) : Layer(seed) {
    mParent = parent;
}

arrayWithLength<int> AddIslandLayer::getArea(int x, int y, int width, int height) {
    int m = x - 1;
    int n = y - 1;
    int o = width + 2;
    int p = height + 2;
    arrayWithLength<int> parentArea = mParent->getArea(m, n, o, p);
    PIXBeginNamedEvent(0.0, "AddIslandLayer::getArea");
    arrayWithLength<int> area = IntCache::allocate(width * height);

    for (int q = 0; q < height; q++) {
        for (int r = 0; r < width; r++) {
            int s = parentArea[r + 0 + (q + 0) * o];
            int t = parentArea[r + 2 + (q + 0) * o];
            int u = parentArea[r + 0 + (q + 2) * o];
            int v = parentArea[r + 2 + (q + 2) * o];
            int w = parentArea[r + 1 + (q + 1) * o];
            initRandom(r + x, q + y);
            if (w != 0 || (s == 0 && t == 0 && u == 0 && v == 0)) {
                if (w > 0 && (s == 0 || t == 0 || u == 0 || v == 0)) {
                    if (nextRandom(5) == 0) {
                        if (w == 4) {
                            area[r + q * width] = 4;
                        } else {
                            area[r + q * width] = 0;
                        }
                    } else {
                        area[r + q * width] = w;
                    }
                } else {
                    area[r + q * width] = w;
                }
            } else {
                int x1 = 1;
                int y1 = 1;
                if (s != 0 && nextRandom(x1++) == 0) {
                    y1 = s;
                }

                if (t != 0 && nextRandom(x1++) == 0) {
                    y1 = t;
                }

                if (u != 0 && nextRandom(x1++) == 0) {
                    y1 = u;
                }

                if (v != 0 && nextRandom(x1++) == 0) {
                    y1 = v;
                }

                if (nextRandom(3) == 0) {
                    area[r + q * width] = y1;
                } else if (y1 == 4) {
                    area[r + q * width] = 4;
                } else {
                    area[r + q * width] = 0;
                }
            }
        }
    }

    PIXEndNamedEvent();
    return area;
}
