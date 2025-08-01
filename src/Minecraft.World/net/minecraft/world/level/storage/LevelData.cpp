#include "net/minecraft/world/level/storage/LevelData.h"

#include "com/mojang/nbt/CompoundTag.h"

#include "net/minecraft/core/BlockPos.h"
#include "net/minecraft/core/System.h"
#include "net/minecraft/world/Difficulty.h"
#include "net/minecraft/world/level/LevelType.h"

LevelData::LevelData(LevelData* other) {
    mSeed = other->mSeed;
    mLevelType = other->mLevelType;
    mGeneratorOptions = other->mGeneratorOptions;
    mGameType = other->mGameType;
    mIsGenerateMapFeatures = other->mIsGenerateMapFeatures;
    mIsSpawnBonusChest = other->mIsSpawnBonusChest;
    mSpawnPosX = other->mSpawnPosX;
    mSpawnPosY = other->mSpawnPosY;
    mSpawnPosZ = other->mSpawnPosZ;
    mGameTime = other->mGameTime;
    mDayTime = other->mDayTime;
    mLastPlayed = other->mLastPlayed;
    mSizeOnDisk = other->mSizeOnDisk;
    qword_50 = other->qword_50;
    mLevelName = other->mLevelName;
    mVersion = other->mVersion;
    mClearWeatherTime = other->mClearWeatherTime;
    mRainTime = other->mRainTime;
    mIsRaining = other->mIsRaining;
    mThunderTime = other->mThunderTime;
    mIsThundering = other->mIsThundering;
    mIsHardcore = other->mIsHardcore;
    mAllowCommands = other->mAllowCommands;
    mInited = other->mInited;
    mCloudHeight = other->mCloudHeight;
    mUseNewSeaLevel = other->mUseNewSeaLevel;
    mHasBeenInCreativeMode = other->mHasBeenInCreativeMode;
    mDifficulty = other->mDifficulty;
    mIsDifficultyLocked = other->mIsDifficultyLocked;
    mHasStronghold = other->mHasStronghold;
    mStrongholdPosX = other->mStrongholdPosX;
    mStrongholdPosY = other->mStrongholdPosY;
    mStrongholdPosZ = other->mStrongholdPosZ;
    mStrongholdEndPortalX = other->mStrongholdEndPortalX;
    mStrongholdEndPortalZ = other->mStrongholdEndPortalZ;
    mHasStrongholdEndPortal = other->mHasStrongholdEndPortal;
    mXZSize = other->mXZSize;
    mHellScale = other->mHellScale;
    mIsModernEnd = other->mIsModernEnd;
    mIsClassicMoat = other->mIsClassicMoat;
    mIsSmallMoat = other->mIsSmallMoat;
    mIsMediumMoat = other->mIsMediumMoat;
    mCurrentXZSize = other->mCurrentXZSize;
    mCurrentHellScale = other->mCurrentHellScale;
    mIsBiggerBiomes = other->mIsBiggerBiomes;
    mBiomeCenterXChunk = other->mBiomeCenterXChunk;
    mBiomeCenterZChunk = other->mBiomeCenterZChunk;
}

CompoundTag* LevelData::createTag() {
    CompoundTag* tag = new CompoundTag();
    setTagData(tag);
    return tag;
}

CompoundTag* LevelData::createTag(std::vector<std::shared_ptr<Player>>*) {
    return createTag();
}

