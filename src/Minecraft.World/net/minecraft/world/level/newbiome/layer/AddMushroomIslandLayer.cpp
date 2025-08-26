#include "net/minecraft/world/level/newbiome/layer/AddMushroomIslandLayer.h"

#include "NX/Platform.h"
#include "net/minecraft/world/level/biome/Biome.h"
#include "net/minecraft/world/level/newbiome/layer/IntCache.h"

AddMushroomIslandLayer::AddMushroomIslandLayer(long long seed, std::shared_ptr<Layer> parent) : Layer(seed) {
    mParent = parent;
}

arrayWithLength<int> AddMushroomIslandLayer::getArea(int x, int y, int width, int height) {
    int m = x - 1;
    int n = y - 1;
    int o = width + 2;
    int p = height + 2;
    arrayWithLength<int> parentArea = mParent->getArea(m, n, o, p);
    PIXBeginNamedEvent(0.0, "AddMushroomIslandLayer::getArea");
    arrayWithLength<int> area = IntCache::allocate(width * height);

    for (int q = 0; q < height; q++) {
        for (int r = 0; r < width; r++) {
            int s = parentArea[r + 0 + (q + 0) * o];
            int t = parentArea[r + 2 + (q + 0) * o];
            int u = parentArea[r + 0 + (q + 2) * o];
            int v = parentArea[r + 2 + (q + 2) * o];
            int w = parentArea[r + 1 + (q + 1) * o];
            initRandom(r + x, q + y);
            if (w == 0 && s == 0 && t == 0 && u == 0 && v == 0 && nextRandom(100) == 0) {
                area[r + q * width] = Biome::MUSHROOM_ISLAND->mBiomeID;
            } else {
                area[r + q * width] = w;
            }
        }
    }

    PIXEndNamedEvent();
    return area;
}
