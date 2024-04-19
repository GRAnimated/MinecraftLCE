#pragma once

class LevelType;
class SuperflatConfig;
class LevelData;
class BiomeSource {
public:
    class LayerOverrideSettings;
};

class Layer {
public:
    static void getDefaultLayers(long long, LevelType*, SuperflatConfig*, LevelData*, BiomeSource::LayerOverrideSettings*);

    Layer(long long);
    ~Layer();
    virtual void modeOrRandom(int, int, int, int);
    virtual void init(long long);
    virtual void initRandom(long long, long long);

    long long mixedSeed;
    long long qword_10;
    long long qword_18;
    long long random;
    long long seed;
};