void LevelData::setTagData(CompoundTag* out) {
    out->putInt(sLevelDataVersionString, 922);  // why is DataVersion it's own static shit wtf
    out->putLong(L"RandomSeed", this->mSeed);
    out->putString(L"generatorName", this->mLevelType->getGeneratorName());
    out->putInt(L"generatorVersion", this->mLevelType->getVersion());

    if (this->mGeneratorOptions) {
        out->put(L"generatorOptions", this->mGeneratorOptions->toTag());
    }

    out->putInt(L"GameType", this->mGameType->getId());
    out->putBoolean(L"MapFeatures", this->mIsGenerateMapFeatures);
    out->putBoolean(L"spawnBonusChest", this->mIsSpawnBonusChest);
    out->putInt(L"SpawnX", this->mSpawnPosX);
    out->putInt(L"SpawnY", this->mSpawnPosY);
    out->putInt(L"SpawnZ", this->mSpawnPosZ);
    out->putLong(L"Time", this->mGameTime);
    out->putLong(L"DayTime", this->mDayTime);
    out->putLong(L"SizeOnDisk", this->mSizeOnDisk);
    out->putLong(L"LastPlayed", System::processTimeInMilliSecs());
    out->putString(L"LevelName", this->mLevelName);
    out->putInt(L"version", this->mVersion);
    out->putInt(L"clearWeatherTime", this->mClearWeatherTime);
    out->putInt(L"rainTime", this->mRainTime);
    out->putBoolean(L"raining", this->mIsRaining);
    out->putInt(L"thunderTime", this->mThunderTime);
    out->putBoolean(L"thundering", this->mIsThundering);
    out->putBoolean(L"hardcore", this->mIsHardcore);
    out->putBoolean(L"allowCommands", this->mAllowCommands);
    out->putBoolean(L"initialized", this->mInited);

    if (this->mDifficulty) {
        out->putByte(L"Difficulty", this->mDifficulty->getId());
    }

    if (this->mCloudHeight != 128) {
        out->putInt(L"cloudHeight", this->mCloudHeight);
    }

    out->putBoolean(L"DifficultyLocked", this->mIsDifficultyLocked);

    CompoundTag* dimensionData = new CompoundTag();

    // had to google for different ways to iterate over map bc theres like 50 ways this could have been done
    std::unordered_map<const DimensionType*, CompoundTag*>::iterator it = mDimensionData.begin();
    while (it != mDimensionData.end()) {
        dimensionData->put(it->first->getName(), it->second->copy());
        ++it;
    }

    out->put(L"DimensionData", dimensionData);

    out->putBoolean(L"newSeaLevel", this->mUseNewSeaLevel);
    out->putBoolean(L"hasBeenInCreative", this->mHasBeenInCreativeMode);

    out->putBoolean(L"hasStronghold", this->mHasStronghold);
    out->putInt(L"StrongholdX", this->mStrongholdPosX);
    out->putInt(L"StrongholdY", this->mStrongholdPosY);
    out->putInt(L"StrongholdZ", this->mStrongholdPosZ);

    out->putBoolean(L"hasStrongholdEndPortal", this->mHasStrongholdEndPortal);
    out->putInt(L"StrongholdEndPortalX", this->mStrongholdEndPortalX);
    out->putInt(L"StrongholdEndPortalZ", this->mStrongholdEndPortalZ);

    out->putInt(L"XZSize", this->mXZSize);
    out->putInt(L"HellScale", this->mHellScale);
    out->putBoolean(L"ModernEnd", this->mIsModernEnd);

    out->putInt(L"ClassicMoat", this->mIsClassicMoat);
    out->putInt(L"SmallMoat", this->mIsSmallMoat);
    out->putInt(L"MediumMoat", this->mIsMediumMoat);

    out->putInt(L"BiomeScale", this->mIsBiggerBiomes);
    out->putInt(L"BiomeCentreXChunk", this->mBiomeCenterXChunk);
    out->putInt(L"BiomeCentreZChunk", this->mBiomeCenterZChunk);
}

long LevelData::getSeed() {
    return mSeed;
}
int LevelData::getXSpawn() {
    return mSpawnPosX;
}
int LevelData::getYSpawn() {
    return mSpawnPosY;
}
int LevelData::getZSpawn() {
    return mSpawnPosZ;
}
int LevelData::getXStronghold() {
    return mStrongholdPosX;
}
int LevelData::getZStronghold() {
    return mStrongholdPosZ;
}
int LevelData::getXStrongholdEndPortal() {
    return mStrongholdEndPortalX;
}
int LevelData::getZStrongholdEndPortal() {
    return mStrongholdEndPortalZ;
}
long LevelData::getGameTime() {
    return mGameTime;
}
long LevelData::getDayTime() {
    return mDayTime;
}
long LevelData::getSizeOnDisk() {
    return mSizeOnDisk;
}
void* LevelData::getLoadedPlayerTag() {
    return nullptr;
}
void LevelData::setSeed(long long seed) {
    mSeed = seed;
}
void LevelData::setXSpawn(int x) {
    mSpawnPosX = x;
}
void LevelData::setYSpawn(int y) {
    mSpawnPosY = y;
}
void LevelData::setZSpawn(int z) {
    mSpawnPosZ = z;
}
void LevelData::setHasStronghold() {
    mHasStronghold = true;
}
bool LevelData::getHasStronghold() {
    return mHasStronghold;
}
void LevelData::setXStronghold(int x) {
    mStrongholdPosX = x;
}
void LevelData::setZStronghold(int z) {
    mStrongholdPosZ = z;
}
void LevelData::setHasStrongholdEndPortal() {
    mHasStrongholdEndPortal = true;
}
bool LevelData::getHasStrongholdEndPortal() {
    return mHasStrongholdEndPortal;
}
void LevelData::setXStrongholdEndPortal(int x) {
    mStrongholdEndPortalX = x;
}
void LevelData::setZStrongholdEndPortal(int z) {
    mStrongholdEndPortalZ = z;
}
void LevelData::setGameTime(long long time) {
    mGameTime = time;
}
void LevelData::setDayTime(long long dayTime) {
    mDayTime = dayTime;
}
void LevelData::setSizeOnDisk(long long sizeOnDisk) {
    mSizeOnDisk = sizeOnDisk;
}
void LevelData::setLoadedPlayerTag(CompoundTag*) {}
void LevelData::setSpawn(const BlockPos& pos) {
    mSpawnPosX = pos.getX();
    mSpawnPosY = pos.getY();
    mSpawnPosZ = pos.getZ();
}
std::wstring LevelData::getLevelName() {
    return mLevelName;
}

