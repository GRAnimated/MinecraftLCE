#pragma once

#include <memory>

class LevelType;
class SuperflatConfig;
class LevelData;
class BiomeSource {
public:
    class LayerOverrideSettings;
};

class Layer {
public:
    static void getDefaultLayers(long long, LevelType*, SuperflatConfig*, LevelData*,
                                 BiomeSource::LayerOverrideSettings*);

    Layer(long long seed);
    ~Layer();
    virtual void modeOrRandom(int, int, int, int);
    virtual void init(long long);
    virtual void initRandom(long long, long long);

    long long mMixedSeed = 0;
    std::shared_ptr<void> field_10;
    long long mRandom = 0;
    long long mSeed = 0;
};