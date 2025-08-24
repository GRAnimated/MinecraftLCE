#include "net/minecraft/world/level/newbiome/layer/BiomeInitLayer.h"

#include "NX/Platform.h"
#include "net/minecraft/world/level/LevelType.h"
#include "net/minecraft/world/level/biome/Biome.h"
#include "net/minecraft/world/level/levelgen/CustomizableSourceSettings.h"
#include "net/minecraft/world/level/newbiome/layer/IntCache.h"

BiomeInitLayer::BiomeInitLayer(long long seed, std::shared_ptr<Layer> childLayer, LevelType* levelType,
                               SuperflatConfig* superflatConfig)
    : Layer(seed) {
    mChildLayer = childLayer;
    if (levelType == LevelType::NORMAL_1_1) {
        mWarmBiomes = {6, true};
        mWarmBiomes[0] = Biome::DESERT;
        mWarmBiomes[1] = Biome::FOREST;
        mWarmBiomes[2] = Biome::EXTREME_HILLS;
        mWarmBiomes[3] = Biome::SWAMP;
        mWarmBiomes[4] = Biome::PLAINS;
        mWarmBiomes[5] = Biome::TAIGA;
    } else {
        mWarmBiomes = {6, true};
        mWarmBiomes[0] = Biome::DESERT;
        mWarmBiomes[1] = Biome::DESERT;
        mWarmBiomes[2] = Biome::DESERT;
        mWarmBiomes[3] = Biome::SAVANNA;
        mWarmBiomes[4] = Biome::SAVANNA;
        mWarmBiomes[5] = Biome::PLAINS;
    }

    mMediumBiomes = {6, true};
    mMediumBiomes[0] = Biome::FOREST;
    mMediumBiomes[1] = Biome::ROOFED_FOREST;
    mMediumBiomes[2] = Biome::EXTREME_HILLS;
    mMediumBiomes[3] = Biome::PLAINS;
    mMediumBiomes[4] = Biome::BIRCH_FOREST;
    mMediumBiomes[5] = Biome::SWAMP;

    mColdBiomes = {4, true};
    mColdBiomes[0] = Biome::FOREST;
    mColdBiomes[1] = Biome::EXTREME_HILLS;
    mColdBiomes[2] = Biome::TAIGA;
    mColdBiomes[3] = Biome::PLAINS;

    mIceBiomes = {4, true};
    mIceBiomes[0] = Biome::ICE_PLAINS;
    mIceBiomes[1] = Biome::ICE_PLAINS;
    mIceBiomes[2] = Biome::ICE_PLAINS;
    mIceBiomes[3] = Biome::COLD_TAIGA;

    CustomizableSourceSettings* settings = nullptr;
    if (levelType != LevelType::NORMAL_1_1 && levelType == LevelType::CUSTOMIZED) {
        CustomizableSourceSettings::Builder* builder
            = CustomizableSourceSettings::Builder::fromString(superflatConfig);
        settings = builder->build();
    }

    mSettings = settings;
}

arrayWithLength<int> BiomeInitLayer::getArea(int i, int j, int k, int l) {
    arrayWithLength<int> is = mChildLayer->getArea(i, j, k, l);
    PIXBeginNamedEvent(0.0, "BiomeInitLayer::getArea");
    arrayWithLength<int> js = IntCache::allocate(k * l);

    for (int m = 0; m < l; ++m) {
        for (int n = 0; n < k; ++n) {
            initRandom(n + i, m + j);
            int o = is[n + m * k];
            int p = (o & 3840) >> 8;
            o &= -3841;
            if (mSettings != nullptr && mSettings->fixedBiome >= 0) {
                js[n + m * k] = mSettings->fixedBiome;
            } else if (isOcean(o)) {
                js[n + m * k] = o;
            } else if (o == Biome::MUSHROOM_ISLAND->mBiomeID) {
                js[n + m * k] = o;
            } else if (o == 1) {
                if (p > 0) {
                    if (nextRandom(3) == 0) {
                        js[n + m * k] = Biome::MESA_PLATEAU_F->mBiomeID;
                    } else {
                        js[n + m * k] = Biome::MESA_PLATEAU->mBiomeID;
                    }
                } else {
                    js[n + m * k] = mWarmBiomes[nextRandom(mWarmBiomes.length)]->mBiomeID;
                }
            } else if (o == 2) {
                if (p > 0) {
                    js[n + m * k] = Biome::JUNGLE->mBiomeID;
                } else {
                    js[n + m * k] = mMediumBiomes[nextRandom(mMediumBiomes.length)]->mBiomeID;
                }
            } else if (o == 3) {
                if (p > 0) {
                    js[n + m * k] = Biome::MEGA_TAIGA->mBiomeID;
                } else {
                    js[n + m * k] = mColdBiomes[nextRandom(mColdBiomes.length)]->mBiomeID;
                }
            } else if (o == 4) {
                js[n + m * k] = mIceBiomes[nextRandom(mIceBiomes.length)]->mBiomeID;
            } else {
                js[n + m * k] = Biome::MUSHROOM_ISLAND->mBiomeID;
            }
        }
    }

    PIXEndNamedEvent();
    return js;
}
