#include "Minecraft.Client/net/minecraft/client/multiplayer/ClientChunkCache.h"
#include "NX/Thread/C4JThreadImpl.h"
#include "net/minecraft/client/Compression.h"
#include "net/minecraft/world/level/Level.h"
#include "net/minecraft/world/level/block/Blocks.h"
#include "net/minecraft/world/level/chunk/storage/OldChunkStorage.h"
#include "net/minecraft/world/level/dimension/Dimension.h"
#include "net/minecraft/world/level/dimension/DimensionType.h"
#include "net/minecraft/world/level/levelgen/ChunkPrimer.h"
#include "net/minecraft/world/level/storage/LevelData.h"

ClientChunkCache::ClientChunkCache(Level* lvl) : m_chunkPos({0, 0}) {
    this->unk3 = nullptr;
    this->m_loadedChunksSize2 = 0;
    this->m_loadedChunksSize1 = 0;
    this->unk11 = nullptr;
    this->unk12 = nullptr;
    this->unk13 = nullptr;
    this->unk14 = nullptr;
    this->unk16 = nullptr;
    this->unk17 = nullptr;
    this->unk18 = nullptr;
    this->unk19 = nullptr;
    this->unk20 = nullptr;
    this->unk21 = nullptr;

    this->MultiPlayerChunkCacheInit(lvl, nullptr);
}

ClientChunkCache::ClientChunkCache(Level* lvl, ChunkStorage* storage) : m_chunkPos({0, 0}) {
    this->unk3 = nullptr;
    this->m_loadedChunksSize2 = 0;
    this->m_loadedChunksSize1 = 0;
    this->unk11 = nullptr;
    this->unk12 = nullptr;
    this->unk13 = nullptr;
    this->unk14 = nullptr;
    this->unk16 = nullptr;
    this->unk17 = nullptr;
    this->unk18 = nullptr;
    this->unk19 = nullptr;
    this->unk20 = nullptr;
    this->unk21 = nullptr;

    MultiPlayerChunkCacheInit(lvl, storage);
}

