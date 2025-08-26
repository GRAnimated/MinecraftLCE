#include "net/minecraft/world/level/newbiome/layer/IslandLayer.h"

#include "NX/Platform.h"
#include "net/minecraft/world/level/newbiome/layer/IntCache.h"

IslandLayer::IslandLayer(long long seed) : Layer(seed) {}

arrayWithLength<int> IslandLayer::getArea(int x, int y, int width, int height) {
    PIXBeginNamedEvent(0.0, "IslandLayer::getArea");
    arrayWithLength<int> area = IntCache::allocate(width * height);

    for (int m = 0; m < height; m++) {
        for (int n = 0; n < width; n++) {
            initRandom(x + n, y + m);
            area[n + m * width] = nextRandom(10) == 0 ? 1 : 0;
        }
    }

    if (x > -width && x <= 0 && y > -height && y <= 0) {
        area[-x + -y * width] = 1;
    }

    PIXEndNamedEvent();
    return area;
}
