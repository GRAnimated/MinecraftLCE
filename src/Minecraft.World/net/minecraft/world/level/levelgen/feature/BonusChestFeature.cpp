#include "net/minecraft/world/level/levelgen/feature/BonusChestFeature.h"

#include "net/minecraft/core/BlockPos.h"
#include "net/minecraft/world/Random.h"
#include "net/minecraft/world/level/Level.h"
#include "net/minecraft/world/level/block/Block.h"
#include "net/minecraft/world/level/block/Blocks.h"
#include "net/minecraft/world/level/block/entity/ChestBlockEntity.h"
#include "net/minecraft/world/level/block/state/BlockState.h"
#include "net/minecraft/world/level/material/Material.h"
#include "net/minecraft/world/level/storage/loot/BuiltInLootTables.h"

BonusChestFeature::BonusChestFeature() : Feature(false) {}

bool BonusChestFeature::place(Level* level, Random& random, const BlockPos& pos) {
    return place(level, random, pos, false);
}

bool BonusChestFeature::place(Level* level, Random& random, const BlockPos& pos, bool fixedPosition) {
    BlockPos origin = pos;
    if (!fixedPosition) {
        const BlockState* state = level->getBlockState(origin);
        while ((state->getMaterial() == Material::AIR || state->getMaterial() == Material::LEAVES)
               && origin.getY() > 1) {
            origin = origin.below();
            state = level->getBlockState(origin);
        }
        if (origin.getY() < 1)
            return false;
        origin = origin.above();
    }
    for (int attempt = 0; attempt < 4; ++attempt) {
        BlockPos candidate(0, 0, 0);
        if (fixedPosition)
            candidate = origin.offset(0, -1, 0);
        else
            candidate
                = origin.offset(random.nextInt(4) - random.nextInt(4), random.nextInt(3) - random.nextInt(3),
                                random.nextInt(4) - random.nextInt(4));
        if (!level->isEmptyBlock(candidate) || !level->getBlockState(candidate.below())->isTopSolidBlocking())
            continue;
        level->setBlock(candidate, Blocks::CHEST->defaultBlockState(), 2, false);
        std::shared_ptr<BlockEntity> entity = level->getBlockEntity(candidate);
        if (entity->isType(eChestBlockEntity)) {
            auto chest = std::dynamic_pointer_cast<ChestBlockEntity>(entity);
            if (chest) {
                chest->setLootTable(&BuiltInLootTables::SPAWN_BONUS_CHEST, random.nextLong());
                chest->m_isBonusChest = true;
            }
        }
        BlockPos east = candidate.east();
        BlockPos west = candidate.west();
        BlockPos north = candidate.north();
        BlockPos south = candidate.south();
        if (level->isEmptyBlock(west) && level->getBlockState(west.below())->isTopSolidBlocking())
            level->setBlock(west, Blocks::TORCH->defaultBlockState(), 2, false);
        if (level->isEmptyBlock(east) && level->getBlockState(east.below())->isTopSolidBlocking())
            level->setBlock(east, Blocks::TORCH->defaultBlockState(), 2, false);
        if (level->isEmptyBlock(north) && level->getBlockState(north.below())->isTopSolidBlocking())
            level->setBlock(north, Blocks::TORCH->defaultBlockState(), 2, false);
        if (level->isEmptyBlock(south) && level->getBlockState(south.below())->isTopSolidBlocking())
            level->setBlock(south, Blocks::TORCH->defaultBlockState(), 2, false);
        return true;
    }
    return false;
}
