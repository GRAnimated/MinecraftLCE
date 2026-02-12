#include "net/minecraft/world/level/storage/LevelData.h"

#include "com/mojang/nbt/CompoundTag.h"

#include "net/minecraft/core/BlockPos.h"
#include "net/minecraft/core/System.h"
#include "net/minecraft/world/Difficulty.h"
#include "net/minecraft/world/level/LevelType.h"

LevelData::LevelData(LevelData* other) {
    m_seed = other->m_seed;
    m_levelType = other->m_levelType;
    m_generatorOptions = other->m_generatorOptions;
    m_gameType = other->m_gameType;
    m_isGenerateMapFeatures = other->m_isGenerateMapFeatures;
    m_isSpawnBonusChest = other->m_isSpawnBonusChest;
    m_spawnPosX = other->m_spawnPosX;
    m_spawnPosY = other->m_spawnPosY;
    m_spawnPosZ = other->m_spawnPosZ;
    m_gameTime = other->m_gameTime;
    m_dayTime = other->m_dayTime;
    m_lastPlayed = other->m_lastPlayed;
    m_sizeOnDisk = other->m_sizeOnDisk;
    m_qword50 = other->m_qword50;
    m_levelName = other->m_levelName;
    m_version = other->m_version;
    m_clearWeatherTime = other->m_clearWeatherTime;
    m_rainTime = other->m_rainTime;
    m_isRaining = other->m_isRaining;
    m_thunderTime = other->m_thunderTime;
    m_isThundering = other->m_isThundering;
    m_isHardcore = other->m_isHardcore;
    m_allowCommands = other->m_allowCommands;
    m_inited = other->m_inited;
    m_cloudHeight = other->m_cloudHeight;
    m_useNewSeaLevel = other->m_useNewSeaLevel;
    m_hasBeenInCreativeMode = other->m_hasBeenInCreativeMode;
    m_difficulty = other->m_difficulty;
    m_isDifficultyLocked = other->m_isDifficultyLocked;
    m_hasStronghold = other->m_hasStronghold;
    m_strongholdPosX = other->m_strongholdPosX;
    m_strongholdPosY = other->m_strongholdPosY;
    m_strongholdPosZ = other->m_strongholdPosZ;
    m_strongholdEndPortalX = other->m_strongholdEndPortalX;
    m_strongholdEndPortalZ = other->m_strongholdEndPortalZ;
    m_hasStrongholdEndPortal = other->m_hasStrongholdEndPortal;
    m_xzSize = other->m_xzSize;
    m_hellScale = other->m_hellScale;
    m_isModernEnd = other->m_isModernEnd;
    m_isClassicMoat = other->m_isClassicMoat;
    m_isSmallMoat = other->m_isSmallMoat;
    m_isMediumMoat = other->m_isMediumMoat;
    m_currentXzSize = other->m_currentXzSize;
    m_currentHellScale = other->m_currentHellScale;
    m_isBiggerBiomes = other->m_isBiggerBiomes;
    m_biomeCenterXChunk = other->m_biomeCenterXChunk;
    m_biomeCenterZChunk = other->m_biomeCenterZChunk;
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
    out->putLong(L"RandomSeed", this->m_seed);
    out->putString(L"generatorName", this->m_levelType->getGeneratorName());
    out->putInt(L"generatorVersion", this->m_levelType->getVersion());

    if (this->m_generatorOptions) {
        out->put(L"generatorOptions", this->m_generatorOptions->toTag());
    }

    out->putInt(L"GameType", this->m_gameType->getId());
    out->putBoolean(L"MapFeatures", this->m_isGenerateMapFeatures);
    out->putBoolean(L"spawnBonusChest", this->m_isSpawnBonusChest);
    out->putInt(L"SpawnX", this->m_spawnPosX);
    out->putInt(L"SpawnY", this->m_spawnPosY);
    out->putInt(L"SpawnZ", this->m_spawnPosZ);
    out->putLong(L"Time", this->m_gameTime);
    out->putLong(L"DayTime", this->m_dayTime);
    out->putLong(L"SizeOnDisk", this->m_sizeOnDisk);
    out->putLong(L"LastPlayed", System::processTimeInMilliSecs());
    out->putString(L"LevelName", this->m_levelName);
    out->putInt(L"version", this->m_version);
    out->putInt(L"clearWeatherTime", this->m_clearWeatherTime);
    out->putInt(L"rainTime", this->m_rainTime);
    out->putBoolean(L"raining", this->m_isRaining);
    out->putInt(L"thunderTime", this->m_thunderTime);
    out->putBoolean(L"thundering", this->m_isThundering);
    out->putBoolean(L"hardcore", this->m_isHardcore);
    out->putBoolean(L"allowCommands", this->m_allowCommands);
    out->putBoolean(L"initialized", this->m_inited);

    if (this->m_difficulty) {
        out->putByte(L"Difficulty", this->m_difficulty->getId());
    }

    if (this->m_cloudHeight != 128) {
        out->putInt(L"cloudHeight", this->m_cloudHeight);
    }

    out->putBoolean(L"DifficultyLocked", this->m_isDifficultyLocked);

    CompoundTag* dimensionData = new CompoundTag();

    // had to google for different ways to iterate over map bc theres like 50 ways this could have been done
    std::unordered_map<const DimensionType*, CompoundTag*>::iterator it = m_dimensionData.begin();
    while (it != m_dimensionData.end()) {
        dimensionData->put(it->first->getName(), it->second->copy());
        ++it;
    }

    out->put(L"DimensionData", dimensionData);

    out->putBoolean(L"newSeaLevel", this->m_useNewSeaLevel);
    out->putBoolean(L"hasBeenInCreative", this->m_hasBeenInCreativeMode);

    out->putBoolean(L"hasStronghold", this->m_hasStronghold);
    out->putInt(L"StrongholdX", this->m_strongholdPosX);
    out->putInt(L"StrongholdY", this->m_strongholdPosY);
    out->putInt(L"StrongholdZ", this->m_strongholdPosZ);

    out->putBoolean(L"hasStrongholdEndPortal", this->m_hasStrongholdEndPortal);
    out->putInt(L"StrongholdEndPortalX", this->m_strongholdEndPortalX);
    out->putInt(L"StrongholdEndPortalZ", this->m_strongholdEndPortalZ);

    out->putInt(L"XZSize", this->m_xzSize);
    out->putInt(L"HellScale", this->m_hellScale);
    out->putBoolean(L"ModernEnd", this->m_isModernEnd);

    out->putInt(L"ClassicMoat", this->m_isClassicMoat);
    out->putInt(L"SmallMoat", this->m_isSmallMoat);
    out->putInt(L"MediumMoat", this->m_isMediumMoat);

    out->putInt(L"BiomeScale", this->m_isBiggerBiomes);
    out->putInt(L"BiomeCentreXChunk", this->m_biomeCenterXChunk);
    out->putInt(L"BiomeCentreZChunk", this->m_biomeCenterZChunk);
}

