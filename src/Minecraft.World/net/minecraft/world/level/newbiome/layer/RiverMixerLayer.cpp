#include "net/minecraft/world/level/newbiome/layer/RiverMixerLayer.h"

#include "NX/Platform.h"
#include "net/minecraft/world/level/biome/Biome.h"
#include "net/minecraft/world/level/newbiome/layer/IntCache.h"

RiverMixerLayer::RiverMixerLayer(long long seed, std::shared_ptr<Layer> parent,
                                 std::shared_ptr<Layer> secondParent)
    : Layer(seed) {
    m_parent1 = parent;
    m_secondParent = secondParent;
}

arrayWithLength<int> RiverMixerLayer::getArea(int x, int y, int width, int height) {
    arrayWithLength<int> parentArea = m_parent1->getArea(x, y, width, height);
    arrayWithLength<int> secondParentArea = m_secondParent->getArea(x, y, width, height);
    PIXBeginNamedEvent(0.0, "RiverMixerLayer::getArea");
    arrayWithLength<int> area = IntCache::allocate(width * height);

    for (int m = 0; m < width * height; m++) {
        if (parentArea[m] != Biome::OCEAN->m_biomeId && parentArea[m] != Biome::DEEP_OCEAN->m_biomeId) {
            if (secondParentArea[m] == Biome::RIVER->m_biomeId) {
                if (parentArea[m] == Biome::ICE_PLAINS->m_biomeId) {
                    area[m] = Biome::FROZEN_RIVER->m_biomeId;
                } else if (parentArea[m] != Biome::MUSHROOM_ISLAND->m_biomeId
                           && parentArea[m] != Biome::MUSHROOM_ISLAND_SHORE->m_biomeId) {
                    area[m] = secondParentArea[m] & 255;
                } else {
                    area[m] = Biome::MUSHROOM_ISLAND->m_biomeId;
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
    m_parent1->init(l);
    m_secondParent->init(l);
    Layer::init(l);
}
