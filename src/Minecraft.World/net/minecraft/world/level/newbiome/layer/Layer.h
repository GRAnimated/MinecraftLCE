#pragma once

#include "net/minecraft/world/ArrayWithLength.h"
#include "net/minecraft/world/level/biome/BiomeSource.h"
#include <memory>

class LevelType;
class SuperflatConfig;
class LevelData;

class Layer {
public:
    static arrayWithLength<std::shared_ptr<Layer>>
    getDefaultLayers(long long seed, LevelType* levelType, SuperflatConfig* superflatConfig,
                     LevelData* levelData, BiomeSource::LayerOverrideSettings* layerOverrideSettings);
    Layer(long long seed);

    static bool isSame(int biomeIdA, int biomeIdB);
    static bool isOcean(int biomeId);

    int nextRandom(int i);
    int random(int i, int j, int k, int l);
    int random(int i, int j);

    virtual ~Layer();
    virtual void init(long long l);
    virtual void initRandom(long long l, long long m);
    virtual arrayWithLength<int> getArea(int x, int y, int width, int height) = 0;
    virtual int modeOrRandom(int i, int j, int k, int l);

    long long mMixedSeed;
    std::shared_ptr<Layer> mParent;
    long long mRandom;
    long long mSeed;
};
