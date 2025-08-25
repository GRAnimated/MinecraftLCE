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

    long mSeed;
    LevelType* mLevelType;
    SuperflatConfig* mGeneratorOptions;
    int mSpawnPosX;
    int mSpawnPosY;
    int mSpawnPosZ;
    long mGameTime;
    long mDayTime;
    long mLastPlayed;
    long mSizeOnDisk;
    int qword_50;
    std::wstring mLevelName;
    int mVersion;
    int mClearWeatherTime;
    bool mIsRaining;
    int mRainTime;
    bool mIsThundering;
    int mThunderTime;
    const GameType* mGameType;
    bool mIsGenerateMapFeatures;
    bool mIsHardcore;
    bool mAllowCommands;
    bool mInited;
    const Difficulty* mDifficulty;
    bool mIsDifficultyLocked;
    std::unordered_map<const DimensionType*, CompoundTag*> mDimensionData;
    int mCloudHeight;
    bool mUseNewSeaLevel;
    bool mHasBeenInCreativeMode;
    bool mIsSpawnBonusChest;
    int mXZSize;
    int mCurrentXZSize;
    int mCurrentHellScale;
    bool mIsClassicMoat;
    bool mIsSmallMoat;
    bool mIsMediumMoat;
    int mHellScale;
    bool mIsModernEnd;
    int mStrongholdPosX;
    int mStrongholdPosY;
    int mStrongholdPosZ;
    bool mHasStronghold;
    int mStrongholdEndPortalX;
    int mStrongholdEndPortalZ;
    bool mHasStrongholdEndPortal;
    bool mIsBiggerBiomes;
    int mBiomeCenterXChunk;
    int mBiomeCenterZChunk;
    GameRules mGameRules;
};
