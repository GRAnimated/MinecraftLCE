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

    arrayWithLength<Biome*> m_warmBiomes;
    arrayWithLength<Biome*> m_mediumBiomes;
    arrayWithLength<Biome*> m_coldBiomes;
    arrayWithLength<Biome*> m_iceBiomes;
    CustomizableSourceSettings* m_settings;
};
