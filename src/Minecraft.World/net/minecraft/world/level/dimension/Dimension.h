#pragma once

class BiomeSource;
class BlockPos;
class DimensionType;
class File;
class Level;
class LevelType;
class ChunkGenerator;
class FlatLevelSource;
class SuperflatConfig;
class WorldBorder;
class AABB;

class Dimension {
public:
    Dimension();
    virtual void init(Level*);
    virtual void init();
    virtual void updateLightRamp();
    virtual ~Dimension();
    virtual ChunkGenerator* createRandomLevelGenerator() const;
    virtual FlatLevelSource* createFlatLevelSource() const;
    virtual void createStorage(File);
    virtual bool isValidSpawn(int, int) const;
    virtual void getTimeOfDay(long long, float) const;
    virtual int getMoonPhase(long long) const;
    virtual bool isNaturalDimension();
    virtual void getSunriseColor(float, float);
    virtual void getFogColor(float, float);
    virtual bool mayRespawn() const;
    virtual void getCloudHeight();
    virtual bool hasGround();
    virtual void* getSpawnPos() const;
    virtual int getSpawnYPosition();
    virtual bool isFoggyAt(int, int);
    virtual WorldBorder* createWorldBorder(Level*);
    virtual void saveData();
    virtual void tick();
    virtual bool canUnloadChunk(int, int);
    virtual DimensionType* getType() = 0;
    virtual int getXZSize();
    virtual AABB* getPlayerConstraints(const BlockPos&);
    virtual bool inPlayerConstraints(const BlockPos&);
    virtual bool containsChunk(int, int);
    virtual void getBlockLightColour();

    BiomeSource* getBiomeSource();
    bool isHasCeiling();
    float* getBrightnessRamp();
    bool isHasSkyLight();
    bool isUltraWarm();

    Level* m_level;
    LevelType* m_levelType;
    SuperflatConfig* m_generatorOptions;
    BiomeSource* m_biomeSource;
    bool m_field28;
    bool m_isHasCeiling;
    bool m_isHasSkyLight;
    float* m_brightnessRamp;
    void* m_field30;
    void* m_field38;
    int m_xzSize;
};