void LevelData::setLevelName(const std::wstring& name) {
    mLevelName = name;
}

int LevelData::getVersion() {
    return mVersion;
}

void LevelData::setVersion(int version) {
    mVersion = version;
}
long LevelData::getLastPlayed() {
    return mLastPlayed;
}
int LevelData::getClearWeatherTime() {
    return mClearWeatherTime;
}
void LevelData::setClearWeatherTime(int clearWeatherTime) {
    mClearWeatherTime = clearWeatherTime;
}
bool LevelData::isThundering() {
    return mIsThundering;
}
void LevelData::setThundering(bool isThundering) {
    mIsThundering = isThundering;
}
int LevelData::getThunderTime() {
    return mThunderTime;
}
void LevelData::setThunderTime(int thunderTime) {
    mThunderTime = thunderTime;
}
bool LevelData::isRaining() {
    return mIsRaining;
}
void LevelData::setRaining(bool isRaining) {
    mIsRaining = isRaining;
}
int LevelData::getRainTime() {
    return mRainTime;
}
void LevelData::setRainTime(int rainTime) {
    mRainTime = rainTime;
}
const GameType* LevelData::getGameType() {
    return mGameType;
}
bool LevelData::isGenerateMapFeatures() {
    return mIsGenerateMapFeatures;
}
void LevelData::setGenerateMapFeatures(bool isGenerateMapFeatures) {
    mIsGenerateMapFeatures = isGenerateMapFeatures;
}
bool LevelData::getSpawnBonusChest() {
    return mIsSpawnBonusChest;
}
bool LevelData::useNewSeaLevel() {
    return mUseNewSeaLevel;
}
bool LevelData::getHasBeenInCreative() {
    return mHasBeenInCreativeMode;
}

void LevelData::setHasBeenInCreative(bool hasBeenInCreative) {
    mHasBeenInCreativeMode = hasBeenInCreative;
}

LevelType* LevelData::getGeneratorType() {
    return mLevelType;
}

void LevelData::setGeneratorType(LevelType* levelType) {
    bool hasBeenInCreative = mHasBeenInCreativeMode;
    LevelType* flatType = LevelType::FLAT;

    mLevelType = levelType;

    mHasBeenInCreativeMode = levelType == flatType || hasBeenInCreative;
}
SuperflatConfig* LevelData::getGeneratorOptions() {
    return mGeneratorOptions;
}
void LevelData::setGeneratorOptions(SuperflatConfig* config) {
    mGeneratorOptions = config;
}
bool LevelData::isHardcore() {
    return mIsHardcore;
}
void LevelData::setHardcore(bool isHardcore) {
    mIsHardcore = isHardcore;
}
bool LevelData::getAllowCommands() {
    return mAllowCommands;
}
void LevelData::setAllowCommands(bool isAllowCommands) {
    mAllowCommands = isAllowCommands;
}
bool LevelData::isInitialized() {
    return mInited;
}
void LevelData::setInitialized(bool isInited) {
    mInited = isInited;
}
const Difficulty* LevelData::getDifficulty() {
    return mDifficulty;
}
int LevelData::getCloudHeight() {
    return mCloudHeight;
}
void LevelData::setCloudHeight(int cloudHeight) {
    mCloudHeight = cloudHeight;
}
bool LevelData::isDifficultyLocked() {
    return mIsDifficultyLocked;
}
void LevelData::setDifficultyLocked(bool isDifficultyLocked) {
    mIsDifficultyLocked = isDifficultyLocked;
}
int LevelData::getXZSize() {
    return mXZSize;
}
int LevelData::getCurrentXZSize() {
    return mCurrentXZSize;
}
int LevelData::getHellScale() {
    return mHellScale;
}
void LevelData::setModernEnd() {
    mIsModernEnd = true;
}
bool LevelData::getModernEnd() {
    return mIsModernEnd;
}
bool LevelData::getBiomeScale() {
    return mIsBiggerBiomes;
}
int LevelData::getBiomeCentreXChunk() {
    return mBiomeCenterXChunk;
}
int LevelData::getBiomeCentreZChunk() {
    return mBiomeCenterZChunk;
}
