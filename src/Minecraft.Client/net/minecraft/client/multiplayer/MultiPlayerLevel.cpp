#include "Minecraft.Client/CGameNetworkManager.h"
#include "Minecraft.Client/Minecraft.h"
#include "Minecraft.Client/Options.h"
#include "Minecraft.Client/multiplayer/ClientChunkCache.h"
#include "Minecraft.Client/multiplayer/MultiPlayerLevel.h"
#include "Minecraft.World/Random.h"
#include "Minecraft.World/level/Level.h"
#include "Minecraft.World/level/chunk/ChunkSource.h"
#include "Minecraft.World/level/chunk/LevelChunk.h"
#include "Minecraft.World/level/dimension/Dimension.h"
#include "Minecraft.World/level/dimension/DimensionType.h"
#include "Minecraft.World/level/storage/LevelData.h"
#include "Minecraft.World/level/storage/MockedLevelStorage.h"
#include "Minecraft.World/level/storage/SavedDataStorage.h"
#include "Minecraft.World/scores/ClientScoreboard.h"

MultiPlayerLevel::MultiPlayerLevel(std::shared_ptr<LevelStorage> levelStorage,
                                   ClientPacketListener* packetListener, LevelSettings* levelSettings,
                                   int dimensionId, const Difficulty* difficulty)
    : Level(levelStorage, new LevelData(levelSettings, L"MpServer"),
            DimensionType::getById(dimensionId)->create(), true) {
    MultiPlayerLevelInit(packetListener, levelSettings, difficulty);
}

MultiPlayerLevel::MultiPlayerLevel(ClientPacketListener* packetListener, LevelSettings* levelSettings,
                                   int dimensionId, const Difficulty* difficulty)
    : Level(std::shared_ptr<MockedLevelStorage>(new MockedLevelStorage()),
            new LevelData(levelSettings, L"MpServer"), DimensionType::getById(dimensionId)->create(), true) {
    MultiPlayerLevelInit(packetListener, levelSettings, difficulty);
}

void MultiPlayerLevel::MultiPlayerLevelInit(ClientPacketListener* packetListener,
                                            LevelSettings* levelSettings, const Difficulty* difficulty) {
    mMinecraft = Minecraft::GetInstance();
    mDimension->init(this);
    mChunkSource = createChunkSource();
    mChunkCache = mChunkSource->getCache();
    mXZSize = mChunkSource->mXZSize;
    if (!mLevelData->isInitialized()) {
        initializeLevel(levelSettings);
        mLevelData->setInitialized(true);
    }

    delete levelSettings;

    if (packetListener)
        mPacketListeners.push_back(packetListener);

    getLevelData()->setDifficulty(difficulty);

    delete mSavedDataStorage;

    mSavedDataStorage = nullptr;

    dword_2cc = 0;
    dword_2d0 = 0;
    dword_2d4 = 0;
    dword_2d8 = 0;
    byte_2c8 = true;
    mClientScoreboard = new ClientScoreboard();

    updateSkyBrightness();
    prepareWeather();

    field_3b0 = mRandom->nextInt(12000);
}

MultiPlayerLevel::~MultiPlayerLevel() {
    mSavedDataStorage = nullptr;
    delete mClientScoreboard;
}

ChunkSource* MultiPlayerLevel::createChunkSource() {
    if (Minecraft::InMiniGame(NORMAL_WORLD, true) && !CGameNetworkManager::sInstance.IsHost()) {
        ChunkStorage* storage = mLevelStorage->createChunkStorage(mDimension);
        mCache = new ClientChunkCache(this, storage);
    } else {
        mCache = new ClientChunkCache(this);
    }

    return mCache;
}

ChunkSource* MultiPlayerLevel::getChunkSource() {
    return Level::getChunkSource();
}

void MultiPlayerLevel::validateSpawn() {}

bool MultiPlayerLevel::hasChunk(int x, int z, bool unk) {
    if (unk)
        return true;

    LevelChunk* chunk = getChunkSource()->getOrCreateChunk(x, z, false);
    return !chunk->isEmpty();
}

bool MultiPlayerLevel::setBlock(const BlockPos& pos, const BlockState* state, int id, bool unk) {
    if (getBlockState(pos) == state) {
        checkLight(pos, false, false);
        return false;
    }

    unshareChunkAt(pos.getX(), pos.getZ());

    if (Level::setBlock(pos, state, id, false))
        return true;

    shareChunkAt(pos.getX(), pos.getZ());
    return false;
}

/*
void MultiPlayerLevel::playSound(std::shared_ptr<Player> player, double a3, double a4, double a5,
                                 const SoundEvent* soundEvent, SoundSource::ESoundSource soundSource,
                                 float a8, float a9, float a10) {
    Minecraft* minecraft = mMinecraft;
    for (s32 i = 0; i < 4; ++i) {
        if (minecraft && minecraft->mLocalPlayers[i]) {
            // arguments are wrong
            playLocalSound(a3, a4, 0.0f, soundEvent, soundSource, a8, a9, true, a10);
        }
    }
}
*/

bool MultiPlayerLevel::addEntity(const std::shared_ptr<Entity>&) {}

void MultiPlayerLevel::tickWeather(bool) {}

int MultiPlayerLevel::getChunkPollRange() {
    return mMinecraft->mOptions->mViewDistance;
}

void MultiPlayerLevel::sendPacketToServer(std::shared_ptr<Packet>) {}

void* MultiPlayerLevel::makeSoundUpdater(std::shared_ptr<Minecart>) {
    return nullptr;
}

void MultiPlayerLevel::setDayTime(long long time) {
    Level::setDayTime(time);
}
