#include "net/minecraft/world/level/Level.h"

#include "NX/Platform.h"
#include "net/minecraft/core/System.h"
#include "net/minecraft/world/entity/Entity.h"
#include "net/minecraft/world/entity/player/Player.h"
#include "net/minecraft/world/level/LevelListener.h"
#include "net/minecraft/world/level/LevelType.h"
#include "net/minecraft/world/level/LightLayer.h"
#include "net/minecraft/world/level/PathNavigationListener.h"
#include "net/minecraft/world/level/biome/BiomeSource.h"
#include "net/minecraft/world/level/block/Blocks.h"
#include "net/minecraft/world/level/block/state/BlockState.h"
#include "net/minecraft/world/level/border/WorldBorder.h"
#include "net/minecraft/world/level/chunk/LevelChunk.h"
#include "net/minecraft/world/level/dimension/Dimension.h"
#include "net/minecraft/world/level/material/Material.h"
#include "net/minecraft/world/level/storage/LevelData.h"
#include "net/minecraft/world/level/storage/LevelStorage.h"
#include <memory>
#include <utility>

Level::Level(std::shared_ptr<LevelStorage> levelStorage, LevelData* levelData, Dimension* dimension,
             bool isLocal) {
    _init();
    m_levelStorage = levelStorage;
    m_levelData = levelData;
    m_dimension = dimension;
    m_isLocal = isLocal;
    m_worldBorder = dimension->createWorldBorder(this);
    if (!m_levelData->useNewSeaLevel())
        m_seaLevel = 64;
}

// NON_MATCHING
void Level::_init() {
    m_cloudColor = 0xFFFFFF;
    m_skyDarken = 0;
    Random rand;
    m_dword14c = rand.nextInt();
    m_dword158 = 0x3C6EF35F;

    m_pathNavigationListener = new PathNavigationListener();
    m_levelListeners.push_back((LevelListener*)m_pathNavigationListener);

    m_dword160 = 0;
    m_dword164 = 0;
    m_dword168 = 0;
    m_skyFlashTime = 0;
    m_dword15c = 0;
    m_random = new Random();
    m_byte178 = false;

    m_dimension = nullptr;
    m_chunkSource = nullptr;
    m_levelStorage = nullptr;
    m_levelData = nullptr;
    m_byte1c8 = false;
    m_savedDataStorage = nullptr;
    m_byte210 = true;
    m_byte211 = true;

    m_isLocal = false;

    InitializeCriticalSection(&m_entityMutex);
    InitializeCriticalSection(&m_blockEntityMutex);

    m_byte212 = false;

    m_qword258 = new unsigned char[0x20000];

    InitializeCriticalSectionAndSpinCount(&m_unkMutex, 0x1400);
    m_byte60 = false;
    m_dword2a8 = 0;
    m_fogDistance = -1;
    m_byte148 = 0;
    m_qword150 = nullptr;
}

const BlockState* Level::getBlockState(const BlockPos& pos) {
    if (isOutsideBuildHeight(pos))
        return Blocks::AIR->defaultBlockState();
    return getChunkAt(pos)->getBlockState(pos);
}

long long Level::getSeed() {
    return m_levelData->getSeed();
}

GameRules* Level::getGameRules() {
    return m_levelData->getGameRules();
}

const Difficulty* Level::getDifficulty() {
    return getLevelData()->getDifficulty();
}

LevelData* Level::getLevelData() {
    return m_levelData;
}

void Level::postConstruct() {}

Biome* Level::getBiome(const BlockPos& pos) {
    if (hasChunkAt(pos)) {
        LevelChunk* chunkAt = getChunkAt(pos);
        return chunkAt->getBiome(pos, m_dimension->getBiomeSource());
    } else {
        return m_dimension->getBiomeSource()->getBiome(pos, Biome::PLAINS);
    }
}

bool Level::hasChunkAt(const BlockPos& pos) {
    return hasChunkAt(pos, true);
}

