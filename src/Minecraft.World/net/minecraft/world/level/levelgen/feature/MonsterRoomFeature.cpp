#include "net/minecraft/world/level/levelgen/feature/MonsterRoomFeature.h"

#include "net/minecraft/core/BlockPos.h"
#include "net/minecraft/core/Direction.h"
#include "net/minecraft/resources/ResourceLocation.h"
#include "net/minecraft/world/Random.h"
#include "net/minecraft/world/entity/EntityIO.h"
#include "net/minecraft/world/level/BaseMobSpawner.h"
#include "net/minecraft/world/level/Level.h"
#include "net/minecraft/world/level/block/Blocks.h"
#include "net/minecraft/world/level/block/ChestBlock.h"
#include "net/minecraft/world/level/block/entity/MobSpawnerBlockEntity.h"
#include "net/minecraft/world/level/block/entity/RandomizableLockableContainerBlockEntity.h"
#include "net/minecraft/world/level/block/state/BlockState.h"
#include "net/minecraft/world/level/material/Material.h"
#include "net/minecraft/world/level/storage/loot/BuiltInLootTables.h"

// name guessed
MonsterRoomFeature::MonsterRoomFeature() : Feature(false) {}

// NON_MATCHING | score: 8414 (lower is better)
bool MonsterRoomFeature::place(Level* level, Random& random, const BlockPos& pos) {
    int radiusX = random.nextInt(2) + 2;
    int radiusZ = random.nextInt(2) + 2;
    int openings = 0;
    for (int x = -radiusX - 1; x <= radiusX + 1; ++x) {
        for (int y = -1; y <= 4; ++y) {
            for (int z = -radiusZ - 1; z <= radiusZ + 1; ++z) {
                BlockPos candidate = pos.offset(x, y, z);
                bool solid = level->getBlockState(candidate)->getMaterial()->isSolid();
                if (y == -1 && !solid)
                    return false;
                if (y == 4 && !solid)
                    return false;
                if ((x == -radiusX - 1 || x == radiusX + 1 || z == -radiusZ - 1 || z == radiusZ + 1) && y == 0
                    && level->isEmptyBlock(candidate) && level->isEmptyBlock(candidate.above()))
                    ++openings;
            }
        }
    }
    if (openings < 1 || openings > 5)
        return false;
    for (int x = -radiusX - 1; x <= radiusX + 1; ++x) {
        for (int y = 3; y >= -1; --y) {
            for (int z = -radiusZ - 1; z <= radiusZ + 1; ++z) {
                BlockPos candidate = pos.offset(x, y, z);
                if (x == -radiusX - 1 || y == -1 || z == -radiusZ - 1 || x == radiusX + 1
                    || z == radiusZ + 1) {
                    if (candidate.getY() >= 0
                        && !level->getBlockState(candidate.below())->getMaterial()->isSolid()) {
                        level->removeBlock(candidate);
                    } else if (level->getBlockState(candidate)->getMaterial()->isSolid()
                               && level->getBlockState(candidate)->getBlock() != Blocks::CHEST) {
                        if (y == -1 && random.nextInt(4) != 0)
                            level->setBlock(candidate, Blocks::MOSSY_COBBLESTONE->defaultBlockState(), 2,
                                            false);
                        else
                            level->setBlock(candidate, Blocks::COBBLESTONE->defaultBlockState(), 2, false);
                    }
                } else if (level->getBlockState(candidate)->getBlock() != Blocks::CHEST) {
                    level->removeBlock(candidate);
                }
            }
        }
    }
    for (int chest = 0; chest < 2; ++chest) {
        for (int attempt = 0; attempt < 3; ++attempt) {
            BlockPos candidate(pos.getX() + random.nextInt(radiusX * 2 + 1) - radiusX, pos.getY(),
                               pos.getZ() + random.nextInt(radiusZ * 2 + 1) - radiusZ);
            if (!level->isEmptyBlock(candidate))
                continue;
            int walls = 0;
            arrayWithLength<const Direction*> directions = Direction::Plane::HORIZONTAL->iterator();
            for (unsigned int i = 0; i < directions.m_length; ++i) {
                if (level->getBlockState(candidate.relative(directions.get(i)))->getMaterial()->isSolid())
                    ++walls;
            }
            if (walls == 1) {
                ChestBlock* chestBlock = static_cast<ChestBlock*>(Blocks::CHEST);
                level->setBlock(candidate,
                                chestBlock->reorient(level, candidate, chestBlock->defaultBlockState()), 2,
                                false);
                std::shared_ptr<BlockEntity> entity = level->getBlockEntity(candidate);
                if (entity->isType(eChestBlockEntity)) {
                    auto container
                        = std::static_pointer_cast<RandomizableLockableContainerBlockEntity>(entity);
                    container->setLootTable(&BuiltInLootTables::SIMPLE_DUNGEON, random.nextLong());
                }
                break;
            }
        }
    }
    level->setBlock(pos, Blocks::MOB_SPAWNER->defaultBlockState(), 2, false);
    std::shared_ptr<BlockEntity> entity = level->getBlockEntity(pos);
    if (entity->isType(eMobSpawnerBlockEntity)) {
        auto spawner = std::static_pointer_cast<MobSpawnerBlockEntity>(entity);
        spawner->getSpawner()->setEntityId(ResourceLocation(randomEntityId(random)));
    }
    return true;
}

// name guessed
// NON_MATCHING | score: 1142 (lower is better)
std::wstring MonsterRoomFeature::randomEntityId(Random& random) {
    static std::wstring types[]
        = {EntityIO::getKey(eSkeleton).toString(), EntityIO::getKey(eZombie).toString(),
           EntityIO::getKey(eZombie).toString(), EntityIO::getKey(eSpider).toString()};
    return types[random.nextInt(4)];
}
