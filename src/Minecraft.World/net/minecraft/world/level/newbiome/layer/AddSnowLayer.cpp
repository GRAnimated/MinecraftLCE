#include "net/minecraft/world/level/newbiome/layer/AddSnowLayer.h"

#include "NX/Platform.h"
#include "net/minecraft/world/level/newbiome/layer/IntCache.h"

AddSnowLayer::AddSnowLayer(long long seed, std::shared_ptr<Layer> parent) : Layer(seed) {
    mParent = parent;
}

arrayWithLength<int> AddSnowLayer::getArea(int x, int y, int width, int height) {
    int m = x - 1;
    int n = y - 1;
    int o = width + 2;
    int p = height + 2;
    arrayWithLength<int> parentArea = mParent->getArea(m, n, o, p);
    PIXBeginNamedEvent(0.0, "AddSnowLayer::getArea");
    arrayWithLength<int> area = IntCache::allocate(width * height);

    for (int q = 0; q < height; q++) {
        for (int r = 0; r < width; r++) {
            int s = parentArea[r + 1 + (q + 1) * o];
            initRandom(r + x, q + y);
            if (s == 0) {
                area[r + q * width] = 0;
            } else {
                int t = nextRandom(6);
                if (t == 0) {
                    t = 4;
                } else if (t <= 1) {
                    t = 3;
                } else {
                    t = 1;
                }

                area[r + q * height] = t;
            }
        }
    }

    PIXEndNamedEvent();
    return area;
}
