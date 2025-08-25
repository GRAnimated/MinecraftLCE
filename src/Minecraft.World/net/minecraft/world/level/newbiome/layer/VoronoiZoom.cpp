#include "net/minecraft/world/level/newbiome/layer/VoronoiZoom.h"

#include "NX/Platform.h"
#include "net/minecraft/core/System.h"
#include "net/minecraft/world/level/newbiome/layer/IntCache.h"

VoronoiZoom::VoronoiZoom(long long seed, std::shared_ptr<Layer> parent) : Layer(seed) {
    mParent = parent;
}

// NON_MATCHING | Score: 652 (Lower is better)
// It's smth with the array copying, I just can't figure it out
arrayWithLength<int> VoronoiZoom::getArea(int x, int y, int width, int height) {
    x -= 2;
    y -= 2;
    int m = x >> 2;
    int n = y >> 2;
    int o = (width >> 2) + 2;
    int p = (height >> 2) + 2;
    arrayWithLength<int> parentArea = mParent->getArea(m, n, o, p);
    PIXBeginNamedEvent(0.0, "VoronoiZoom::getArea");
    int q = (o - 1) << 2;
    int r = (p - 1) << 2;
    arrayWithLength<int> area = IntCache::allocate(q * r);

    for (int s = 0; s < p - 1; s++) {
        int t = 0;
        int u = parentArea[t + 0 + (s + 0) * o];

        for (int v = parentArea[t + 0 + (s + 1) * o]; t < o - 1; t++) {
            initRandom((t + m) << 2, (s + n) << 2);
            double e = (nextRandom(1024) / 1024.0 - 0.5) * 3.6;
            double f = (nextRandom(1024) / 1024.0 - 0.5) * 3.6;
            initRandom((t + m + 1) << 2, (s + n) << 2);
            double g = (nextRandom(1024) / 1024.0 - 0.5) * 3.6 + 4.0;
            double h = (nextRandom(1024) / 1024.0 - 0.5) * 3.6;
            initRandom((t + m) << 2, (s + n + 1) << 2);
            double w = (nextRandom(1024) / 1024.0 - 0.5) * 3.6;
            double x1 = (nextRandom(1024) / 1024.0 - 0.5) * 3.6 + 4.0;
            initRandom((t + m + 1) << 2, (s + n + 1) << 2);
            double y1 = (nextRandom(1024) / 1024.0 - 0.5) * 3.6 + 4.0;
            double z = (nextRandom(1024) / 1024.0 - 0.5) * 3.6 + 4.0;
            int aa = parentArea[t + 1 + (s + 0) * o] & 255;
            int ab = parentArea[t + 1 + (s + 1) * o] & 255;

            for (int ac = 0; ac < 4; ac++) {
                int ad = ((s << 2) + ac) * q + (t << 2);

                for (int ae = 0; ae < 4; ae++) {
                    double af = (ac - f) * (ac - f) + (ae - e) * (ae - e);
                    double ag = (ac - h) * (ac - h) + (ae - g) * (ae - g);
                    double ah = (ac - x1) * (ac - x1) + (ae - w) * (ae - w);
                    double ai = (ac - z) * (ac - z) + (ae - y1) * (ae - y1);
                    if (af < ag && af < ah && af < ai) {
                        area[ad++] = u;
                    } else if (ag < af && ag < ah && ag < ai) {
                        area[ad++] = aa;
                    } else if (ah < af && ah < ag && ah < ai) {
                        area[ad++] = v;
                    } else {
                        area[ad++] = ab;
                    }
                }
            }

            u = aa;
            v = ab;
        }
    }

    arrayWithLength<int> newArea = IntCache::allocate(width * height);

    for (int t = 0; t < height; ++t) {
        System::arraycopy(area, (t + (y & 3)) * q + (x & 3), &newArea, t * width, width);
    }

    PIXEndNamedEvent();
    return newArea;
}
