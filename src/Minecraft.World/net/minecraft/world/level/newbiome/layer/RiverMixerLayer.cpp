#include "net/minecraft/world/level/newbiome/layer/RiverMixerLayer.h"

#include "NX/Platform.h"
#include "net/minecraft/world/level/biome/Biome.h"
#include "net/minecraft/world/level/newbiome/layer/IntCache.h"

RiverMixerLayer::RiverMixerLayer(long long seed, std::shared_ptr<Layer> parent,
                                 std::shared_ptr<Layer> secondParent)
    : Layer(seed) {
    mParent1 = parent;
    mSecondParent = secondParent;
}

arrayWithLength<int> RiverMixerLayer::getArea(int x, int y, int width, int height) {
    arrayWithLength<int> parentArea = mParent1->getArea(x, y, width, height);
    arrayWithLength<int> secondParentArea = mSecondParent->getArea(x, y, width, height);
    PIXBeginNamedEvent(0.0, "RiverMixerLayer::getArea");
    arrayWithLength<int> area = IntCache::allocate(width * height);

    for (int m = 0; m < width * height; m++) {
        if (parentArea[m] != Biome::OCEAN->mBiomeID && parentArea[m] != Biome::DEEP_OCEAN->mBiomeID) {
            if (secondParentArea[m] == Biome::RIVER->mBiomeID) {
                if (parentArea[m] == Biome::ICE_PLAINS->mBiomeID) {
                    area[m] = Biome::FROZEN_RIVER->mBiomeID;
                } else if (parentArea[m] != Biome::MUSHROOM_ISLAND->mBiomeID
                           && parentArea[m] != Biome::MUSHROOM_ISLAND_SHORE->mBiomeID) {
                    area[m] = secondParentArea[m] & 255;
                } else {
                    area[m] = Biome::MUSHROOM_ISLAND->mBiomeID;
                }
            } else {
                area[m] = parentArea[m];
            }
        } else {
            area[m] = parentArea[m];
        }
    }

    PIXEndNamedEvent();
    return area;
}

void RiverMixerLayer::init(long long l) {
    mParent1->init(l);
    mSecondParent->init(l);
    Layer::init(l);
}
