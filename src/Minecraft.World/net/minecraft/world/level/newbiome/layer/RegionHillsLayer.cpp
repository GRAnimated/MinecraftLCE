#include "RegionHillsLayer.h"

#include "NX/Platform.h"
#include "net/minecraft/world/level/biome/Biome.h"
#include "net/minecraft/world/level/newbiome/layer/IntCache.h"

RegionHillsLayer::RegionHillsLayer(long long seed, std::shared_ptr<Layer> parent,
                                   std::shared_ptr<Layer> secondParent)
    : Layer(seed) {
    m_parent = parent;
    m_secondParent = secondParent;
}

// NON_MATCHING | Score: 9654 (Lower is better)
// 4J did some goofy shit with this one...
arrayWithLength<int> RegionHillsLayer::getArea(int x, int y, int width, int height) {
    arrayWithLength<int> parentArea = m_parent->getArea(x - 1, y - 1, width + 2, height + 2);
    arrayWithLength<int> secondParentArea = m_secondParent->getArea(x - 1, y - 1, width + 2, height + 2);
    PIXBeginNamedEvent(0.0, "RegionHillsLayer::getArea");
    arrayWithLength<int> area = IntCache::allocate(width * height);

    for (int m = 0; m < height; m++) {
        for (int n = 0; n < width; n++) {
            initRandom(n + x, m + y);
            int o = parentArea[n + 1 + (m + 1) * (width + 2)];
            int p = secondParentArea[n + 1 + (m + 1) * (width + 2)];
            bool bl = (p - 2) % 29 == 0;

            Biome* biome0 = Biome::getBiome(o + 128);
            if (o != 0 && p >= 2 && o <= 127 && (p - 2) % 29 == 1) {
                Biome* biome = biome0;
                area[n + m * width] = biome == nullptr ? o : biome->m_biomeId + 128;
            } else if (nextRandom(3) != 0 && !bl) {
                area[n + m * width] = o;
            } else {
                Biome* biome = biome0;
                if (o == Biome::DESERT->m_biomeId) {
                    biome = Biome::DESERT_HILLS;
                } else if (o == Biome::FOREST->m_biomeId) {
                    biome = Biome::FOREST_HILLS;
                } else if (o == Biome::BIRCH_FOREST->m_biomeId) {
                    biome = Biome::BIRCH_FOREST_HILLS;
                } else if (o == Biome::ROOFED_FOREST->m_biomeId) {
                    biome = Biome::PLAINS;
                } else if (o == Biome::TAIGA->m_biomeId) {
                    biome = Biome::TAIGA_HILLS;
                } else if (o == Biome::MEGA_TAIGA->m_biomeId) {
                    biome = Biome::MEGA_TAIGA_HILLS;
                } else if (o == Biome::COLD_TAIGA->m_biomeId) {
                    biome = Biome::COLD_TAIGA_HILLS;
                } else if (o == Biome::PLAINS->m_biomeId) {
                    if (nextRandom(3) == 0) {
                        biome = Biome::FOREST_HILLS;
                    } else {
                        biome = Biome::FOREST;
                    }
                } else if (o == Biome::ICE_PLAINS->m_biomeId) {
                    biome = Biome::ICE_MOUNTAINS;
                } else if (o == Biome::JUNGLE->m_biomeId) {
                    biome = Biome::JUNGLE_HILLS;
                } else if (o == Biome::OCEAN->m_biomeId) {
                    biome = Biome::DEEP_OCEAN;
                } else if (o == Biome::EXTREME_HILLS->m_biomeId) {
                    biome = Biome::EXTREME_HILLS_PLUS;
                } else if (o == Biome::SAVANNA->m_biomeId) {
                    biome = Biome::SAVANNA_PLATEAU;
                } else if (isSame(o, Biome::MESA_PLATEAU_F->m_biomeId)) {
                    biome = Biome::MESA;
                } else if (o == Biome::DEEP_OCEAN->m_biomeId && nextRandom(3) == 0) {
                    int q = nextRandom(2);
                    if (q == 0) {
                        biome = Biome::PLAINS;
                    } else {
                        biome = Biome::FOREST;
                    }
                }

                int q = biome->m_biomeId;
                if (bl && q != o) {
                    Biome* biome3 = biome;
                    q = biome3 == nullptr ? o : biome3->m_biomeId + 128;
                }

                if (q == o) {
                    area[n + m * width] = o;
                } else {
                    int r = parentArea[n + 1 + (m + 0) * (width + 2)];
                    int s = parentArea[n + 2 + (m + 1) * (width + 2)];
                    int t = parentArea[n + 0 + (m + 1) * (width + 2)];
                    int u = parentArea[n + 1 + (m + 2) * (width + 2)];
                    int v = 0;
                    if (isSame(r, o)) {
                        ++v;
                    }

                    if (isSame(s, o)) {
                        ++v;
                    }

                    if (isSame(t, o)) {
                        ++v;
                    }

                    if (isSame(u, o)) {
                        ++v;
                    }

                    if (v >= 3) {
                        area[n + m * width] = q;
                    } else {
                        area[n + m * width] = o;
                    }
                }
            }
        }
    }

    PIXEndNamedEvent();
    return area;
}