long LevelData::getSeed() {
    return m_seed;
}
int LevelData::getXSpawn() {
    return m_spawnPosX;
}
int LevelData::getYSpawn() {
    return m_spawnPosY;
}
int LevelData::getZSpawn() {
    return m_spawnPosZ;
}
int LevelData::getXStronghold() {
    return m_strongholdPosX;
}
int LevelData::getZStronghold() {
    return m_strongholdPosZ;
}
int LevelData::getXStrongholdEndPortal() {
    return m_strongholdEndPortalX;
}
int LevelData::getZStrongholdEndPortal() {
    return m_strongholdEndPortalZ;
}
long LevelData::getGameTime() {
    return m_gameTime;
}
long LevelData::getDayTime() {
    return m_dayTime;
}
long LevelData::getSizeOnDisk() {
    return m_sizeOnDisk;
}
void* LevelData::getLoadedPlayerTag() {
    return nullptr;
}
void LevelData::setSeed(long long seed) {
    m_seed = seed;
}
void LevelData::setXSpawn(int x) {
    m_spawnPosX = x;
}
void LevelData::setYSpawn(int y) {
    m_spawnPosY = y;
}
void LevelData::setZSpawn(int z) {
    m_spawnPosZ = z;
}
void LevelData::setHasStronghold() {
    m_hasStronghold = true;
}
bool LevelData::getHasStronghold() {
    return m_hasStronghold;
}
void LevelData::setXStronghold(int x) {
    m_strongholdPosX = x;
}
void LevelData::setZStronghold(int z) {
    m_strongholdPosZ = z;
}
void LevelData::setHasStrongholdEndPortal() {
    m_hasStrongholdEndPortal = true;
}
bool LevelData::getHasStrongholdEndPortal() {
    return m_hasStrongholdEndPortal;
}
void LevelData::setXStrongholdEndPortal(int x) {
    m_strongholdEndPortalX = x;
}
void LevelData::setZStrongholdEndPortal(int z) {
    m_strongholdEndPortalZ = z;
}
void LevelData::setGameTime(long long time) {
    m_gameTime = time;
}
void LevelData::setDayTime(long long dayTime) {
    m_dayTime = dayTime;
}
void LevelData::setSizeOnDisk(long long sizeOnDisk) {
    m_sizeOnDisk = sizeOnDisk;
}
void LevelData::setLoadedPlayerTag(CompoundTag*) {}
void LevelData::setSpawn(const BlockPos& pos) {
    m_spawnPosX = pos.getX();
    m_spawnPosY = pos.getY();
    m_spawnPosZ = pos.getZ();
}
std::wstring LevelData::getLevelName() {
    return m_levelName;
}

