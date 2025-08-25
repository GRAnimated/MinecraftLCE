#include "net/minecraft/world/level/newbiome/layer/Layer.h"

#include "net/minecraft/world/level/biome/Biome.h"
#include "net/minecraft/world/level/levelgen/CustomizableSourceSettings.h"
#include "net/minecraft/world/level/newbiome/layer/AddDeepOceanLayer.h"
#include "net/minecraft/world/level/newbiome/layer/AddEdgeLayer.h"
#include "net/minecraft/world/level/newbiome/layer/AddIslandLayer.h"
#include "net/minecraft/world/level/newbiome/layer/AddMushroomIslandLayer.h"
#include "net/minecraft/world/level/newbiome/layer/AddSnowLayer.h"
#include "net/minecraft/world/level/newbiome/layer/BiomeCacheLayer.h"
#include "net/minecraft/world/level/newbiome/layer/BiomeEdgeLayer.h"
#include "net/minecraft/world/level/newbiome/layer/BiomeInitLayer.h"
#include "net/minecraft/world/level/newbiome/layer/FuzzyZoomLayer.h"
#include "net/minecraft/world/level/newbiome/layer/GrowMushroomIslandLayer.h"
#include "net/minecraft/world/level/newbiome/layer/IslandLayer.h"
#include "net/minecraft/world/level/newbiome/layer/RareBiomeSpotLayer.h"
#include "net/minecraft/world/level/newbiome/layer/RegionHillsLayer.h"
#include "net/minecraft/world/level/newbiome/layer/RemoveTooMuchOceanLayer.h"
#include "net/minecraft/world/level/newbiome/layer/RiverInitLayer.h"
#include "net/minecraft/world/level/newbiome/layer/RiverLayer.h"
#include "net/minecraft/world/level/newbiome/layer/RiverMixerLayer.h"
#include "net/minecraft/world/level/newbiome/layer/ShoreLayer.h"
#include "net/minecraft/world/level/newbiome/layer/SmoothLayer.h"
#include "net/minecraft/world/level/newbiome/layer/VoronoiZoom.h"
#include "net/minecraft/world/level/storage/LevelData.h"

Layer::Layer(long long seed) {
    this->mParent = nullptr;

    long long n = seed;
    for (int i = 0; i < 3; i++) {
        n *= n * 6364136223846793005LL + 1442695040888963407LL;
        n += seed;
    }

    this->mMixedSeed = 0;
    this->mSeed = n;
}

Layer::~Layer() {}

