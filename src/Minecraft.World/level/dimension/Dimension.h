#pragma once

class BiomeSource;
class BlockPos;
class File;
class Level;
class LevelType;
class ChunkGenerator;
class FlatLevelSource;
class SuperflatConfig;

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
    virtual void isValidSpawn(int, int) const;
    virtual void getTimeOfDay(long long, float) const;
    virtual void getMoonPhase(long long) const;
    virtual void isNaturalDimension();
    virtual void getSunriseColor(float, float);
    virtual void getFogColor(float, float);
    virtual void mayRespawn() const;
    virtual void getCloudHeight();
    virtual void hasGround();
    virtual void getSpawnPos() const;
    virtual void getSpawnYPosition();
    virtual void isFoggyAt(int, int);
    virtual void createWorldBorder(Level*);
    virtual void saveData();
    virtual void tick();
    virtual void canUnloadChunk(int, int);
    virtual void getType() = 0;
    virtual void getXZSize();
    virtual void getPlayerConstraints(BlockPos const&);
    virtual void inPlayerConstraints(BlockPos const&);
    virtual void containsChunk(int, int);
    virtual void getBlockLightColour();

    Level* level;
    LevelType* levelType;
    SuperflatConfig* generatorOptions;
    BiomeSource* biomeSource;
    bool field_28;
    bool field_29;
    bool isHasSkyLight;
    void* brightnessRamp;
    void* field_30;
    void* field_38;
    int xzSize;
};