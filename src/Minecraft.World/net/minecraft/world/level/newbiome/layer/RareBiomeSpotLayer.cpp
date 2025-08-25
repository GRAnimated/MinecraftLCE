#include "net/minecraft/world/level/newbiome/layer/RareBiomeSpotLayer.h"

#include "NX/Platform.h"
#include "net/minecraft/world/level/biome/Biome.h"
#include "net/minecraft/world/level/newbiome/layer/IntCache.h"

RareBiomeSpotLayer::RareBiomeSpotLayer(long long seed, std::shared_ptr<Layer> parent) : Layer(seed) {
    mParent = parent;
}

arrayWithLength<int> RareBiomeSpotLayer::getArea(int x, int y, int width, int height) {
    arrayWithLength<int> parentArea = mParent->getArea(x - 1, y - 1, width + 2, height + 2);
    PIXBeginNamedEvent(0.0, "RareBiomeSpotLayer::getArea");
    arrayWithLength<int> area = IntCache::allocate(width * height);

    for (int m = 0; m < height; m++) {
        for (int n = 0; n < width; n++) {
            initRandom(n + x, m + y);
            int o = parentArea[n + 1 + (m + 1) * (width + 2)];
            if (nextRandom(57) == 0) {
                if (o == Biome::PLAINS->mBiomeID) {
                    area[n + m * width] = Biome::SUNFLOWER_PLAINS->mBiomeID;
                } else {
                    area[n + m * width] = o;
                }
            } else {
                area[n + m * width] = o;
            }
        }
    }

    PIXEndNamedEvent();
    return area;
}