// NON_MATCHING | Score: 995 (Lower is better)
arrayWithLength<std::shared_ptr<Layer>>
Layer::getDefaultLayers(long long seed, LevelType* levelType, SuperflatConfig* superflatConfig,
                        LevelData* levelData, BiomeSource::LayerOverrideSettings* layerOverrideSettings) {
    int useBiomeScale = 0;
    int centerXChunk;
    int centerZChunk;
    if (layerOverrideSettings != nullptr) {
        useBiomeScale = layerOverrideSettings->GetBiomeScale();
        centerXChunk = layerOverrideSettings->GetCentreXChunk();
        centerZChunk = layerOverrideSettings->GetCentreZChunk();
    } else if (levelData != nullptr) {
        useBiomeScale = levelData->getBiomeScale();
        centerXChunk = levelData->getBiomeCentreXChunk();
        centerZChunk = levelData->getBiomeCentreZChunk();
    }

    std::shared_ptr<Layer> layer = std::shared_ptr<Layer>(new IslandLayer(1));
    layer = std::shared_ptr<Layer>(new FuzzyZoomLayer(2000, layer));
    layer = std::shared_ptr<Layer>(new AddIslandLayer(1, layer));
    layer = std::shared_ptr<Layer>(new ZoomLayer(2001, layer));
    layer = std::shared_ptr<Layer>(new AddIslandLayer(2, layer));
    layer = std::shared_ptr<Layer>(new AddIslandLayer(50, layer));
    layer = std::shared_ptr<Layer>(new AddIslandLayer(70, layer));
    layer = std::shared_ptr<Layer>(new RemoveTooMuchOceanLayer(2, layer));
    layer = std::shared_ptr<Layer>(new AddSnowLayer(2, layer));
    layer = std::shared_ptr<Layer>(new AddIslandLayer(3, layer));
    layer = std::shared_ptr<Layer>(new AddEdgeLayer(2, layer, AddEdgeLayer::Mode::COOL_WARM));
    layer = std::shared_ptr<Layer>(new AddEdgeLayer(2, layer, AddEdgeLayer::Mode::HEAT_ICE));
    layer = std::shared_ptr<Layer>(new AddEdgeLayer(3, layer, AddEdgeLayer::Mode::SPECIAL));
    layer = std::shared_ptr<Layer>(new ZoomLayer(2002, layer));
    layer = std::shared_ptr<Layer>(new ZoomLayer(2003, layer));
    layer = std::shared_ptr<Layer>(new AddIslandLayer(4, layer));

    if (useBiomeScale) {
        layer = std::shared_ptr<Layer>(new AddMushroomIslandLayer(5, layer));
    }

    layer = std::shared_ptr<Layer>(new AddDeepOceanLayer(4, layer));
    layer = ZoomLayer::zoom(1000, layer, 0);

    int biomeScale = 4;
    int riverScale = biomeScale;
    CustomizableSourceSettings* settings = nullptr;
    if (superflatConfig != nullptr) {
        if (levelType == LevelType::CUSTOMIZED) {
            CustomizableSourceSettings::Builder* builder
                = CustomizableSourceSettings::Builder::fromString(superflatConfig);
            settings = builder->build();
            biomeScale = settings->biomeSize;
            riverScale = settings->riverSize;
            if (builder != nullptr) {
                delete builder;
            }
        }
    }

    if (levelType == LevelType::LARGE_BIOMES) {
        biomeScale = 6;
    }

    std::shared_ptr<Layer> river = layer;
    river = ZoomLayer::zoom(1000, river, 0);
    river = std::shared_ptr<Layer>(new RiverInitLayer(100, river));

    std::shared_ptr<Layer> biome = layer;
    biome = std::shared_ptr<Layer>(new BiomeInitLayer(200, layer, levelType, superflatConfig));
    biome = ZoomLayer::zoom(1000, biome, useBiomeScale);
    biome = std::shared_ptr<Layer>(new BiomeEdgeLayer(1000, biome));

    std::shared_ptr<Layer> zoom = river;
    zoom = ZoomLayer::zoom(1000, zoom, 2);
    biome = std::shared_ptr<Layer>(new RegionHillsLayer(1000, biome, zoom));
    river = ZoomLayer::zoom(1000, river, 2);
    river = ZoomLayer::zoom(1000, river, riverScale);
    river = std::shared_ptr<Layer>(new RiverLayer(1, river));
    river = std::shared_ptr<Layer>(new SmoothLayer(1000, river));
    biome = std::shared_ptr<Layer>(new RareBiomeSpotLayer(1001, biome));

    for (int k = 0; k < biomeScale; k++) {
        biome = std::shared_ptr<Layer>(new ZoomLayer(k + 1000, biome));

        if (k == 0) {
            biome = std::shared_ptr<Layer>(new AddIslandLayer(3, biome));

            if (!useBiomeScale) {
                biome = std::shared_ptr<Layer>(new AddMushroomIslandLayer(5, biome));
            }
        }

        if (k == 1 || biomeScale == 1) {
            if (!useBiomeScale) {
                biome = std::shared_ptr<Layer>(new GrowMushroomIslandLayer(5, biome));
            }

            biome = std::shared_ptr<Layer>(new ShoreLayer(1000, biome));
        }
    }

    biome = std::shared_ptr<Layer>(new SmoothLayer(1000, biome));
    biome = std::shared_ptr<Layer>(new RiverMixerLayer(100, biome, river));

    if (levelData != nullptr) {
        biome = std::shared_ptr<Layer>(
            new BiomeCacheLayer(1, biome, levelData->getXZSize(), useBiomeScale, centerXChunk, centerZChunk));
    }

    std::shared_ptr<Layer> biome2 = biome;

    std::shared_ptr<Layer> voronoi = std::shared_ptr<Layer>(new VoronoiZoom(10, biome));
    biome->init(seed);
    voronoi->init(seed);

    arrayWithLength<std::shared_ptr<Layer>> array(3, true);
    array[0] = biome;
    array[1] = voronoi;
    array[2] = biome2;

    return array;
}

