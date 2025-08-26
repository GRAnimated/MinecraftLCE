#include "net/minecraft/world/level/newbiome/layer/ShoreLayer.h"

#include "NX/Platform.h"
#include "net/minecraft/world/level/biome/Biome.h"
#include "net/minecraft/world/level/biome/MesaBiome.h"
#include "net/minecraft/world/level/newbiome/layer/IntCache.h"

ShoreLayer::ShoreLayer(long long seed, std::shared_ptr<Layer> parent) : Layer(seed) {
    mParent = parent;
}

// NON_MATCHING | Score: 1146 (Lower is better)
void ShoreLayer::replaceIfNeighborOcean(arrayWithLength<int> array0, arrayWithLength<int> array1, int i,
                                        int j, int k, int l, int m) {
    if (isOcean(l)) {
        array1[i + j * k] = l;
    } else {
        int n = array0[i + 1 + (j + 1 - 1) * (k + 2)];
        int o = array0[i + 1 + 1 + (j + 1) * (k + 2)];
        int p = array0[i + 1 - 1 + (j + 1) * (k + 2)];
        int q = array0[i + 1 + (j + 1 + 1) * (k + 2)];
        if (!isOcean(n) && !isOcean(o) && !isOcean(p) && !isOcean(q)) {
            array1[i + j * k] = l;
        } else {
            array1[i + j * k] = m;
        }
    }
}

bool ShoreLayer::isJungleCompatible(int biomeId) {
    if (Biome::getBiome(biomeId) != nullptr && Biome::getBiome(biomeId)->getBaseClass() == Biome::_JUNGLE) {
        return true;
    } else {
        return biomeId == Biome::JUNGLE_EDGE->mBiomeID || biomeId == Biome::JUNGLE->mBiomeID
               || biomeId == Biome::JUNGLE_HILLS->mBiomeID || biomeId == Biome::FOREST->mBiomeID
               || biomeId == Biome::TAIGA->mBiomeID || isOcean(biomeId);
    }
}

bool ShoreLayer::isMesa(int biomeId) {
    return dynamic_cast<MesaBiome*>(Biome::getBiome(biomeId)) != nullptr;
}

// NON_MATCHING | Score: 1945 (Lower is better)
arrayWithLength<int> ShoreLayer::getArea(int x, int y, int width, int height) {
    arrayWithLength<int> parentArea = mParent->getArea(x - 1, y - 1, width + 2, height + 2);
    PIXBeginNamedEvent(0.0, "ShoreLayer::getArea");
    arrayWithLength<int> area = IntCache::allocate(width * height);

    for (int m = 0; m < height; m++) {
        for (int n = 0; n < width; n++) {
            initRandom(n + x, m + y);
            int o = parentArea[n + 1 + (m + 1) * (width + 2)];
            Biome* biome = Biome::getBiome(o);
            if (o == Biome::MUSHROOM_ISLAND->mBiomeID) {
                int p = parentArea[n + 1 + (m + 1 - 1) * (width + 2)];
                int q = parentArea[n + 1 + 1 + (m + 1) * (width + 2)];
                int r = parentArea[n + 1 - 1 + (m + 1) * (width + 2)];
                int s = parentArea[n + 1 + (m + 1 + 1) * (width + 2)];
                if (p != Biome::OCEAN->mBiomeID && q != Biome::OCEAN->mBiomeID && r != Biome::OCEAN->mBiomeID
                    && s != Biome::OCEAN->mBiomeID) {
                    area[n + m * width] = o;
                } else {
                    area[n + m * width] = Biome::MUSHROOM_ISLAND_SHORE->mBiomeID;
                }
            } else if (biome != nullptr && biome->getBaseClass() == Biome::_JUNGLE) {
                int p = parentArea[n + 1 + (m + 1 - 1) * (width + 2)];
                int q = parentArea[n + 1 + 1 + (m + 1) * (width + 2)];
                int r = parentArea[n + 1 - 1 + (m + 1) * (width + 2)];
                int s = parentArea[n + 1 + (m + 1 + 1) * (width + 2)];
                if (isJungleCompatible(p) && isJungleCompatible(q) && isJungleCompatible(r)
                    && isJungleCompatible(s)) {
                    if (!isOcean(p) && !isOcean(q) && !isOcean(r) && !isOcean(s)) {
                        area[n + m * width] = o;
                    } else {
                        area[n + m * width] = Biome::BEACH->mBiomeID;
                    }
                } else {
                    area[n + m * width] = Biome::JUNGLE_EDGE->mBiomeID;
                }
            } else if (o != Biome::EXTREME_HILLS->mBiomeID && o != Biome::EXTREME_HILLS_PLUS->mBiomeID
                       && o != Biome::EXTREME_HILLS_EDGE->mBiomeID) {
                if (biome != nullptr && biome->isSnowCovered()) {
                    replaceIfNeighborOcean(parentArea, area, n, m, width, o, Biome::COLD_BEACH->mBiomeID);
                } else if (o != Biome::MESA->mBiomeID && o != Biome::MESA_PLATEAU_F->mBiomeID) {
                    if (o != Biome::OCEAN->mBiomeID && o != Biome::DEEP_OCEAN->mBiomeID
                        && o != Biome::RIVER->mBiomeID && o != Biome::SWAMP->mBiomeID) {
                        int p = parentArea[n + 1 + (m + 1 - 1) * (width + 2)];
                        int q = parentArea[n + 1 + 1 + (m + 1) * (width + 2)];
                        int r = parentArea[n + 1 - 1 + (m + 1) * (width + 2)];
                        int s = parentArea[n + 1 + (m + 1 + 1) * (width + 2)];
                        if (!isOcean(p) && !isOcean(q) && !isOcean(r) && !isOcean(s)) {
                            area[n + m * width] = o;
                        } else {
                            area[n + m * width] = Biome::BEACH->mBiomeID;
                        }
                    } else {
                        area[n + m * width] = o;
                    }
                } else {
                    int p = parentArea[n + 1 + (m + 1 - 1) * (width + 2)];
                    int q = parentArea[n + 1 + 1 + (m + 1) * (width + 2)];
                    int r = parentArea[n + 1 - 1 + (m + 1) * (width + 2)];
                    int s = parentArea[n + 1 + (m + 1 + 1) * (width + 2)];
                    if (!isOcean(p) && !isOcean(q) && !isOcean(r) && !isOcean(s)) {
                        if (isMesa(p) && isMesa(q) && isMesa(r) && isMesa(s)) {
                            area[n + m * width] = o;
                        } else {
                            area[n + m * width] = Biome::DESERT->mBiomeID;
                        }
                    } else {
                        area[n + m * width] = o;
                    }
                }
            } else {
                replaceIfNeighborOcean(parentArea, area, n, m, width, o, Biome::STONE_BEACH->mBiomeID);
            }
        }
    }

    PIXEndNamedEvent();
    return area;
}
