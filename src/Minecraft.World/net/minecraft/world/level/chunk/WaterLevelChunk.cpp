#include "Minecraft.World/net/minecraft/world/level/chunk/WaterLevelChunk.h"

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

const BlockState* WaterLevelChunk::setBlock(const BlockPos& block_pos, const BlockState* block_state) {
    return block_state;
}
bool WaterLevelChunk::setBlockAndData(int i, int i1, int i2, int i3, int i4, bool cond) {
    return true;
}
void WaterLevelChunk::setBrightness(LightLayer::variety variety, const BlockPos& block_pos, int i) {}
void WaterLevelChunk::addEntity(std::shared_ptr<Entity> entity) {}
void WaterLevelChunk::removeEntity(std::shared_ptr<Entity> entity) {}
void WaterLevelChunk::removeEntity(std::shared_ptr<Entity> entity, int i) {}
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