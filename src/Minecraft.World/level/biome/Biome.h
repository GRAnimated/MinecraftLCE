#pragma once

#include <string>
#include <vector>

#include "Minecraft.World/WeighedRandomItem.h"
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

    enum EBiomeIDs : int {
        BiomeID_OCEAN = 0,
        BiomeID_PLAINS = 1,
        BiomeID_DESERT = 2,
        BiomeID_EXTREME_HILLS = 3,
        BiomeID_FOREST = 4,
        BiomeID_TAIGA = 5,
        BiomeID_SWAMPLAND = 6,
        BiomeID_RIVER = 7,
        BiomeID_HELL = 8,
        BiomeID_THE_END = 9,
        BiomeID_FROZEN_OCEAN = 10,
        BiomeID_FROZEN_RIVER = 11,
        BiomeID_ICE_PLAINS = 12,
        BiomeID_ICE_MOUNTAINS = 13,
        BiomeID_MUSHROOM_ISLAND = 14,
        BiomeID_MUSHROOM_ISLAND_SHORE = 15,
        BiomeID_BEACH = 16,
        BiomeID_DESERT_HILLS = 17,
        BiomeID_FOREST_HILLS = 18,
        BiomeID_TAIGA_HILLS = 19,
        BiomeID_EXTREME_HILLS_EDGE = 20,
        BiomeID_JUNGLE = 21,
        BiomeID_JUNGLE_HILLS = 22,
        BiomeID_JUNGLE_EDGE = 23,
        BiomeID_DEEP_OCEAN = 24,
        BiomeID_STONE_BEACH = 25,
        BiomeID_COLD_BEACH = 26,
        BiomeID_BIRCH_FOREST = 27,
        BiomeID_BIRCH_FOREST_HILLS = 28,
        BiomeID_ROOFED_FOREST = 29,
        BiomeID_COLD_TAIGA = 30,
        BiomeID_COLD_TAIGA_HILLS = 31,
        BiomeID_MEGA_TAIGA = 32,
        BiomeID_MEGA_TAIGA_HILLS = 33,
        BiomeID_EXTREME_HILLS_PLUS = 34,
        BiomeID_SAVANNA = 35,
        BiomeID_SAVANNA_PLATEAU = 36,
        BiomeID_MESA = 37,
        BiomeID_MESA_PLATEAU_F = 38,
        BiomeID_MESA_PLATEAU = 39,
        BiomeID_THE_VOID = 127,
        BiomeID_SUNFLOWER_PLAINS = 129,
        BiomeID_DESERT_M = 130,
        BiomeID_EXTREME_HILLS_M = 131,
        BiomeID_FLOWER_FOREST = 132,
        BiomeID_TAIGA_M = 133,
        BiomeID_SWAMPLAND_M = 134,
        BiomeID_ICE_PLAINS_SPIKES = 140,
        BiomeID_JUNGLE_M = 149,
        BiomeID_JUNGLE_EDGE_M = 151,
        BiomeID_BIRCH_FOREST_M = 155,
        BiomeID_BIRCH_FOREST_HILLS_M = 156,
        BiomeID_ROOFED_FOREST_M = 157,
        BiomeID_COLD_TAIGA_M = 158,
        BiomeID_MEGA_SPRUCE_TAIGA = 160,
        BiomeID_REDWOOD_TAIGA_HILLS_M = 161,
        BiomeID_EXTREME_HILLS_PLUS_M = 162,
        BiomeID_SAVANNA_M = 163,
        BiomeID_SAVANNA_PLATEAU_M = 164,
        BiomeID_MESA_BRYCE = 165,
        BiomeID_MESA_PLATEAU_F_M = 166,
        BiomeID_MESA_PLATEAU_M = 167,
        BiomeID_LIMIT = 256,
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

    class MobSpawnerData : public WeighedRandomItem {
    public:
        MobSpawnerData(int instanceType, int weight, int unk, int unk2) : WeighedRandomItem(weight) {
            mInstanceType = instanceType;
            _10 = unk;
            _14 = unk2;
        }

    private:
        int mInstanceType;
        int _10;
        int _14;
    };

    struct LegacyBlockData {  // Guessed name
        LegacyBlockData(int blockId = 0, int blockData = 0) : id(blockId), data(blockData) {}
        int id = 0;
        int data = 0;
    };

    Biome(Biome::EBiomeIDs, Biome::BiomeProperties*);
    static Biome** getBiomes();
    static Biome* getBiome(int);
    static Biome* getBiome(int, Biome*);
    static Biome* byId(int);

    static BiomeDecorator* createDecorator();

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

    static void generateColoursDebugOutput();

    int mNameId;
    int mDescriptionId;
    float mDepth;
    float mScale;
    float mTemperature;
    float mDownfall;
    bool mIsSnow;
    bool mIsDry;
    std::wstring mMutatedBiomeName;
    std::wstring mBiomeName;
    LegacyBlockData mGrass;
    LegacyBlockData mDirt;
    BiomeDecorator* mBiomeDecorator;
    int mBiomeID;
    std::vector<Biome::MobSpawnerData*> mHostileMobs;
    std::vector<Biome::MobSpawnerData*> mPassiveMobs;
    std::vector<Biome::MobSpawnerData*> mAquaticMobs;
    std::vector<Biome::MobSpawnerData*> mChickens;
    std::vector<Biome::MobSpawnerData*> field_d8;
    std::vector<Biome::MobSpawnerData*> field_f0;
    std::vector<Biome::MobSpawnerData*> mNeutralMobs;
    std::vector<Biome::MobSpawnerData*> mAmbientMobs;
    eMinecraftColour mWaterColor;
    eMinecraftColour mSkyColor;
    eMinecraftColour mPreviewColor;
};
