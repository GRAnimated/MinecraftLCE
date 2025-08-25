#include "net/minecraft/world/level/newbiome/layer/RemoveTooMuchOceanLayer.h"

#include "NX/Platform.h"
#include "net/minecraft/world/level/newbiome/layer/IntCache.h"

RemoveTooMuchOceanLayer::RemoveTooMuchOceanLayer(long long seed, std::shared_ptr<Layer> parent)
    : Layer(seed) {
    mParent = parent;
}

arrayWithLength<int> RemoveTooMuchOceanLayer::getArea(int x, int y, int width, int height) {
    int m = x - 1;
    int n = y - 1;
    int o = width + 2;
    int p = height + 2;
    arrayWithLength<int> parentArea = mParent->getArea(m, n, o, p);
    PIXBeginNamedEvent(0.0, "RemoveTooMuchOceanLayer::getArea");
    arrayWithLength<int> area = IntCache::allocate(width * height);

    for (int q = 0; q < height; q++) {
        for (int r = 0; r < width; r++) {
            int s = parentArea[r + 1 + (q + 1 - 1) * (width + 2)];
            int t = parentArea[r + 1 + 1 + (q + 1) * (width + 2)];
            int u = parentArea[r + 1 - 1 + (q + 1) * (width + 2)];
            int v = parentArea[r + 1 + (q + 1 + 1) * (width + 2)];
            int w = parentArea[r + 1 + (q + 1) * o];
            area[r + q * width] = w;
            initRandom(r + x, q + y);
            if (w == 0 && s == 0 && t == 0 && u == 0 && v == 0 && nextRandom(2) == 0) {
                area[r + q * height] = 1;
            }
        }
    }

    PIXEndNamedEvent();
    return area;
}
