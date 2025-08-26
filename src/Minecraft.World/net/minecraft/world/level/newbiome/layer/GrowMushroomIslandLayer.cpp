#include "net/minecraft/world/level/newbiome/layer/GrowMushroomIslandLayer.h"

#include "NX/Platform.h"
#include "net/minecraft/world/level/biome/Biome.h"
#include "net/minecraft/world/level/newbiome/layer/IntCache.h"

GrowMushroomIslandLayer::GrowMushroomIslandLayer(long long seed, std::shared_ptr<Layer> parent)
    : Layer(seed) {
    mParent = parent;
}

arrayWithLength<int> GrowMushroomIslandLayer::getArea(int x, int y, int width, int height) {
    int m = x - 1;
    int n = y - 1;
    int o = width + 2;
    int p = height + 2;
    arrayWithLength<int> parentArea = mParent->getArea(m, n, o, p);
    PIXBeginNamedEvent(0.0, "GrowMushroomIslandLayer::getArea");
    arrayWithLength<int> area = IntCache::allocate(width * height);

    for (int q = 0; q < height; q++) {
        for (int r = 0; r < width; r++) {
            int s = parentArea[r + 0 + (q + 0) * o];
            int t = parentArea[r + 2 + (q + 0) * o];
            int u = parentArea[r + 0 + (q + 2) * o];
            int v = parentArea[r + 2 + (q + 2) * o];
            int w = parentArea[r + 1 + (q + 1) * o];
            if (s == 14 || t == 14 || u == 14 || v == 14) {
                area[r + q * width] = 14;
            } else {
                area[r + q * width] = w;
            }
        }
    }

    PIXEndNamedEvent();
    return area;
}
