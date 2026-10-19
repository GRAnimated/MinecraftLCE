#include "net/minecraft/world/level/levelgen/feature/RoofTreeFeature.h"

#include "NX/Platform.h"
#include "net/minecraft/core/Direction.h"
#include "net/minecraft/core/MutableBlockPos.h"
#include "net/minecraft/world/Random.h"
#include "net/minecraft/world/level/Level.h"
#include "net/minecraft/world/level/block/Blocks.h"
#include "net/minecraft/world/level/block/NewLeafBlock.h"
#include "net/minecraft/world/level/block/NewLogBlock.h"
#include "net/minecraft/world/level/material/Material.h"
#include <cstdlib>

const BlockState* RoofTreeFeature::TRUNK;  // name guessed
const BlockState* RoofTreeFeature::LEAVES;

void RoofTreeFeature::staticCtor() {
    TRUNK = Blocks::LOG2->defaultBlockState()->setValue(NewLogBlock::VARIANT, PlanksBlock::Variant::DARK_OAK);
    LEAVES = Blocks::LEAVES2->defaultBlockState()
                 ->setValue(NewLeafBlock::VARIANT, PlanksBlock::Variant::DARK_OAK)
                 ->setValue(LeafBlock::CHECK_DECAY, false);
}

// name guessed
RoofTreeFeature::RoofTreeFeature(bool update) : AbstractTreeFeature(update, 6, TRUNK, LEAVES, false) {}
RoofTreeFeature::~RoofTreeFeature() = default;

// name guessed
bool RoofTreeFeature::canPlaceTreeOfHeight(Level* level, const BlockPos& pos, int height) {
    int x = pos.getX();
    int y = pos.getY();
    int z = pos.getZ();
    BlockPos candidate;
    for (int dy = 0; dy <= height + 1; ++dy) {
        int radius = dy == 0 ? 0 : 1;
        if (dy >= height - 1)
            radius = 2;
        for (int dx = -radius; dx <= radius; ++dx) {
            for (int dz = -radius; dz <= radius; ++dz) {
                candidate = BlockPos(x + dx, y + dy, z + dz);
                if (!isFree(level->getBlockState(candidate)->getBlock()))
                    return false;
            }
        }
    }
    return true;
}

// name guessed
void RoofTreeFeature::placeLogAt(Level* level, const BlockPos& pos) {
    if (isFree(level->getBlockState(pos)->getBlock()))
        setBlock(level, pos, m_trunk);
}

// name guessed
void RoofTreeFeature::placeLeafAt(Level* level, int x, int y, int z) {
    BlockPos pos(x, y, z);
    if (level->getBlockState(pos)->getMaterial() == Material::AIR)
        setBlock(level, pos, m_leaves);
}

// name guessed
// NON_MATCHING | score: 18451 (lower is better)
bool RoofTreeFeature::place(Level* level, Random& random, const BlockPos& pos) {
    PIXBeginNamedEvent(0, "RoofTreeFeature::place");
    int height = random.nextInt(3) + random.nextInt(2) + m_minHeight;
    int originX = pos.getX();
    int originY = pos.getY();
    int originZ = pos.getZ();
    if (originY <= 0 || originY + height >= 256) {
        PIXEndNamedEvent();
        return false;
    }
    BlockPos below = pos.below();
    Block* ground = level->getBlockState(below)->getBlock();
    if ((ground != Blocks::GRASS && ground != Blocks::DIRT) || pos.getY() >= 255 - height
        || !canPlaceTreeOfHeight(level, pos, height)) {
        PIXEndNamedEvent();
        return false;
    }
    setDirtAt(level, below);
    setDirtAt(level, below.east());
    setDirtAt(level, below.south());
    setDirtAt(level, below.south().east());
    const Direction* direction = Direction::Plane::HORIZONTAL->getRandomDirection(random);
    int bendStart = height - random.nextInt(4);
    int bendLength = 2 - random.nextInt(3);
    int trunkX = originX;
    int trunkZ = originZ;
    int top = originY + height - 1;
    MutableBlockPos candidate(0, 0, 0);
    for (int y = 0; y < height; ++y) {
        if (y >= bendStart && bendLength > 0) {
            trunkX += direction->getX();
            trunkZ += direction->getZ();
            --bendLength;
        }
        int worldY = pos.getY() + y;
        candidate.set(trunkX, worldY, trunkZ);
        Material* material = level->getBlockState(candidate)->getMaterial();
        if (material == Material::AIR || material == Material::LEAVES) {
            placeLogAt(level, candidate);
            placeLogAt(level, candidate.east());
            placeLogAt(level, candidate.south());
            placeLogAt(level, candidate.east().south());
            top = worldY;
        }
    }
    for (int dx = -2; dx <= 0; ++dx) {
        for (int dz = -2; dz <= 0; ++dz) {
            placeLeafAt(level, trunkX + dx, top - 1, trunkZ + dz);
            placeLeafAt(level, trunkX + 1 - dx, top - 1, trunkZ + dz);
            placeLeafAt(level, trunkX + dx, top - 1, trunkZ + 1 - dz);
            placeLeafAt(level, trunkX + 1 - dx, top - 1, trunkZ + 1 - dz);
            if ((dx > -2 || dz > -1) && (dx != -1 || dz != -2)) {
                placeLeafAt(level, trunkX + dx, top + 1, trunkZ + dz);
                placeLeafAt(level, trunkX + 1 - dx, top + 1, trunkZ + dz);
                placeLeafAt(level, trunkX + dx, top + 1, trunkZ + 1 - dz);
                placeLeafAt(level, trunkX + 1 - dx, top + 1, trunkZ + 1 - dz);
            }
        }
    }
    if (random.nextBoolean()) {
        placeLeafAt(level, trunkX, top + 2, trunkZ);
        placeLeafAt(level, trunkX + 1, top + 2, trunkZ);
        placeLeafAt(level, trunkX + 1, top + 2, trunkZ + 1);
        placeLeafAt(level, trunkX, top + 2, trunkZ + 1);
    }
    for (int dx = -3; dx <= 4; ++dx) {
        for (int dz = -3; dz <= 4; ++dz) {
            if ((dx != -3 || dz != -3) && (dx != -3 || dz != 4) && (dx != 4 || dz != -3)
                && (dx != 4 || dz != 4) && (std::abs(dx) < 3 || std::abs(dz) < 3))
                placeLeafAt(level, trunkX + dx, top, trunkZ + dz);
        }
    }
    for (int dx = -1; dx <= 2; ++dx) {
        for (int dz = -1; dz <= 2; ++dz) {
            if ((dx < 0 || dx > 1 || dz < 0 || dz > 1) && random.nextInt(3) == 0) {
                int length = random.nextInt(3) + 2;
                for (int dy = 0; dy < length; ++dy) {
                    BlockPos branch(originX + dx, top - 1 - dy, originZ + dz);
                    placeLogAt(level, branch);
                }
                for (int x = -1; x <= 1; ++x)
                    for (int z = -1; z <= 1; ++z)
                        placeLeafAt(level, trunkX + dx + x, top, trunkZ + dz + z);
                for (int x = -2; x <= 2; ++x)
                    for (int z = -2; z <= 2; ++z)
                        if (std::abs(x) != 2 || std::abs(z) != 2)
                            placeLeafAt(level, trunkX + dx + x, top - 1, trunkZ + dz + z);
            }
        }
    }
    PIXEndNamedEvent();
    return true;
}
