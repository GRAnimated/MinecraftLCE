#pragma once

#include "net/minecraft/world/level/block/entity/BlockEntity.h"

class BaseMobSpawner;

class MobSpawnerBlockEntity : public BlockEntity {
public:
    BaseMobSpawner* getSpawner();

private:
    BaseMobSpawner* m_spawner;
};
