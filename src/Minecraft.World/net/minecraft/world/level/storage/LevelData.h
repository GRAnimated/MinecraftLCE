#pragma once

#include "net/minecraft/world/level/GameRules.h"
#include "net/minecraft/world/level/LevelType.h"
#include "net/minecraft/world/level/dimension/DimensionType.h"
#include "net/minecraft/world/level/gamemode/GameType.h"

#include "net/minecraft/core/BlockPos.h"
#include "net/minecraft/world/level/storage/config/SuperflatConfig.h"
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

class CompoundTag;
class BlockPos;
class Player;
class Difficulty;
class LevelSettings;

class LevelData {
public:
    static std::wstring sLevelDataVersionString;

    LevelData();
    LevelData(CompoundTag*);
    LevelData(LevelSettings*, const std::wstring&);
    LevelData(LevelData*);
    virtual ~LevelData();
    virtual CompoundTag* createTag();
    virtual CompoundTag* createTag(std::vector<std::shared_ptr<Player>>*);
    virtual void setTagData(CompoundTag* out);
    virtual long getSeed();
    virtual int getXSpawn();
    virtual int getYSpawn();
    virtual int getZSpawn();
    virtual int getXStronghold();
    virtual int getZStronghold();
    virtual int getXStrongholdEndPortal();
    virtual int getZStrongholdEndPortal();
    virtual long getGameTime();
    virtual long getDayTime();
    virtual long getSizeOnDisk();
    virtual void* getLoadedPlayerTag();
    virtual void setSeed(long long);
    virtual void setXSpawn(int);
    virtual void setYSpawn(int);
    virtual void setZSpawn(int);
    virtual void setHasStronghold();
    virtual bool getHasStronghold();
    virtual void setXStronghold(int);
    virtual void setZStronghold(int);
    virtual void setHasStrongholdEndPortal();
    virtual bool getHasStrongholdEndPortal();
    virtual void setXStrongholdEndPortal(int);
    virtual void setZStrongholdEndPortal(int);
    virtual void setGameTime(long long);
    virtual void setDayTime(long long);
    virtual void setSizeOnDisk(long long);
    virtual void setLoadedPlayerTag(CompoundTag*);
    virtual void setSpawn(const BlockPos&);
    virtual std::wstring getLevelName();
    virtual void setLevelName(const std::wstring&);
    virtual int getVersion();
    virtual void setVersion(int);
    virtual long getLastPlayed();
    virtual int getClearWeatherTime();
    virtual void setClearWeatherTime(int);
    virtual bool isThundering();
    virtual void setThundering(bool);
    virtual int getThunderTime();
    virtual void setThunderTime(int);
    virtual bool isRaining();
    virtual void setRaining(bool);
    virtual int getRainTime();
    virtual void setRainTime(int);
    virtual const GameType* getGameType();
    virtual bool isGenerateMapFeatures();
    virtual void setGenerateMapFeatures(bool);
    virtual bool getSpawnBonusChest();
    virtual void setGameType(const GameType*);
    virtual bool useNewSeaLevel();
    virtual bool getHasBeenInCreative();
    virtual void setHasBeenInCreative(bool);
    virtual LevelType* getGeneratorType();
    virtual void setGeneratorType(LevelType*);
    virtual SuperflatConfig* getGeneratorOptions();
    virtual void setGeneratorOptions(SuperflatConfig*);
    virtual bool isHardcore();
    virtual void setHardcore(bool);
    virtual bool getAllowCommands();
    virtual void setAllowCommands(bool);
    virtual bool isInitialized();
    virtual void setInitialized(bool);
    virtual GameRules* getGameRules();
    virtual const Difficulty* getDifficulty();
    virtual void setDifficulty(const Difficulty*);
    virtual int getCloudHeight();
    virtual void setCloudHeight(int);
    virtual bool isDifficultyLocked();
    virtual void setDifficultyLocked(bool);
    virtual void getDimensionData(const DimensionType*);
    virtual void setDimensionData(const DimensionType*, CompoundTag*);
    virtual int getXZSize();
    virtual int getCurrentXZSize();
    virtual void fillMoatValues(bool* isClassicMoat, bool* isSmallMoat, bool* isMediumMoat);  // made up name
    virtual void func_7100212238();
    virtual int getHellScale();
    virtual void setModernEnd();
    virtual bool getModernEnd();
    virtual bool getBiomeScale();
    virtual int getBiomeCentreXChunk();
    virtual int getBiomeCentreZChunk();

    long m_seed;
    LevelType* m_levelType;
    SuperflatConfig* m_generatorOptions;
    int m_spawnPosX;
    int m_spawnPosY;
    int m_spawnPosZ;
    long m_gameTime;
    long m_dayTime;
    long m_lastPlayed;
    long m_sizeOnDisk;
    int m_qword50;
    std::wstring m_levelName;
    int m_version;
    int m_clearWeatherTime;
    bool m_isRaining;
    int m_rainTime;
    bool m_isThundering;
    int m_thunderTime;
    const GameType* m_gameType;
    bool m_isGenerateMapFeatures;
    bool m_isHardcore;
    bool m_allowCommands;
    bool m_inited;
    const Difficulty* m_difficulty;
    bool m_isDifficultyLocked;
    std::unordered_map<const DimensionType*, CompoundTag*> m_dimensionData;
    int m_cloudHeight;
    bool m_useNewSeaLevel;
    bool m_hasBeenInCreativeMode;
    bool m_isSpawnBonusChest;
    int m_xzSize;
    int m_currentXzSize;
    int m_currentHellScale;
    bool m_isClassicMoat;
    bool m_isSmallMoat;
    bool m_isMediumMoat;
    int m_hellScale;
    bool m_isModernEnd;
    int m_strongholdPosX;
    int m_strongholdPosY;
    int m_strongholdPosZ;
    bool m_hasStronghold;
    int m_strongholdEndPortalX;
    int m_strongholdEndPortalZ;
    bool m_hasStrongholdEndPortal;
    bool m_isBiggerBiomes;
    int m_biomeCenterXChunk;
    int m_biomeCenterZChunk;
    GameRules m_gameRules;
};
