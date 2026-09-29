#include "Minecraft.World/net/minecraft/world/level/chunk/WaterLevelChunk.h"
#include "net/minecraft/core/BlockPos.h"
#include "net/minecraft/world/Random.h"
#include "net/minecraft/world/level/Level.h"

WaterLevelChunk::WaterLevelChunk(Level* lvl, ChunkPrimer* primer, int x, int z)
    : LevelChunk(lvl, primer, x, z) {
    this->unk6 = true;  // if I had to guess, it's m_populated
    this->m_populatedFlags = 0b0000011111111110;
}

void WaterLevelChunk::reSyncLighting() {}
void WaterLevelChunk::dropLighting() {}
void WaterLevelChunk::recalcBlockLights() {}
void WaterLevelChunk::recalcHeightmapOnly() {}
void WaterLevelChunk::recalcHeightmap() {}
void WaterLevelChunk::lightLava() {}
bool WaterLevelChunk::setData(int i, int i1, int i2, int i3, int i4, bool* p) {
    *p = true;
    return true;
}

const BlockState* WaterLevelChunk::setBlock(const BlockPos& pos, const BlockState* state) {
    return state;
}
bool WaterLevelChunk::setBlockAndData(int i, int i1, int i2, int i3, int i4, bool cond) {
    return true;
}
void WaterLevelChunk::setBrightness(LightLayer::variety variety, const BlockPos& block_pos, int i) {}
void WaterLevelChunk::addEntity(std::shared_ptr<Entity> entity) {}
void WaterLevelChunk::removeEntity(std::shared_ptr<Entity> entity) {}
void WaterLevelChunk::removeEntity(std::shared_ptr<Entity> entity, int i) {}
std::shared_ptr<BlockEntity> WaterLevelChunk::getBlockEntity(const BlockPos& block_pos,
                                                             LevelChunk::EntityCreationType entity_creation) {
    return nullptr;
}
void WaterLevelChunk::addBlockEntity(std::shared_ptr<BlockEntity> block_entity) {}
void WaterLevelChunk::setBlockEntity(const BlockPos& block_pos, std::shared_ptr<BlockEntity> block_entity) {}
void WaterLevelChunk::removeBlockEntity(const BlockPos& block_pos) {}
void WaterLevelChunk::load(bool cond) {}
void WaterLevelChunk::unload(bool cond, bool cond1) {}
bool WaterLevelChunk::containsPlayer() {
    return false;
}

void WaterLevelChunk::markUnsaved() {}
void WaterLevelChunk::getEntities(std::shared_ptr<Entity> entity, AABB const* aabb,
                                  std::vector<std::shared_ptr<Entity>>& shared_ptrs,
                                  const Predicate<std::shared_ptr<Entity>>* predicate) {}
void WaterLevelChunk::getEntitiesOfClass(const std::type_info& type_info, AABB const* aabb,
                                         std::vector<std::shared_ptr<Entity>>& shared_ptrs,
                                         const Predicate<std::shared_ptr<Entity>>* predicate, bool cond) {}
int WaterLevelChunk::countEntities() {
    return 0;
}

bool WaterLevelChunk::shouldSave(bool) {
    return false;
}

bool WaterLevelChunk::testSetBlocksAndData(arrayWithLength<unsigned char> array_with_length, int i, int i1,
                                           int i2, int i3, int i4, int i5, int i6) {
    return false;
}

// NON_MATCHING | Difference: 795
Random* WaterLevelChunk::getRandom(long long i) {
    return new Random((this->m_level->getSeed() + 0x5AC0DB * this->mXPos
                       + 0x4C1906LL * (this->mXPos * this->mXPos) + 0x5F24F * this->mZPos
                       + 0x4307A7LL * (this->mZPos * this->mZPos))
                      ^ i);
}

Biome* WaterLevelChunk::getBiome(const BlockPos& block_pos, BiomeSource* biome_source) {
    return Biome::getBiome(Biome::EBiomeIDs::BiomeID_OCEAN);
}

void WaterLevelChunk::setLevelChunkBrightness(LightLayer::variety variety, int x, int y, int z,
                                              int brightness) {
    LevelChunk::setBrightness(variety, BlockPos(x, y, z), brightness);
}