void LevelData::setLevelName(const std::wstring& name) {
    m_levelName = name;
}

int LevelData::getVersion() {
    return m_version;
}

void LevelData::setVersion(int version) {
    m_version = version;
}
long LevelData::getLastPlayed() {
    return m_lastPlayed;
}
int LevelData::getClearWeatherTime() {
    return m_clearWeatherTime;
}
void LevelData::setClearWeatherTime(int clearWeatherTime) {
    m_clearWeatherTime = clearWeatherTime;
}
bool LevelData::isThundering() {
    return m_isThundering;
}
void LevelData::setThundering(bool isThundering) {
    m_isThundering = isThundering;
}
int LevelData::getThunderTime() {
    return m_thunderTime;
}
void LevelData::setThunderTime(int thunderTime) {
    m_thunderTime = thunderTime;
}
bool LevelData::isRaining() {
    return m_isRaining;
}
void LevelData::setRaining(bool isRaining) {
    m_isRaining = isRaining;
}
int LevelData::getRainTime() {
    return m_rainTime;
}
void LevelData::setRainTime(int rainTime) {
    m_rainTime = rainTime;
}
const GameType* LevelData::getGameType() {
    return m_gameType;
}
bool LevelData::isGenerateMapFeatures() {
    return m_isGenerateMapFeatures;
}
void LevelData::setGenerateMapFeatures(bool isGenerateMapFeatures) {
    m_isGenerateMapFeatures = isGenerateMapFeatures;
}
bool LevelData::getSpawnBonusChest() {
    return m_isSpawnBonusChest;
}
bool LevelData::useNewSeaLevel() {
    return m_useNewSeaLevel;
}
bool LevelData::getHasBeenInCreative() {
    return m_hasBeenInCreativeMode;
}

void LevelData::setHasBeenInCreative(bool hasBeenInCreative) {
    m_hasBeenInCreativeMode = hasBeenInCreative;
}

LevelType* LevelData::getGeneratorType() {
    return m_levelType;
}

void LevelData::setGeneratorType(LevelType* levelType) {
    bool hasBeenInCreative = m_hasBeenInCreativeMode;
    LevelType* flatType = LevelType::FLAT;

    m_levelType = levelType;

    m_hasBeenInCreativeMode = levelType == flatType || hasBeenInCreative;
}
SuperflatConfig* LevelData::getGeneratorOptions() {
    return m_generatorOptions;
}
void LevelData::setGeneratorOptions(SuperflatConfig* config) {
    m_generatorOptions = config;
}
bool LevelData::isHardcore() {
    return m_isHardcore;
}
void LevelData::setHardcore(bool isHardcore) {
    m_isHardcore = isHardcore;
}
bool LevelData::getAllowCommands() {
    return m_allowCommands;
}
void LevelData::setAllowCommands(bool isAllowCommands) {
    m_allowCommands = isAllowCommands;
}
bool LevelData::isInitialized() {
    return m_inited;
}
void LevelData::setInitialized(bool isInited) {
    m_inited = isInited;
}
const Difficulty* LevelData::getDifficulty() {
    return m_difficulty;
}
int LevelData::getCloudHeight() {
    return m_cloudHeight;
}
void LevelData::setCloudHeight(int cloudHeight) {
    m_cloudHeight = cloudHeight;
}
bool LevelData::isDifficultyLocked() {
    return m_isDifficultyLocked;
}
void LevelData::setDifficultyLocked(bool isDifficultyLocked) {
    m_isDifficultyLocked = isDifficultyLocked;
}
int LevelData::getXZSize() {
    return m_xzSize;
}
int LevelData::getCurrentXZSize() {
    return m_currentXzSize;
}
int LevelData::getHellScale() {
    return m_hellScale;
}
void LevelData::setModernEnd() {
    m_isModernEnd = true;
}
bool LevelData::getModernEnd() {
    return m_isModernEnd;
}
bool LevelData::getBiomeScale() {
    return m_isBiggerBiomes;
}
int LevelData::getBiomeCentreXChunk() {
    return m_biomeCenterXChunk;
}
int LevelData::getBiomeCentreZChunk() {
    return m_biomeCenterZChunk;
}