LevelChunk* Level::getChunkAt(const BlockPos& pos) {
    return getChunk(pos.getX() >> 4, pos.getZ() >> 4);
}

BiomeSource* Level::getBiomeSource() {
    return m_dimension->getBiomeSource();
}

void Level::initializeLevel(LevelSettings*) {
    m_levelData->setInitialized(true);
}

MinecraftServer* Level::getServer() {
    return nullptr;
}

void Level::validateSpawn() {
    BlockPos spawnPos = {8, 64, 8};
    setSpawnPos(spawnPos);
}

const BlockState* Level::getTopBlockState(const BlockPos& pos) {
    if (m_levelData->getGeneratorType() == LevelType::FLAT)
        return Blocks::GRASS->defaultBlockState();

    BlockPos blockPos = {pos.getX(), getSeaLevel(), pos.getZ()};

    while (!isEmptyBlock(blockPos.above())) {
        blockPos = blockPos.above();
    }

    return getBlockState(blockPos);
}

int Level::getSeaLevel() {
    return m_seaLevel;
}

bool Level::isInWorldBounds(const BlockPos& pos) {
    return (unsigned int)pos.getY() < HEIGHT_LIMIT;
}

bool Level::isInWorldBounds(int x, int y, int z) {
    return (unsigned int)y < HEIGHT_LIMIT;
}

bool Level::isOutsideBuildHeight(const BlockPos& pos) {
    return pos.getY() < 0 || pos.getY() >= 256;
}

bool Level::isEmptyBlock(const BlockPos& pos) {
    return getBlockState(pos)->getMaterial() == Material::AIR;
}

void Level::blockUpdated(const BlockPos& pos, Block* block, bool unk) {
    updateNeighborsAt(pos, block, unk);
}

void Level::updateObservingBlocksAt(const BlockPos& pos, Block* block) {
    observedNeighborChanged(pos.west(), block, pos);
    observedNeighborChanged(pos.east(), block, pos);
    observedNeighborChanged(pos.below(), block, pos);
    observedNeighborChanged(pos.above(), block, pos);
    observedNeighborChanged(pos.north(), block, pos);
    observedNeighborChanged(pos.south(), block, pos);
}

void Level::setData(const BlockPos& pos, int id, int flag, bool update) {
    setData(pos.getX(), pos.getY(), pos.getZ(), id, flag, update);
}

void Level::removeBlock(const BlockPos& pos) {
    setBlock(pos, Blocks::AIR->defaultBlockState(), 3, false);
}

void Level::levelEvent(int eventType, const BlockPos& pos, int data) {
    levelEvent(nullptr, eventType, pos, data);
}

void Level::levelEvent(std::shared_ptr<Player> player, int eventType, const BlockPos& pos, int data) {
    for (LevelListener* listener : this->m_levelListeners) {
        listener->levelEvent(player, eventType, pos, data);
    }
}

void Level::setBlockAndUpdate(const BlockPos& pos, const BlockState* state) {
    setBlock(pos, state, 3, false);
}

void Level::sendBlockUpdated(const BlockPos& pos, const BlockState* state, const BlockState* state2, int id,
                             bool unk) {
    for (LevelListener* listener : this->m_levelListeners) {
        listener->blockChanged(this, pos, state, state2, id, unk);
    }
}

void Level::lightColumnChanged(int x, int z, int y0, int y1) {
    PIXBeginNamedEvent(0.0f, "LightColumnChanged (%d,%d) %d to %d", x, z, y0, y1);
    if (y0 > y1) {
        int temp = y1;
        y1 = y0;
        y0 = temp;
    }

    if (m_dimension->isHasSkyLight()) {
        PIXBeginNamedEvent(0.0f, "Checking lights");
        for (int i = y0; i <= y1; i++) {
            PIXBeginNamedEvent(0.0f, "Checking light %d", i);
            BlockPos result = {x, i, z};
            checkLight(LightLayer::SKY, result, false, false);
            PIXEndNamedEvent();
        }
        PIXEndNamedEvent();
    }
    PIXBeginNamedEvent(0.0f, "Setting blocks dirty");
    BlockPos result = {x, y0, z};
    BlockPos v14 = {x, y1, z};
    setBlocksDirty(result, v14);
    PIXEndNamedEvent();
    PIXEndNamedEvent();
}

