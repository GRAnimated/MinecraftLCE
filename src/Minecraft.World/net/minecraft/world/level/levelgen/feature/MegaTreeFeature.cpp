#include "net/minecraft/world/level/levelgen/feature/MegaTreeFeature.h"

#include "net/minecraft/core/BlockPos.h"
#include "net/minecraft/world/Random.h"
#include "net/minecraft/world/level/Level.h"
#include "net/minecraft/world/level/block/Blocks.h"
#include "net/minecraft/world/level/material/Material.h"

MegaTreeFeature::MegaTreeFeature(bool update, int minHeight, int heightRange, const BlockState* trunk,
                                 const BlockState* leaves)
    : AbstractTreeFeature(update, minHeight, trunk, leaves, false), m_heightRange(heightRange) {}

int MegaTreeFeature::calcTreeHeigth(Random& random) {
    int height = random.nextInt(3) + m_minHeight;
    if (m_heightRange > 1)
        height += random.nextInt(m_heightRange);
    return height;
}

bool MegaTreeFeature::checkIsFree(Level* level, const BlockPos& pos, int height) {
    if (pos.getY() < 1 || pos.getY() + height > 255)
        return false;
    bool free = true;
    for (int y = 0; y <= height + 1; ++y) {
        int radius = y == 0 ? 1 : 2;
        for (int x = -radius; x <= radius && free; ++x) {
            for (int z = -radius; z <= radius && free; ++z) {
                if (pos.getY() + y < 0 || pos.getY() + y > 255)
                    free = false;
                else
                    free = isFree(level->getBlockState(pos.offset(x, y, z))->getBlock());
            }
        }
    }
    return free;
}

bool MegaTreeFeature::makeDirtFloor(const BlockPos& pos, Level* level) {
    BlockPos below = pos.below();
    Block* ground = level->getBlockState(below)->getBlock();
    if ((ground != Blocks::GRASS && ground != Blocks::DIRT) || pos.getY() <= 1)
        return false;
    setDirtAt(level, below);
    setDirtAt(level, below.east());
    setDirtAt(level, below.south());
    setDirtAt(level, below.south().east());
    return true;
}

bool MegaTreeFeature::prepareTree(Level* level, Random&, const BlockPos& pos, int height) {
    if (checkIsFree(level, pos, height))
        return makeDirtFloor(pos, level);
    return false;
}

void MegaTreeFeature::placeDoubleTrunkLeaves(Level* level, const BlockPos& pos, int radius) {
    int squared = radius * radius;
    for (int x = -radius; x <= radius + 1; ++x) {
        for (int z = -radius; z <= radius + 1; ++z) {
            int dx = x - 1;
            int dz = z - 1;
            if (x * x + z * z <= squared || dx * dx + z * z <= squared || dx * dx + dz * dz <= squared
                || x * x + dz * dz <= squared) {
                BlockPos candidate = pos.offset(x, 0, z);
                Material* material = level->getBlockState(candidate)->getMaterial();
                if (material == Material::AIR || material == Material::LEAVES)
                    setBlock(level, candidate, m_leaves);
            }
        }
    }
}

void MegaTreeFeature::placeSingleTrunkLeaves(Level* level, const BlockPos& pos, int radius) {
    for (int x = -radius; x <= radius; ++x) {
        for (int z = -radius; z <= radius; ++z) {
            if (x * x + z * z <= radius * radius) {
                BlockPos candidate = pos.offset(x, 0, z);
                Material* material = level->getBlockState(candidate)->getMaterial();
                if (material == Material::AIR || material == Material::LEAVES)
                    setBlock(level, candidate, m_leaves);
            }
        }
    }
}
