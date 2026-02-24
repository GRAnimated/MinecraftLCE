#include "net/minecraft/world/level/newbiome/layer/BiomeInitLayer.h"

#include "NX/Platform.h"
#include "net/minecraft/world/level/LevelType.h"
#include "net/minecraft/world/level/biome/Biome.h"
#include "net/minecraft/world/level/levelgen/CustomizableSourceSettings.h"
#include "net/minecraft/world/level/newbiome/layer/IntCache.h"

BiomeInitLayer::BiomeInitLayer(long long seed, std::shared_ptr<Layer> parent, LevelType* levelType,
                               SuperflatConfig* superflatConfig)
    : Layer(seed) {
    m_parent = parent;
    if (levelType == LevelType::NORMAL_1_1) {
        m_warmBiomes = {6, true};
        m_warmBiomes[0] = Biome::DESERT;
        m_warmBiomes[1] = Biome::FOREST;
        m_warmBiomes[2] = Biome::EXTREME_HILLS;
        m_warmBiomes[3] = Biome::SWAMP;
        m_warmBiomes[4] = Biome::PLAINS;
        m_warmBiomes[5] = Biome::TAIGA;
    } else {
        m_warmBiomes = {6, true};
        m_warmBiomes[0] = Biome::DESERT;
        m_warmBiomes[1] = Biome::DESERT;
        m_warmBiomes[2] = Biome::DESERT;
        m_warmBiomes[3] = Biome::SAVANNA;
        m_warmBiomes[4] = Biome::SAVANNA;
        m_warmBiomes[5] = Biome::PLAINS;
    }

    m_mediumBiomes = {6, true};
    m_mediumBiomes[0] = Biome::FOREST;
    m_mediumBiomes[1] = Biome::ROOFED_FOREST;
    m_mediumBiomes[2] = Biome::EXTREME_HILLS;
    m_mediumBiomes[3] = Biome::PLAINS;
    m_mediumBiomes[4] = Biome::BIRCH_FOREST;
    m_mediumBiomes[5] = Biome::SWAMP;

    m_coldBiomes = {4, true};
    m_coldBiomes[0] = Biome::FOREST;
    m_coldBiomes[1] = Biome::EXTREME_HILLS;
    m_coldBiomes[2] = Biome::TAIGA;
    m_coldBiomes[3] = Biome::PLAINS;

    m_iceBiomes = {4, true};
    m_iceBiomes[0] = Biome::ICE_PLAINS;
    m_iceBiomes[1] = Biome::ICE_PLAINS;
    m_iceBiomes[2] = Biome::ICE_PLAINS;
    m_iceBiomes[3] = Biome::COLD_TAIGA;

    CustomizableSourceSettings* settings = nullptr;
    if (levelType != LevelType::NORMAL_1_1 && levelType == LevelType::CUSTOMIZED) {
        CustomizableSourceSettings::Builder* builder
            = CustomizableSourceSettings::Builder::fromString(superflatConfig);
        settings = builder->build();
    }

    m_settings = settings;
}

arrayWithLength<int> BiomeInitLayer::getArea(int x, int y, int width, int height) {
    arrayWithLength<int> parentArea = m_parent->getArea(x, y, width, height);
    PIXBeginNamedEvent(0.0, "BiomeInitLayer::getArea");
    arrayWithLength<int> area = IntCache::allocate(width * height);

    for (int m = 0; m < height; m++) {
        for (int n = 0; n < width; n++) {
            initRandom(n + x, m + y);
            int o = parentArea[n + m * width];
            int p = (o & 3840) >> 8;
            o &= -3841;
            if (m_settings != nullptr && m_settings->m_fixedBiome >= 0) {
                area[n + m * width] = m_settings->m_fixedBiome;
            } else if (isOcean(o)) {
                area[n + m * width] = o;
            } else if (o == Biome::MUSHROOM_ISLAND->m_biomeId) {
                area[n + m * width] = o;
            } else if (o == 1) {
                if (p > 0) {
                    if (nextRandom(3) == 0) {
                        area[n + m * width] = Biome::MESA_PLATEAU_F->m_biomeId;
                    } else {
                        area[n + m * width] = Biome::MESA_PLATEAU->m_biomeId;
                    }
                } else {
                    area[n + m * width] = m_warmBiomes[nextRandom(m_warmBiomes.m_length)]->m_biomeId;
                }
            } else if (o == 2) {
                if (p > 0) {
                    area[n + m * width] = Biome::JUNGLE->m_biomeId;
                } else {
                    area[n + m * width] = m_mediumBiomes[nextRandom(m_mediumBiomes.m_length)]->m_biomeId;
                }
            } else if (o == 3) {
                if (p > 0) {
                    area[n + m * width] = Biome::MEGA_TAIGA->m_biomeId;
                } else {
                    area[n + m * width] = m_coldBiomes[nextRandom(m_coldBiomes.m_length)]->m_biomeId;
                }
            } else if (o == 4) {
                area[n + m * width] = m_iceBiomes[nextRandom(m_iceBiomes.m_length)]->m_biomeId;
            } else {
                area[n + m * width] = Biome::MUSHROOM_ISLAND->m_biomeId;
            }
        }
    }

    PIXEndNamedEvent();
    return area;
}