void Level::neighborChanged(const BlockPos& pos, Block* block, const BlockPos& neighborPos) {
    if (!m_isLocal) {
        getBlockState(pos)->neighborChanged(this, pos, block, neighborPos);
    }
}

bool Level::isBlockToBeTickedAt(const BlockPos& pos, Block* block) {
    return false;
}

bool Level::canSeeSky(const BlockPos& pos) {
    return getChunkAt(pos)->isSkyLit(pos);
}

bool Level::canSeeSkyFromBelowWater(const BlockPos& pos) {
    if (pos.getY() >= 63)
        return canSeeSky(pos);

    BlockPos curPos = {pos.getX(), 63, pos.getZ()};
    if (!canSeeSky(curPos))
        return false;

    curPos = curPos.below();
    while (curPos.getY() > pos.getY()) {
        const BlockState* blockState = getBlockState(curPos);
        if (blockState->getLightBlock() > 0) {
            if (!blockState->getMaterial()->isLiquid())
                return false;
        }
        curPos = curPos.below();
    }

    return true;
}

int Level::getRawBrightness(const BlockPos& pos) {
    return getRawBrightness(pos, true);
}

int Level::getRawBrightness(const BlockPos& pos, bool unk) {
    if (!isWithinLevelBounds(pos.getX(), pos.getZ()))
        return 15;

    if (unk && getBlockState(pos)->doesPropagate()) {
        int brightness = getRawBrightness(pos.above(), false);
        int brightness2 = getRawBrightness(pos.east(), false);
        int brightness3 = getRawBrightness(pos.west(), false);
        int brightness4 = getRawBrightness(pos.south(), false);
        int brightness5 = getRawBrightness(pos.north(), false);

        if (brightness2 > brightness)
            brightness = brightness2;
        if (brightness3 > brightness)
            brightness = brightness3;
        if (brightness4 > brightness)
            brightness = brightness4;
        if (brightness5 > brightness)
            brightness = brightness5;

        return brightness;
    }

    if (pos.getY() < 0) {
        return 0;
    }

    BlockPos adjustedPos = pos;
    if (pos.getY() >= HEIGHT_LIMIT)
        adjustedPos = BlockPos(pos.getX(), HEIGHT_LIMIT - 1, pos.getZ());

    LevelChunk* chunkAt = getChunkAt(adjustedPos);
    return chunkAt->getRawBrightness(adjustedPos, m_skyDarken);
}

BlockPos Level::getHeightmapPos(const BlockPos& pos) {
    return BlockPos(pos.getX(), getHeightmapHeight(pos.getX(), pos.getZ()), pos.getZ());
}

int Level::getHeightmapHeight(int x, int z) {
    if (!isWithinLevelBounds(x, z))
        return getSeaLevel() + 1;

    if (!hasChunk(x >> 4, z >> 4, true))
        return false;

    LevelChunk* chunk = getChunk(x >> 4, z >> 4);
    return chunk->getHeightmap(x & 0xF, z & 0xF);
}

int Level::getHeightmap(int x, int z) {
    if (!isWithinLevelBounds(x, z))
        return 64;

    if (!hasChunk(x >> 4, z >> 4, true))
        return false;

    LevelChunk* chunk = getChunk(x >> 4, z >> 4);
    return chunk->getHeightmap(x & 0xF, z & 0xF);
}

