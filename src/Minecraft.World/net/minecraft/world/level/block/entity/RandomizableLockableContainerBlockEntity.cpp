#include "net/minecraft/world/level/block/entity/RandomizableLockableContainerBlockEntity.h"

void RandomizableLockableContainerBlockEntity::setLootTable(ResourceLocation* table, long long seed) {
    m_lootTable = table;
    m_lootTableSeed = seed;
}
