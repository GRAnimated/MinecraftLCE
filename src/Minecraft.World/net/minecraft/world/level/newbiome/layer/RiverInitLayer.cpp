#include "net/minecraft/world/level/newbiome/layer/RiverInitLayer.h"

#include "NX/Platform.h"
#include "net/minecraft/world/level/newbiome/layer/IntCache.h"

RiverInitLayer::RiverInitLayer(long long seed, std::shared_ptr<Layer> parent) : Layer(seed) {
    mParent = parent;
}

arrayWithLength<int> RiverInitLayer::getArea(int x, int y, int width, int height) {
    arrayWithLength<int> parentArea = mParent->getArea(x, y, width, height);
    PIXBeginNamedEvent(0.0, "RiverInitLayer::getArea");
    arrayWithLength<int> area = IntCache::allocate(width * height);

    for (int m = 0; m < height; m++) {
        for (int n = 0; n < width; n++) {
            initRandom(n + x, m + y);
            area[n + m * width] = parentArea[n + m * width] > 0 ? nextRandom(299999) + 2 : 0;
        }
    }

    PIXEndNamedEvent();
    return area;
}