void Layer::init(long long l) {
    mMixedSeed = l;
    if (mParent != nullptr) {
        mParent->init(l);
    }

    mMixedSeed *= mMixedSeed * 6364136223846793005L + 1442695040888963407L;
    mMixedSeed += mSeed;
    mMixedSeed *= mMixedSeed * 6364136223846793005L + 1442695040888963407L;
    mMixedSeed += mSeed;
    mMixedSeed *= mMixedSeed * 6364136223846793005L + 1442695040888963407L;
    mMixedSeed += mSeed;
}

void Layer::initRandom(long long l, long long m) {
    mRandom = mMixedSeed;
    mRandom *= mRandom * 6364136223846793005L + 1442695040888963407L;
    mRandom += l;
    mRandom *= mRandom * 6364136223846793005L + 1442695040888963407L;
    mRandom += m;
    mRandom *= mRandom * 6364136223846793005L + 1442695040888963407L;
    mRandom += l;
    mRandom *= mRandom * 6364136223846793005L + 1442695040888963407L;
    mRandom += m;
}

int Layer::nextRandom(int i) {
    int j = (int)((mRandom >> 24) % i);
    if (j < 0) {
        j += i;
    }

    mRandom *= mRandom * 6364136223846793005L + 1442695040888963407L;
    mRandom += mMixedSeed;
    return j;
}

bool Layer::isSame(int biomeIdA, int biomeIdB) {
    if (biomeIdA == biomeIdB) {
        return true;
    } else {
        Biome* biome = Biome::getBiome(biomeIdA);
        Biome* biome2 = Biome::getBiome(biomeIdB);
        if (biome != nullptr && biome2 != nullptr) {
            if (biome != Biome::MESA_PLATEAU_F && biome != Biome::MESA_PLATEAU) {
                return biome == biome2 || biome->getBaseClass() == biome2->getBaseClass();
            } else {
                return biome2 == Biome::MESA_PLATEAU_F || biome2 == Biome::MESA_PLATEAU;
            }
        } else {
            return false;
        }
    }
}

bool Layer::isOcean(int biomeId) {
    if (Biome::OCEAN->mBiomeID == biomeId) {
        return true;
    } else if (Biome::DEEP_OCEAN->mBiomeID == biomeId) {
        return true;
    }

    return Biome::FROZEN_OCEAN->mBiomeID == biomeId;
}

int Layer::random(int i, int j, int k, int l) {
    int random = nextRandom(4);

    int ret = (random != 2 ? i : k);
    if (random == 3)
        ret = l;
    if (random == 1)
        ret = j;
    return ret;
}

int Layer::random(int i, int j) {
    if (nextRandom(2)) {
        return j;
    }

    return i;
}

int Layer::modeOrRandom(int i, int j, int k, int l) {
    if (j == k && k == l) {
        return j;
    } else if (i == j && i == k) {
        return i;
    } else if (i == j && i == l) {
        return i;
    } else if (i == k && i == l) {
        return i;
    } else if (i == j && k != l) {
        return i;
    } else if (i == k && j != l) {
        return i;
    } else if (i == l && j != k) {
        return i;
    } else if (j == k && i != l) {
        return j;
    } else if (j == l && i != k) {
        return j;
    } else {
        return k == l && i != j ? k : random(i, j, k, l);
    }
}
