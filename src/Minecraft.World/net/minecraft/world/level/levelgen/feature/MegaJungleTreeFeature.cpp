#include "net/minecraft/world/level/levelgen/feature/MegaJungleTreeFeature.h"

#include "NX/Platform.h"
#include "net/minecraft/core/MutableBlockPos.h"
#include "net/minecraft/util/Mth.h"
#include "net/minecraft/world/Random.h"
#include "net/minecraft/world/level/Level.h"
#include "net/minecraft/world/level/block/Blocks.h"
#include "net/minecraft/world/level/block/VineBlock.h"

MegaJungleTreeFeature::MegaJungleTreeFeature(bool update, int minHeight, int heightRange,
                                             const BlockState* trunk, const BlockState* leaves)
    : MegaTreeFeature(update, minHeight, heightRange, trunk, leaves) {}
MegaJungleTreeFeature::~MegaJungleTreeFeature() = default;

void MegaJungleTreeFeature::createCrown(Level* level, const BlockPos& pos, int radius) {
    for (int y = 0; y >= -2; --y)
        placeDoubleTrunkLeaves(level, pos.above(y), radius + 1 - y);
}

void MegaJungleTreeFeature::placeVine(Level* level, Random& random, const BlockPos& pos,
                                      const BooleanProperty* property) {
    if (random.nextInt(3) > 0 && level->isEmptyBlock(pos))
        setBlock(level, pos,
                 Blocks::VINE->defaultBlockState()->setValue(const_cast<BooleanProperty*>(property), true));
}

bool MegaJungleTreeFeature::place(Level* level, Random& random, const BlockPos& pos) {
    PIXBeginNamedEvent(0, "MegaJungleTreeFeature::place");
    int height = calcTreeHeigth(random);
    if (!prepareTree(level, random, pos, height)) {
        PIXEndNamedEvent();
        return false;
    }
    PIXBeginNamedEvent(0, "Create crown");
    createCrown(level, pos.above(height), 2);
    PIXEndNamedEvent();
    int branchY = pos.getY() + height - 2 - random.nextInt(4);
    PIXBeginNamedEvent(0, "Place leaves");
    MutableBlockPos branch(0, 0, 0);
    for (; branchY > pos.getY() + height / 2; branchY -= random.nextInt(4) + 2) {
        float angle = random.nextFloat() * (Mth::PI * 2.0f);
        int x = pos.getX() + static_cast<int>(0.5f + Mth::cos(angle) * 4.0f);
        int z = pos.getZ() + static_cast<int>(0.5f + Mth::sin(angle) * 4.0f);
        for (int segment = 0; segment < 5; ++segment) {
            x = pos.getX() + static_cast<int>(Mth::cos(angle) * segment + 1.5f);
            z = pos.getZ() + static_cast<int>(Mth::sin(angle) * segment + 1.5f);
            branch.set(x, branchY - 3 + segment / 2, z);
            setBlock(level, branch, m_trunk);
        }
        int depth = 1 + random.nextInt(2);
        for (int y = branchY - depth; y <= branchY; ++y) {
            branch.set(x, y, z);
            placeSingleTrunkLeaves(level, branch, 1 - (y - branchY));
        }
    }
    PIXEndNamedEvent();
    PIXBeginNamedEvent(0, "Place trunk");
    for (int y = 0; y < height; ++y) {
        BlockPos northWest = pos.above(y);
        if (isFree(level->getBlockState(northWest)->getBlock())) {
            setBlock(level, northWest, m_trunk);
            if (y > 0) {
                placeVine(level, random, northWest.west(), VineBlock::EAST);
                placeVine(level, random, northWest.north(), VineBlock::SOUTH);
            }
        }
        if (y < height - 1) {
            BlockPos northEast = northWest.east();
            if (isFree(level->getBlockState(northEast)->getBlock())) {
                setBlock(level, northEast, m_trunk);
                if (y > 0) {
                    placeVine(level, random, northEast.east(), VineBlock::WEST);
                    placeVine(level, random, northEast.north(), VineBlock::SOUTH);
                }
            }
            BlockPos southEast = northWest.south().east();
            if (isFree(level->getBlockState(southEast)->getBlock())) {
                setBlock(level, southEast, m_trunk);
                if (y > 0) {
                    placeVine(level, random, southEast.east(), VineBlock::WEST);
                    placeVine(level, random, southEast.south(), VineBlock::NORTH);
                }
            }
            BlockPos southWest = northWest.south();
            if (isFree(level->getBlockState(southWest)->getBlock())) {
                setBlock(level, southWest, m_trunk);
                if (y > 0) {
                    placeVine(level, random, southWest.west(), VineBlock::EAST);
                    placeVine(level, random, southWest.south(), VineBlock::NORTH);
                }
            }
        }
    }
    PIXEndNamedEvent();
    PIXEndNamedEvent();
    return true;
}
