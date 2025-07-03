#include "net/minecraft/world/level/storage/LevelData.h"

#include "com/mojang/nbt/CompoundTag.h"
#include "net/minecraft/core/BlockPos.h"
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

// NON_MATCHING: regswap
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