int Level::getBrightnessPropagate(LightLayer::variety layer, const BlockPos& pos) {
    if (!m_dimension->isHasSkyLight() && layer == LightLayer::variety::SKY) {
        return 0;
    }

    BlockPos adjustedPos = pos;
    if (adjustedPos.getY() < 0) {
        adjustedPos = BlockPos(adjustedPos.getX(), 0, adjustedPos.getZ());
    }

    if (isInWorldBounds(adjustedPos) && hasChunkAt(adjustedPos)) {
        const BlockState* blockState = getBlockState(adjustedPos);
        if (blockState->doesPropagate()) {
            int brightness = getBrightness(layer, adjustedPos.above());
            int brightness2 = getBrightness(layer, adjustedPos.east());
            int brightness3 = getBrightness(layer, adjustedPos.west());
            int brightness4 = getBrightness(layer, adjustedPos.south());
            int brightness5 = getBrightness(layer, adjustedPos.north());

            if (brightness2 > brightness)
                brightness = brightness2;
            if (brightness3 > brightness)
                brightness = brightness3;
            if (brightness4 > brightness)
                brightness = brightness4;
            if (brightness5 > brightness)
                brightness = brightness5;

            return brightness;
        } else {
            return getChunkAt(adjustedPos)->getBrightness(layer, adjustedPos);
        }
    }
    return layer;
}

int Level::getLightColor(const BlockPos& pos, int unk1, int unk2) {
    int sky = getBrightnessPropagate(LightLayer::SKY, pos);
    int block = getBrightnessPropagate(LightLayer::BLOCK, pos);

    if (block < unk1)
        block = unk1;

    return (16 * block) | (sky << 20);
}

float Level::getBrightness(const BlockPos& pos, int brightness) {
    int rawBrightness = getRawBrightness(pos);
    if (rawBrightness >= brightness)
        brightness = rawBrightness;
    return m_dimension->getBrightnessRamp()[brightness];
}

float Level::getBrightness(const BlockPos& pos) {
    return m_dimension->getBrightnessRamp()[getRawBrightness(pos)];
}

int Level::getBlockId(int x, int y, int z) {
    if (!isInWorldBounds(x, y, z))
        return 0;

    LevelChunk* chunk = getChunk(x >> 4, z >> 4);
    return chunk->getBlockId(x & 0xF, y, z & 0xF);
}

Block* Level::getBlock(const BlockPos& pos) {
    return Block::byId(getBlockId(pos.getX(), pos.getY(), pos.getZ()));
}

int Level::getBlockData(int x, int y, int z) {
    if (!isInWorldBounds(x, y, z))
        return 0;

    LevelChunk* chunk = getChunk(x >> 4, z >> 4);
    return chunk->getData(x & 0xF, y, z & 0xF);
}

void Level::playLocalSound(double, double, double, const SoundEvent*, SoundSource::ESoundSource, float, float,
                           bool, float) {}

bool Level::addGlobalEntity(std::shared_ptr<Entity> entity) {
    m_globalEntities.push_back(entity);
    return true;
}

void Level::entityAdded(std::shared_ptr<Entity> entity) {
    for (LevelListener* listener : this->m_levelListeners) {
        listener->entityAdded(entity);
    }
}

void Level::entityRemoved(std::shared_ptr<Entity> entity) {
    for (LevelListener* listener : this->m_levelListeners) {
        listener->entityRemoved(entity);
    }
}

void Level::playerRemoved(std::shared_ptr<Entity> entity) {
    for (LevelListener* listener : this->m_levelListeners) {
        listener->playerRemoved(entity);
    }
}

void Level::addListener(LevelListener* listener) {
    m_levelListeners.push_back(listener);
}

void Level::removeListener(LevelListener* listener) {
    for (auto it = this->m_levelListeners.begin(); it != this->m_levelListeners.end(); it++) {
        if (listener == *it) {
            this->m_levelListeners.erase(it);
            return;
        }
    }
}

bool Level::hasTickNextTick(const BlockPos&, Block*) {
    return true;
}

void Level::addToTickNextTick(const BlockPos&, Block*, int) {}

void Level::addToTickNextTick(const BlockPos&, Block*, int, int) {}

void Level::forceAddBlockTick(const BlockPos&, Block*, int, int) {}

