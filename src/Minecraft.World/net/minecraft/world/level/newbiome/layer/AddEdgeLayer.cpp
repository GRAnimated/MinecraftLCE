#include "net/minecraft/world/level/newbiome/layer/AddEdgeLayer.h"

#include "NX/Platform.h"
#include "net/minecraft/world/level/newbiome/layer/IntCache.h"

AddEdgeLayer::AddEdgeLayer(long long seed, std::shared_ptr<Layer> parent, AddEdgeLayer::Mode mode)
    : Layer(seed) {
    mParent = parent;
    mMode = mode;
}

arrayWithLength<int> AddEdgeLayer::coolWarm(int x, int y, int width, int height) {
    int m = x - 1;
    int n = y - 1;
    int o = 1 + width + 1;
    int p = 1 + height + 1;
    arrayWithLength<int> parentArea = mParent->getArea(m, n, o, p);
    PIXBeginNamedEvent(0.0, "AddEdgeLayer::getArea");
    arrayWithLength<int> area = IntCache::allocate(width * height);

    for (int q = 0; q < height; q++) {
        for (int r = 0; r < width; r++) {
            initRandom(r + x, q + y);
            int s = parentArea[r + 1 + (q + 1) * o];
            if (s == 1) {
                int t = parentArea[r + 1 + (q + 1 - 1) * o];
                int u = parentArea[r + 1 + 1 + (q + 1) * o];
                int v = parentArea[r + 1 - 1 + (q + 1) * o];
                int w = parentArea[r + 1 + (q + 1 + 1) * o];
                bool bl = t == 3 || u == 3 || v == 3 || w == 3;
                bool bl2 = t == 4 || u == 4 || v == 4 || w == 4;
                if (bl || bl2) {
                    s = 2;
                }
            }

            area[r + q * height] = s;
        }
    }

    PIXEndNamedEvent();
    return area;
}

arrayWithLength<int> AddEdgeLayer::heatIce(int x, int y, int width, int height) {
    int m = x - 1;
    int n = y - 1;
    int o = 1 + width + 1;
    int p = 1 + height + 1;
    arrayWithLength<int> parentArea = mParent->getArea(m, n, o, p);
    arrayWithLength<int> area = IntCache::allocate(width * height);

    for (int q = 0; q < height; q++) {
        for (int r = 0; r < width; r++) {
            int s = parentArea[r + 1 + (q + 1) * o];
            if (s == 4) {
                int t = parentArea[r + 1 + (q + 1 - 1) * o];
                int u = parentArea[r + 1 + 1 + (q + 1) * o];
                int v = parentArea[r + 1 - 1 + (q + 1) * o];
                int w = parentArea[r + 1 + (q + 1 + 1) * o];
                bool bl = t == 2 || u == 2 || v == 2 || w == 2;
                bool bl2 = t == 1 || u == 1 || v == 1 || w == 1;
                if (bl2 || bl) {
                    s = 3;
                }
            }

            area[r + q * height] = s;
        }
    }

    return area;
}

arrayWithLength<int> AddEdgeLayer::introduceSpecial(int x, int y, int width, int height) {
    arrayWithLength<int> parentArea = mParent->getArea(x, y, width, height);
    arrayWithLength<int> area = IntCache::allocate(width * height);

    for (int m = 0; m < height; m++) {
        for (int n = 0; n < width; n++) {
            initRandom(n + x, m + y);
            int o = parentArea[n + m * width];
            if (o != 0 && nextRandom(13) == 0) {
                o |= (1 + nextRandom(15)) << 8 & 3840;
            }

            area[n + m * width] = o;
        }
    }

    return area;
}

arrayWithLength<int> AddEdgeLayer::getArea(int i, int j, int k, int l) {
    switch (mMode) {
    case COOL_WARM:
    default:
        return coolWarm(i, j, k, l);
    case HEAT_ICE:
        return heatIce(i, j, k, l);
    case SPECIAL:
        return introduceSpecial(i, j, k, l);
    }
}
