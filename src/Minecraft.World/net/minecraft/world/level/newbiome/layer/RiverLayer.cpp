#include "net/minecraft/world/level/newbiome/layer/RiverLayer.h"

#include "NX/Platform.h"
#include "net/minecraft/world/level/biome/Biome.h"
#include "net/minecraft/world/level/newbiome/layer/IntCache.h"

RiverLayer::RiverLayer(long long seed, std::shared_ptr<Layer> parent) : Layer(seed) {
    mParent = parent;
}

arrayWithLength<int> RiverLayer::getArea(int x, int y, int width, int height) {
    int m = x - 1;
    int n = y - 1;
    int o = width + 2;
    int p = height + 2;
    arrayWithLength<int> parentArea = mParent->getArea(m, n, o, p);
    PIXBeginNamedEvent(0.0, "RiverLayer::getArea");
    arrayWithLength<int> area = IntCache::allocate(width * height);

    for (int q = 0; q < height; q++) {
        for (int r = 0; r < width; r++) {
            int s = riverFilter(parentArea[r + 0 + (q + 1) * o]);
            int t = riverFilter(parentArea[r + 2 + (q + 1) * o]);
            int u = riverFilter(parentArea[r + 1 + (q + 0) * o]);
            int v = riverFilter(parentArea[r + 1 + (q + 2) * o]);
            int w = riverFilter(parentArea[r + 1 + (q + 1) * o]);
            if (w == s && w == u && w == t && w == v) {
                area[r + q * width] = -1;
            } else {
                area[r + q * width] = Biome::RIVER->mBiomeID;
            }
        }
    }

    PIXEndNamedEvent();
    return area;
}

int RiverLayer::riverFilter(int id) {
    return id >= 2 ? 2 + (id & 1) : id;
}