void Level::tickServerPlayers() {}

void Level::tick() {
    PIXBeginNamedEvent(0.0f, "Weather tick");
    tickWeather(false);
    PIXEndNamedEvent();
}

void Level::tickClientSideBlocks(int, int, LevelChunk*) {}

void Level::tickBlocks() {
    buildAndPrepareChunksToPoll();
}

void Level::instaTick(const BlockPos& pos, const BlockState* state, Random& random) {
    setInstaTick(true);
    state->getBlock()->tick(this, pos, state, &random);
    setInstaTick(false);
}

bool Level::tickPendingTicks(bool) {
    return false;
}

std::vector<TickNextTickData*>* Level::fetchTicksInChunk(LevelChunk*, bool) {
    return nullptr;
}

std::vector<TickNextTickData*>* Level::fetchTicksInArea(BoundingBox*, bool) {
    return nullptr;
}

std::shared_ptr<Entity> Level::getEntity(int id) {
    auto it = m_entityIdMap.find(id);
    if (it != m_entityIdMap.end()) {
        return it->second;
    }
    return nullptr;
}

void Level::setSeaLevel(int seaLevel) {
    m_seaLevel = seaLevel;
}

int Level::getDirectSignal(const BlockPos& pos, const Direction* direction) {
    return getBlockState(pos)->getDirectSignal(this, pos, direction);
}

LevelType* Level::getGeneratorType() {
    return m_levelData->getGeneratorType();
}

void Level::disconnect(bool) {}

void Level::checkSession() {
    m_levelStorage->checkSession();
}

long Level::getGameTime() {
    return m_levelData->getGameTime();
}

long Level::getDayTime() {
    return m_levelData->getDayTime();
}

BlockPos Level::getSharedSpawnPos() {
    BlockPos spawnPos = {m_levelData->getXSpawn(), m_levelData->getYSpawn(), m_levelData->getZSpawn()};
    if (!getWorldBorder()->isWithinBounds(spawnPos)) {
        return getHeightmapPos({(int)getWorldBorder()->getCenterX(), 0, (int)getWorldBorder()->getCenterZ()});
    }
    return spawnPos;
}

WorldBorder* Level::getWorldBorder() {
    return m_worldBorder;
}

bool Level::mayInteract(std::shared_ptr<Player>, const BlockPos&, Block*) {
    return true;
}

void Level::broadcastEntityEvent(std::shared_ptr<Entity>, unsigned int, int) {}

ChunkSource* Level::getChunkSource() {
    return m_chunkSource;
}

void Level::updateSleepingPlayerList() {}

bool Level::isRaining() {
    return getRainLevel(1.0f) > 0.2f;
}

bool Level::isHumidAt(const BlockPos& pos) {
    return getBiome(pos)->isHumid();
}

int Level::getMaxBuildHeight() {
    return HEIGHT_LIMIT;
}

int Level::getHeight() {
    if (m_dimension->isUltraWarm())
        return 128;
    else
        return HEIGHT_LIMIT;
}

bool Level::isAllEmpty() {
    return false;
}

void Level::createFireworks(double, double, double, double, double, double, CompoundTag*) {}

int Level::getFogDistance() {
    return m_fogDistance;
}

int Level::getSkyFlashTime() {
    return m_skyFlashTime;
}

void Level::sendPacketToServer(std::shared_ptr<Packet>) {}

void* Level::findNearestMapFeature(const std::wstring&, const BlockPos&, bool) {
    return nullptr;
}

bool Level::AllPlayersAreSleeping() {
    return false;
}

void Level::blockEntityAddedExtra(std::shared_ptr<BlockEntity>) {}

void Level::blockEntityRemovedExtra(std::shared_ptr<BlockEntity>) {}

bool Level::newPrimedTntAllowed() {
    return true;
}

bool Level::newFallingBlockAllowed() {
    return true;
}

bool Level::explodeNextEnderCrystal() {
    return true;
}
