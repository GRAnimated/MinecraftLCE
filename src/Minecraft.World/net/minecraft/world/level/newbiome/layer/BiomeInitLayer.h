#pragma once

#include "net/minecraft/world/ArrayWithLength.h"
#include "net/minecraft/world/level/newbiome/layer/Layer.h"

class CustomizableSourceSettings;
class Biome;
class SuperflatConfig;

class BiomeInitLayer : public Layer {
public:
    BiomeInitLayer(long long seed, std::shared_ptr<Layer> parent, LevelType* levelType,
                   SuperflatConfig* superflatConfig);

    arrayWithLength<int> getArea(int x, int y, int width, int height) override;

    arrayWithLength<Biome*> mWarmBiomes;
    arrayWithLength<Biome*> mMediumBiomes;
    arrayWithLength<Biome*> mColdBiomes;
    arrayWithLength<Biome*> mIceBiomes;
    CustomizableSourceSettings* mSettings;
};
