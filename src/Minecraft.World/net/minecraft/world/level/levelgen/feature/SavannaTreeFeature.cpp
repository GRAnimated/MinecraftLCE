#include "net/minecraft/world/level/levelgen/feature/SavannaTreeFeature.h"

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

const BlockState* SavannaTreeFeature::TRUNK;  // name guessed
const BlockState* SavannaTreeFeature::LEAVES;

void SavannaTreeFeature::staticCtor() {
    TRUNK = Blocks::LOG2->defaultBlockState()->setValue(NewLogBlock::VARIANT, PlanksBlock::Variant::ACACIA);
    LEAVES = Blocks::LEAVES2->defaultBlockState()
                 ->setValue(NewLeafBlock::VARIANT, PlanksBlock::Variant::ACACIA)
                 ->setValue(LeafBlock::CHECK_DECAY, false);
}

// name guessed
SavannaTreeFeature::SavannaTreeFeature(bool update) : AbstractTreeFeature(update, 5, TRUNK, LEAVES, false) {}
SavannaTreeFeature::~SavannaTreeFeature() = default;

// name guessed
void SavannaTreeFeature::placeLogAt(Level* level, const BlockPos& pos) {
    setBlock(level, pos, m_trunk);
}

// name guessed
void SavannaTreeFeature::placeLeafAt(Level* level, const BlockPos& pos) {
    Material* material = level->getBlockState(pos)->getMaterial();
    if (material == Material::AIR || material == Material::LEAVES)
        setBlock(level, pos, m_leaves);
}

// name guessed
bool SavannaTreeFeature::place(Level* level, Random& random, const BlockPos& pos) {
    PIXBeginNamedEvent(0, "SavannaTreeFeature::place");
    int height = random.nextInt(3) + random.nextInt(3) + m_minHeight;
    if (pos.getY() <= 0 || pos.getY() + height >= 256) {
        PIXEndNamedEvent();
        return false;
    }
    bool free = true;
    for (int y = pos.getY(); y <= pos.getY() + height + 1; ++y) {
        int radius = y == pos.getY() ? 0 : 1;
        if (y >= pos.getY() + height - 1)
            radius = 2;
        for (int x = pos.getX() - radius; x <= pos.getX() + radius && free; ++x) {
            for (int z = pos.getZ() - radius; z <= pos.getZ() + radius && free; ++z) {
                if (static_cast<unsigned int>(y) < 256) {
                    free = isFree(level->getBlockState(BlockPos(x, y, z))->getBlock());
                } else {
                    free = false;
                }
            }
        }
    }
    if (!free) {
        PIXEndNamedEvent();
        return false;
    }
    Block* ground = level->getBlockState(pos.below())->getBlock();
    if ((ground != Blocks::GRASS && ground != Blocks::DIRT) || pos.getY() >= 255 - height) {
        PIXEndNamedEvent();
        return false;
    }
    setDirtAt(level, pos.below());
    const Direction* direction = Direction::Plane::HORIZONTAL->getRandomDirection(random);
    int bendStart = height - random.nextInt(4) - 1;
    int bendLength = 3 - random.nextInt(3);
    int trunkX = pos.getX();
    int trunkZ = pos.getZ();
    int top = 0;
    MutableBlockPos candidate(0, 0, 0);
    for (int y = 0; y < height; ++y) {
        int worldY = pos.getY() + y;
        if (y >= bendStart && bendLength > 0) {
            trunkX += direction->getX();
            trunkZ += direction->getZ();
            --bendLength;
        }
        candidate.set(trunkX, worldY, trunkZ);
        Material* material = level->getBlockState(candidate)->getMaterial();
        if (material == Material::AIR || material == Material::LEAVES) {
            placeLogAt(level, candidate);
            top = worldY;
        }
    }
    {
        BlockPos crown(trunkX, top, trunkZ);
        for (int x = -3; x <= 3; ++x) {
            for (int z = -3; z <= 3; ++z) {
                if (std::abs(x) != 3 || std::abs(z) != 3)
                    placeLeafAt(level, crown.offset(x, 0, z));
            }
        }
        crown = crown.above();
        for (int x = -1; x <= 1; ++x)
            for (int z = -1; z <= 1; ++z)
                placeLeafAt(level, crown.offset(x, 0, z));
        placeLeafAt(level, crown.east(2));
        placeLeafAt(level, crown.west(2));
        placeLeafAt(level, crown.south(2));
        placeLeafAt(level, crown.north(2));
    }

    trunkX = pos.getX();
    trunkZ = pos.getZ();
    const Direction* branchDirection = Direction::Plane::HORIZONTAL->getRandomDirection(random);
    if (branchDirection != direction) {
        int branchStart = bendStart - random.nextInt(2) - 1;
        int branchLength = 1 + random.nextInt(3);
        int branchTop = 0;
        for (int y = branchStart; y < height && branchLength > 0; ++y, --branchLength) {
            if (y < 1)
                continue;
            int worldY = pos.getY() + y;
            trunkX += branchDirection->getX();
            trunkZ += branchDirection->getZ();
            BlockPos branch(trunkX, worldY, trunkZ);
            Material* material = level->getBlockState(branch)->getMaterial();
            if (material == Material::AIR || material == Material::LEAVES) {
                placeLogAt(level, branch);
                branchTop = worldY;
            }
        }
        if (branchTop > 0) {
            BlockPos crown(trunkX, branchTop, trunkZ);
            for (int x = -2; x <= 2; ++x)
                for (int z = -2; z <= 2; ++z)
                    if (std::abs(x) != 2 || std::abs(z) != 2)
                        placeLeafAt(level, crown.offset(x, 0, z));
            crown = crown.above();
            for (int x = -1; x <= 1; ++x)
                for (int z = -1; z <= 1; ++z)
                    placeLeafAt(level, crown.offset(x, 0, z));
        }
    }
    PIXEndNamedEvent();
    return true;
}
