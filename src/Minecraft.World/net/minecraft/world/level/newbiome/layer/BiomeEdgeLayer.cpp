#include "net/minecraft/world/level/newbiome/layer/BiomeEdgeLayer.h"

#include "NX/Platform.h"
#include "net/minecraft/world/level/biome/Biome.h"
#include "net/minecraft/world/level/newbiome/layer/IntCache.h"

BiomeEdgeLayer::BiomeEdgeLayer(long long seed, std::shared_ptr<Layer> parent) : Layer(seed) {
    m_parent = parent;
}

// NON_MATCHING
arrayWithLength<int> BiomeEdgeLayer::getArea(int x, int y, int width, int height) {
    arrayWithLength<int> parentArea = m_parent->getArea(x - 1, y - 1, width + 2, height + 2);
    PIXBeginNamedEvent(0.0, "BiomeEdgeLayer::getArea");
    arrayWithLength<int> area = IntCache::allocate(width * height);

    for (int m = 0; m < height; m++) {
        for (int n = 0; n < width; n++) {
            initRandom(n + x, m + y);
            int o = parentArea[n + 1 + (m + 1) * (width + 2)];
            if (!checkEdge(parentArea, area, n, m, width, o, Biome::EXTREME_HILLS->m_biomeId,
                           Biome::EXTREME_HILLS_EDGE->m_biomeId)
                && !checkEdgeStrict(parentArea, area, n, m, height, o, Biome::MESA_PLATEAU_F->m_biomeId,
                                    Biome::MESA->m_biomeId)
                && !checkEdgeStrict(parentArea, area, n, m, height, o, Biome::MESA_PLATEAU->m_biomeId,
                                    Biome::MESA->m_biomeId)
                && !checkEdgeStrict(parentArea, area, n, m, height, o, Biome::MEGA_TAIGA->m_biomeId,
                                    Biome::TAIGA->m_biomeId)) {
                if (o == Biome::DESERT->m_biomeId) {
                    int p = parentArea[n + 1 + (m + 1 - 1) * (width + 2)];
                    int q = parentArea[n + 1 + 1 + (m + 1) * (width + 2)];
                    int r = parentArea[n + 1 - 1 + (m + 1) * (width + 2)];
                    int s = parentArea[n + 1 + (m + 1 + 1) * (width + 2)];
                    if (p != Biome::ICE_PLAINS->m_biomeId && q != Biome::ICE_PLAINS->m_biomeId
                        && r != Biome::ICE_PLAINS->m_biomeId && s != Biome::ICE_PLAINS->m_biomeId) {
                        area[n + m * width] = o;
                    } else {
                        area[n + m * width] = Biome::EXTREME_HILLS_PLUS->m_biomeId;
                    }
                } else if (o == Biome::SWAMP->m_biomeId) {
                    int p = parentArea[n + 1 + (m + 1 - 1) * (width + 2)];
                    int q = parentArea[n + 1 + 1 + (m + 1) * (width + 2)];
                    int r = parentArea[n + 1 - 1 + (m + 1) * (width + 2)];
                    int s = parentArea[n + 1 + (m + 1 + 1) * (width + 2)];
                    if (p != Biome::DESERT->m_biomeId && q != Biome::DESERT->m_biomeId
                        && r != Biome::DESERT->m_biomeId && s != Biome::DESERT->m_biomeId
                        && p != Biome::COLD_TAIGA->m_biomeId && q != Biome::COLD_TAIGA->m_biomeId
                        && r != Biome::COLD_TAIGA->m_biomeId && s != Biome::COLD_TAIGA->m_biomeId
                        && p != Biome::ICE_PLAINS->m_biomeId && q != Biome::ICE_PLAINS->m_biomeId
                        && r != Biome::ICE_PLAINS->m_biomeId && s != Biome::ICE_PLAINS->m_biomeId) {
                        if (p != Biome::JUNGLE->m_biomeId && s != Biome::JUNGLE->m_biomeId
                            && q != Biome::JUNGLE->m_biomeId && r != Biome::JUNGLE->m_biomeId) {
                            area[n + m * width] = o;
                        } else {
                            area[n + m * width] = Biome::JUNGLE_EDGE->m_biomeId;
                        }
                    } else {
                        area[n + m * width] = Biome::PLAINS->m_biomeId;
                    }
                } else {
                    area[n + m * width] = o;
                }
            }
        }
    }

    PIXEndNamedEvent();
    return area;
}

bool BiomeEdgeLayer::checkEdge(arrayWithLength<int> array0, arrayWithLength<int> array1, int i, int j, int k,
                               int l, int m, int n) {
    if (!isSame(l, m)) {
        return false;
    } else {
        int o = array0[i + 1 + (j + 1 - 1) * (k + 2)];
        int p = array0[i + 1 + 1 + (j + 1) * (k + 2)];
        int q = array0[i + 1 - 1 + (j + 1) * (k + 2)];
        int r = array0[i + 1 + (j + 1 + 1) * (k + 2)];
        if (isValidTemperatureEdge(o, m) && isValidTemperatureEdge(p, m) && isValidTemperatureEdge(q, m)
            && isValidTemperatureEdge(r, m)) {
            array1[i + j * k] = l;
            return true;
        }

        array1[i + j * k] = n;
        return true;
    }
}

bool BiomeEdgeLayer::checkEdgeStrict(arrayWithLength<int> array0, arrayWithLength<int> array1, int i, int j,
                                     int k, int l, int m, int n) {
    if (l != m) {
        return false;
    } else {
        int o = array0[i + 1 + (j + 1 - 1) * (k + 2)];
        int p = array0[i + 1 + 1 + (j + 1) * (k + 2)];
        int q = array0[i + 1 - 1 + (j + 1) * (k + 2)];
        int r = array0[i + 1 + (j + 1 + 1) * (k + 2)];
        if (isSame(o, m) && isSame(p, m) && isSame(q, m) && isSame(r, m)) {
            array1[i + j * k] = l;
            return true;
        }

        array1[i + j * k] = n;
        return true;
    }
}

bool BiomeEdgeLayer::isValidTemperatureEdge(int biomeId0, int biomeId1) {
    if (isSame(biomeId0, biomeId1)) {
        return true;
    } else {
        Biome* biome0 = Biome::getBiome(biomeId0);
        Biome* biome1 = Biome::getBiome(biomeId1);
        if (biome0 != nullptr && biome1 != nullptr) {
            int temperature0 = biome0->getTemperatureCategory();
            int temperature1 = biome1->getTemperatureCategory();
            return temperature0 == temperature1 || temperature0 == 2 || temperature1 == 2;
        } else {
            return false;
        }
    }
}
