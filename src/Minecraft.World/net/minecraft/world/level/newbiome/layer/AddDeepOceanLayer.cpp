#include "net/minecraft/world/level/newbiome/layer/AddDeepOceanLayer.h"

#include "NX/Platform.h"
#include "net/minecraft/world/level/biome/Biome.h"
#include "net/minecraft/world/level/newbiome/layer/IntCache.h"

AddDeepOceanLayer::AddDeepOceanLayer(long long seed, std::shared_ptr<Layer> parent) : Layer(seed) {
    mParent = parent;
}

arrayWithLength<int> AddDeepOceanLayer::getArea(int x, int y, int width, int height) {
    int m = x - 1;
    int n = y - 1;
    int o = width + 2;
    int p = height + 2;
    arrayWithLength<int> parentArea = mParent->getArea(m, n, o, p);
    PIXBeginNamedEvent(0.0, "AddDeepOceanLayer::getArea");
    arrayWithLength<int> area = IntCache::allocate(width * height);

    for (int q = 0; q < height; q++) {
        for (int r = 0; r < width; r++) {
            int s = parentArea[r + 1 + (q + 1 - 1) * (width + 2)];
            int t = parentArea[r + 1 + 1 + (q + 1) * (width + 2)];
            int u = parentArea[r + 1 - 1 + (q + 1) * (width + 2)];
            int v = parentArea[r + 1 + (q + 1 + 1) * (width + 2)];
            int w = parentArea[r + 1 + (q + 1) * o];
            int x1 = 0;
            if (s == 0) {
                ++x1;
            }

            if (t == 0) {
                ++x1;
            }

            if (u == 0) {
                ++x1;
            }

            if (v == 0) {
                ++x1;
            }

            if (w == 0 && x1 > 3) {
                area[r + q * width] = Biome::DEEP_OCEAN->mBiomeID;
            } else {
                area[r + q * width] = w;
            }
        }
    }

    PIXEndNamedEvent();
    return area;
}
