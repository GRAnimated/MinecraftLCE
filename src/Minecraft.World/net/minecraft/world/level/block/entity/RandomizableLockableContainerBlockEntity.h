#pragma once

#include "net/minecraft/world/level/block/entity/LockableContainerBlockEntity.h"

class ResourceLocation;

class RandomizableLockableContainerBlockEntity : public LockableContainerBlockEntity {
public:
    void setLootTable(ResourceLocation*, long long seed);

private:
    char m_unknown50[8];
    ResourceLocation* m_lootTable;
    long long m_lootTableSeed;
};

ASSERT_SIZEOF(RandomizableLockableContainerBlockEntity, 0x68)