// I completely missed the branch out to this, only noticed once I tried matching the second constructor
// Wii U Edition didn't do a jumpout, so the symbol and function exists
// NON_MATCHING | Difference: 11775
void ClientChunkCache::MultiPlayerChunkCacheInit(Level *lvl, ChunkStorage *storage) {
    int bounds;

    int xzSize = lvl->mDimension->getXZSize();
    if (xzSize >= 0)
        bounds = xzSize;
    else
        bounds = xzSize + 1;

    this->m_xzBounds = xzSize;
    this->m_xzCenter = bounds >> 1;
    this->m_xzSize = xzSize;

    this->unk28 = new char[this->m_xzBounds * this->m_xzBounds];
    memset(this->unk28, 0, this->m_xzBounds * this->m_xzBounds);

    this->m_emptyChunk = new EmptyLevelChunk(lvl, 0, 0);
    this->m_chunkStorage = storage;
    this->unk4 = 0;

    // is there a way to force IDA to show jumpouts instead of just hiding code from me
    if (storage) {
        InitializeCriticalSection(&this->m_storageMutex);
        this->m_storageThread = new C4JThreadImpl(StorageThreadProc, this, "MultiPlayerChunkCache", 0x100000);
        this->m_storageThread->SetProcessor(1);
        this->m_storageThread->Run();
    } else {
        this->m_storageThread = nullptr;
    }

    // If overworld
    if (lvl->mDimension->getType() == DimensionType::OVERWORLD) {
        arrayWithLength<unsigned char> blocks = arrayWithLength<unsigned char>(0x8000u, true);
        arrayWithLength<unsigned char> data = arrayWithLength<unsigned char>(0x4000u, true);

        LevelData* dat = lvl->getLevelData();
        // If overworld is superflat
        if (dat->getGeneratorType() == LevelType::FLAT) {
            // from 0 to 16 chunk coords x
            for (int x = 0; x != 16; x++) {
                // from 0 to 128 chunk coords y (old height limit)
                for (int y = 0; y != 128; y++) {
                    // if y is 3, which is the grass layer height on a superflat world
                    if (y == 3) {
                        // from 0 to 16 chunk coords z
                        for (int z = 0; z != 16; z++) {
                            blocks[INDEX_BLOCK_ARRAY(x, y, z)] = Blocks::GRASS->getId();  // place a grass block
                        }
                    } else if (y > 2) {
                        // if y is larger than 2, but not 3, we are above the topmost layer of
                        // the superflat world

                        // from 0 to 16 chunk coords z
                        for (int z = 0; z != 16; z++) {
                            blocks[INDEX_BLOCK_ARRAY(x, y, z)] = 0;  // place an air block
                        }
                    } else {
                        // otherwise, y is below the grass layer

                        // from 0 to 16 chunk coords z
                        for (int z = 0; z != 16; z++) {
                            blocks[INDEX_BLOCK_ARRAY(x, y, z)] = Blocks::DIRT->getId();  // place a dirt block
                        }
                    }
                }
            }
        } else {  // otherwise, we're in a normal generator (e.g. Default, Large Biomes)
            for (int x = 0; x != 16; x++)  // from 0 to 16 chunk coords z
            {
                for (int y = 0; y != 128; y++)  // from 0 to 128 chunk coords y (old height limit)
                {
                    for (int z = 0; z != 16; z++)  // from 0 to 16 chunk coords x
                    {
                        int sl = lvl->getSeaLevel();  // get sea level
                        int id;

                        // TODO can't get this to look neat without mismatching
                        Block* blk = Blocks::STONE;  // default block is stone

                        // if we are above 10 blocks below sea level, set the block to water, then check if y
                        // is higher than sea level if it is, we will fall through to set ID to 0, which is
                        // AIR otherwise, blk is now water, so we will fall through and get the ID of our
                        // water block
                        if (y > sl - 10 && (blk = Blocks::WATER, y >= sl))
                            id = 0;  // set block to air
                        else
                            id = blk->getId();  // set block to Water, if between sea level and 10 blocks
                                                // below sea level, otherwise Stone.

                        blocks[INDEX_BLOCK_ARRAY(x, y, z)] = id;  // set the ID in the array
                    }
                }
            }
        }

        ChunkPrimer primer = ChunkPrimer(false, blocks, data);
        this->m_waterChunk = new WaterLevelChunk(lvl, &primer, 0, 0);

        delete blocks.data;
        delete data.data;

        // sets skylight
        if (dat->getGeneratorType() == LevelType::FLAT) {
            for (int x = 0; x != 16; x++) {       // from 0 to 16 chunk coords x
                for (int y = 0; y != 128; y++) {  // from 0 to 128 chunk coords y (old world height)
                    if (y >= 3) {  // if y is bigger or equal to 3, which is any block at or above the top block
                        for (int z = 0; z != 16; z++) {  // from 0 to 16 chunk coords z
                            m_waterChunk->setLevelChunkBrightness(LightLayer::SKY, x, y, z,
                                                                  15);  // set light level to 15
                        }
                    }
                }
            }
        } else {
            for (int x = 0; x != 16; x++) {          // from 0 to 16 chunk coords x
                for (int y = 0; y != 128; y++) {     // from 0 to 128 chunk coords y (old world height)
                    for (int z = 0; z != 16; z++) {  // from 0 to 16 chunk coords z
                        int brightness = 2;          // underwater/in-block brightness

                        if (y >= lvl->getSeaLevel() - 1)  // if we are above the sea level minus 1
                            brightness = 15;              // set our brightness to max, as this is skylight

                        m_waterChunk->setLevelChunkBrightness(LightLayer::SKY, x, y, z,
                                                              brightness);  // set the brightness
                    }
                }
            }
        }
    } else {
        this->m_waterChunk = nullptr;  // no need for a water chunk when not in the overworld
    }

    this->m_level = lvl;
    this->m_dimension = lvl->mDimension;

    // apparently correct? difference went down after
    this->m_cache = new LevelChunk*[(this->m_xzBounds * this->m_xzBounds)];
    memset(this->m_cache, 0, sizeof(LevelChunk*) * (this->m_xzBounds * this->m_xzBounds));

    InitializeCriticalSectionAndSpinCount(&this->m_mutex, 0);
}

LevelChunk* ClientChunkCache::getChunkIfLoaded(int x, int z) {
    // this better be a fucking decompiler moment
    // I can't get any sensible variation of this function to match,
    // but I can get this monstrosity to match...
    // this code makes me want to violently throw up all over my keyboard

    // I seriously hope that I just haven't tried enough ways, and that this was implemented in a somewhat sound way.

    LevelChunk **c; // pointer to pointer to chunk
    if (inBounds(x, z)) { // if xz in bounds
        const int idx = computeIdx(x, z); // get idx (must be separate var???)

        c = m_cache + idx; // set to chunk in cache at idx
    } else if (!this->m_waterChunk) { // otherwise, if we don't have a water chunk
        c = reinterpret_cast<LevelChunk**>(&this->m_waterChunk) - 1; // it falls into m_chunkStorage, and sets it to that, what the fuck!?!?!?
    } else { // otherwise, if we have a water chunk
        c = reinterpret_cast<LevelChunk**>(&this->m_waterChunk); // set to water chunk
    }

    return *c; // deref and return
}

