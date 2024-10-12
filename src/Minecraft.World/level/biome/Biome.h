#pragma once

#include <string>
#include <vector>

#include "Minecraft.World/level/material/MaterialColor.h"
#include "Minecraft.World/phys/Vec3.h"

class Random;
class Block;
class BlockPos;
class Level;
class ChunkPrimer;
class MobCategory;
class BiomeDecorator;
class Feature;
class PerlinSimplexNoise;

// TODO: Move this
class WeightedRandomItem {
public:
    virtual ~WeightedRandomItem();
};

class Biome {
public:
    static Biome* BIOMES[256];

    static Biome* OCEAN;
    static Biome* PLAINS;
    static Biome* DESERT;
    static Biome* MOUNTAINS;
    static Biome* FOREST;
    static Biome* TAIGA;
    static Biome* SWAMP;
    static Biome* RIVER;
    static Biome* THE_END;
    static Biome* FROZEN_OCEAN;
    static Biome* FROZEN_RIVER;
    static Biome* SNOWY_TUNDRA;
    static Biome* SNOWY_MOUNTAINS;
    static Biome* MUSHROOM_FIELD_SHORE;
    static Biome* BEACH;
    static Biome* DESERT_HILLS;
    static Biome* WOODED_HILLS;
    static Biome* TAIGA_HILLS;
    static Biome* MOUNTAIN_EDGE;
    static Biome* JUNGLE;
    static Biome* JUNGLE_HILLS;
    static Biome* JUNGLE_EDGE;
    static Biome* STONE_SHORE;
    static Biome* SNOWY_BEACH;
    static Biome* BIRCH_FOREST;
    static Biome* BIRCH_FOREST_HILLS;
    static Biome* DARK_FOREST;
    static Biome* SNOWY_TAIGA;
    static Biome* SNOWY_TAIGA_HILLS;
    static Biome* GIANT_TREE_TAIGA;
    static Biome* GIANT_TREE_TAIGA_HILLS;
    static Biome* WOODED_MOUNTAINS;
    static Biome* SAVANNA;
    static Biome* SAVANNA_PLATEAU;
    static Biome* BADLANDS;
    static Biome* WOODED_BADLANDS_PLATEAU;
    static Biome* BADLANDS_PLATEAU;
    static Biome* THE_VOID;
    static Biome* SUNFLOWER_PLAINS;
    static Biome* DESERT_LAKES;
    static Biome* GRAVELLY_MOUNTAINS;
    static Biome* FLOWER_FOREST;
    static Biome* TAIGA_MOUNTAINS;
    static Biome* SWAMP_HILLS;
    static Biome* ICE_SPIKES;
    static Biome* MODIFIED_JUNGLE;
    static Biome* MODIFIED_JUNGLE_EDGE;
    static Biome* TALL_BIRCH_FOREST;
    static Biome* TALL_BIRCH_HILLS;
    static Biome* DARK_FOREST_HILLS;
    static Biome* SNOWY_TAIGA_MOUNTAINS;
    static Biome* GIANT_SPRUCE_TAIGA;
    static Biome* GIANT_SPRUCE_TAIGA_HILLS;
    static Biome* MODIFIED_GRAVELLY_MOUNTAINS;
    static Biome* SHATTERED_SAVANNA;
    static Biome* SHATTERED_SAVANNA_PLATEAU;
    static Biome* ERODED_BADLANDS;
    static Biome* MODIFIED_WOODED_BADLANDS_PLATEAU;
    static Biome* MODIFIED_BADLANDS_PLATEAU;

    static PerlinSimplexNoise* TEMPERATURE_NOISE;

    enum EBiomeIDs : unsigned int {
        LIMIT = 256,
    };

    enum BaseClass {
        _BEACH = 0,
        _DESERT = 1,
        _EXTREME_HILLS = 2,
        _FOREST = 3,
        _HELL = 4,
        _ICE = 5,
        _JUNGLE = 6,
        _MESA = 7,
        _MUSHROOM_ISLAND = 8,
        _OCEAN = 10,
        _PLAINS = 11,
        _RIVER = 13,
        _SAVANNA = 14,
        _STONE_BEACH = 15,
        _SWAMP = 16,
        _TAIGA = 17,
        _THE_END = 18,
        _VOID = 19
    };

    class BiomeProperties {
    public:
        BiomeProperties(std::wstring const&);
        void depth(float);
        void downfall(float);
        void dry(void);
        BiomeProperties* mutated(std::wstring const&);
        void scale(float);
        void snow(void);
        void temperature(float);
        void waterColor(int);

    private:
        std::wstring mBiomeName;
        float mDepth = 0.1f;
        float mScale = 0.2f;
        float mTemperature = 0.5f;
        float mDownfall = 0.5f;
        int mWaterColor = 0xFFFFFF;
        bool mIsSnow = false;
        bool mIsNotDry = true;
        std::wstring mMutatedBiomeName;
    };

    class MobSpawnerData {
    public:
        virtual ~MobSpawnerData();
    };

    Biome(Biome::EBiomeIDs, Biome::BiomeProperties*);
    static Biome** getBiomes();
    static Biome* getBiome(int);
    static Biome* getBiome(int, Biome*);

    virtual ~Biome();
    virtual Feature* getTreeFeature(Random&);
    virtual void getGrassFeature(Random&);
    virtual Block* getRandomFlower(Random&, const BlockPos*);
    virtual unsigned int getSkyColor(float);
    virtual bool hasSnow();
    virtual bool hasRain();
    virtual bool isHumid();
    virtual float getCreatureProbability();
    virtual float getTemperature(const BlockPos*);
    virtual void decorate(Level*, Random&, const BlockPos*);
    virtual unsigned int getGrassColor(const BlockPos*);
    virtual unsigned int getFoliageColor(const BlockPos*);
    virtual void setGrassColor(const BlockPos*, unsigned int);
    virtual void setFoliageColor(const BlockPos*, unsigned int);
    virtual void buildSurfaceAt(Level*, Random&, ChunkPrimer*, int, int, double);
    virtual void buildSurfaceAtDefault(Level*, Random&, ChunkPrimer*, int, int, double);
    virtual int getBaseClass() = 0;
    virtual int getTemperatureCategory();
    virtual bool isAlwaysValidSpawn();
    virtual void getWaterColor();
    virtual Vec3 getFogColor(float, float) const;
    virtual bool isFoggy();
    virtual bool isNatural();

    bool isSnowCovered();

    void setNameAndDescription(int, int);
    void setPreviewColor(eMinecraftColour);
    void setWaterSkyColor(eMinecraftColour, eMinecraftColour);

    void getMobs(MobCategory*);

    std::wstring getName(bool);
    std::wstring getDescription();

    float getTemperature();
    float getDownfall();

    int mNameId;
    int mDescriptionId;
    float mDepth;
    float mScale;
    float mTemperature;
    float mDownfall;
    bool mIsSnow;
    bool mIsDry;
    void* qword_28;
    void* qword_30;
    void* qword_38;
    void* qword_40;
    void* qword_48;
    void* qword_50;
    int mGrassId;
    int field_5C;
    int mDirtId;
    BiomeDecorator* mBiomeDecorator;
    int dword_70;
    std::vector<void*> field_78;
    std::vector<void*> field_90;
    std::vector<void*> field_a8;
    std::vector<void*> field_c0;
    std::vector<void*> field_d8;
    std::vector<void*> field_f0;
    std::vector<void*> field_108;
    std::vector<void*> field_120;
    eMinecraftColour mWaterColor;
    eMinecraftColour mSkyColor;
    eMinecraftColour mPreviewColor;
};