LevelChunk* ClientChunkCache::getOrCreateChunk(int x, int z, bool unk) {
    LevelChunk *c = this->getChunkIfLoaded(x, z); // get chunk
    if (!c) // if null, return empty chunk inst
        return this->m_emptyChunk;

    return c; // return chunk otherwise since not null
}

std::wstring ClientChunkCache::gatherStats() {
    EnterCriticalSection(&this->m_mutex);
    const int u = (this->m_loadedChunksSize1 - this->m_loadedChunksSize2) >> 3; // maybe this is some vector or map?
    LeaveCriticalSection(&this->m_mutex);

    return L"MultiplayerChunkCache: " + std::to_wstring(u);
}

int ClientChunkCache::getLoadedChunksCount() {
    return 0;
}

bool ClientChunkCache::isChunkGeneratedAt(int x, int z) {
    return false;
}

bool ClientChunkCache::hasChunk(int x, int z) {
    return true;
}
bool ClientChunkCache::reallyHasChunk(int x, int z) {
    if (!inBounds(x, z))
        return true; // if out of bounds, it returns true because the client will then fetch a WaterLevelChunk

    int idx = computeIdx(x, z);
    if (this->m_cache[idx])
        return this->unk28[idx] != 0;

    return false;
}

LevelChunk* ClientChunkCache::getChunk(int x, int z) {
    // Remember the comment at getChunkIfLoaded? Yeah, I wrote that when I didn't think it could get any worse...
    // It got Worse.

    LevelChunk **c; // pointer to pointer to chunk
    if (inBounds(x, z)) { // if xz in bounds
        const int idx = computeIdx(x, z); // get idx (must be separate var???)

        LevelChunk *h = m_cache[idx]; // set to chunk in cache at idx
        if (h)
            return h; // return chunk

        c = reinterpret_cast<LevelChunk**>(&this->m_emptyChunk); //return empty chunk
    } else if (!this->m_waterChunk) { // otherwise, if we don't have a water chunk
        c = reinterpret_cast<LevelChunk**>(&this->m_waterChunk) - 1; // it falls into m_chunkStorage, and sets it to that, what the fuck!?!?!?
    } else { // otherwise, if we have a water chunk
        c = reinterpret_cast<LevelChunk**>(&this->m_waterChunk); // set to water chunk
    }

    return *c; // deref and return
}

LevelChunk* ClientChunkCache::getChunkAt(const BlockPos& pos) {
    return getChunk(pos.getX(), pos.getZ());
}

bool ClientChunkCache::save(bool, ProgressListener*) {
    return true;
}

bool ClientChunkCache::shouldSave() {
    return false;
}

LevelChunk** ClientChunkCache::getCache() {
    return this->m_cache;
}

std::vector<Biome::MobSpawnerData>* ClientChunkCache::getMobsAt(MobCategory* category, const BlockPos& pos) {
    return nullptr;
}

BlockPos* ClientChunkCache::findNearestMapFeature(Level*, const std::wstring&, const BlockPos&, bool) {
    return nullptr;
}

int ClientChunkCache::getLoadedChunks() {
    return (this->m_loadedChunksSize1 - this->m_loadedChunksSize2) >> 3;
}

void ClientChunkCache::recreateLogicStructuresForChunk(LevelChunk*, int, int) {}

// why the fuck does this return int
int ClientChunkCache::inBounds(int x, int z) {
    return this->m_dimension->containsChunk(x, z);
}

int ClientChunkCache::computeIdx(int x, int z) {
    return (this->m_xzCenter + x) * this->m_xzBounds + (this->m_xzCenter + z);
}

// NON_MATCHING | Difference: 4252
int ClientChunkCache::StorageThreadProc(void*) {
    Compression::UseDefaultThreadStorage();
    OldChunkStorage::UseDefaultThreadStorage();
    AABB::CreateNewThreadStorage();
    Vec3::CreateNewThreadStorage();
}
