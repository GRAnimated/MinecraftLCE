#include "net/minecraft/world/level/levelgen/feature/PineFeature.h"

#include "NX/Platform.h"
#include "net/minecraft/client/CMinecraftApp.h"
#include "net/minecraft/core/MutableBlockPos.h"
#include "net/minecraft/world/level/Level.h"
#include "net/minecraft/world/level/block/Blocks.h"
#include "net/minecraft/world/level/block/OldLeafBlock.h"
#include "net/minecraft/world/level/block/OldLogBlock.h"
#include "net/minecraft/world/level/block/state/BlockState.h"
#include "net/minecraft/world/level/material/Material.h"
#include <cstdlib>

const BlockState* PineFeature::TRUNK;  // name guessed
const BlockState* PineFeature::LEAVES;

void PineFeature::staticCtor() {
    TRUNK = Blocks::LOG->defaultBlockState()->setValue(OldLogBlock::VARIANT, PlanksBlock::Variant::SPRUCE);
    LEAVES = Blocks::LEAVES->defaultBlockState()
                 ->setValue(OldLeafBlock::VARIANT, PlanksBlock::Variant::SPRUCE)
                 ->setValue(LeafBlock::CHECK_DECAY, false);
}

// name guessed
PineFeature::PineFeature() : AbstractTreeFeature(false, 7, TRUNK, LEAVES, false) {}

// name guessed
bool PineFeature::place(Level* level, Random& random, const BlockPos& pos) {
    PIXBeginNamedEvent(0, "PineFeature::place");
    int height = random.nextInt(5) + m_minHeight;
    int foliageStart = height - random.nextInt(2) - 3;
    int maxRadius = random.nextInt(height - foliageStart + 1) + 1;
    if (pos.getY() <= 0 || pos.getY() + height >= 128) {
        PIXEndNamedEvent();
        return false;
    }
    if (CConsoleMinecraftApp::sInstance.getLevelGenerationOptions()
        && CConsoleMinecraftApp::sInstance.getLevelGenerationOptions()->intersects(
            BlockPos(pos.getX() - maxRadius, pos.getY() - 1, pos.getZ() - maxRadius),
            BlockPos(pos.getX() + maxRadius, pos.getY() + height, pos.getZ() + maxRadius))) {
        PIXEndNamedEvent();
        return false;
    }
    bool free = true;
    for (int y = pos.getY(); y <= pos.getY() + height + 1 && free; ++y) {
        int radius = y - pos.getY() < foliageStart ? 0 : maxRadius;
        for (int x = pos.getX() - radius; x <= pos.getX() + radius && free; ++x) {
            for (int z = pos.getZ() - radius; z <= pos.getZ() + radius && free; ++z) {
                if (y >= 0 && y < 128)
                    free = isFree(level->getBlockState(BlockPos(x, y, z))->getBlock());
                else
                    free = false;
            }
        }
    }
    if (!free) {
        PIXEndNamedEvent();
        return false;
    }
    Block* ground = level->getBlockState(pos.below())->getBlock();
    if ((ground != Blocks::GRASS && ground != Blocks::DIRT) || pos.getY() >= 127 - height) {
        PIXEndNamedEvent();
        return false;
    }
    setDirtAt(level, pos.below());
    MutableBlockPos leaves(0, 0, 0);
    int radius = 0;
    for (int y = pos.getY() + height; y >= pos.getY() + foliageStart; --y) {
        for (int x = pos.getX() - radius; x <= pos.getX() + radius; ++x) {
            int dx = x - pos.getX();
            for (int z = pos.getZ() - radius; z <= pos.getZ() + radius; ++z) {
                int dz = z - pos.getZ();
                if (std::abs(dx) == radius && std::abs(dz) == radius && radius > 0)
                    continue;
                leaves.set(x, y, z);
                if (!level->getBlockState(leaves)->isSolid())
                    setBlock(level, leaves, m_leaves);
            }
        }
        if (radius >= 1 && y == pos.getY() + foliageStart + 1)
            --radius;
        else if (radius < maxRadius)
            ++radius;
    }
    for (int y = 0; y < height - 1; ++y) {
        Material* material = level->getBlockState(pos.above(y))->getMaterial();
        if (material == Material::AIR || material == Material::LEAVES)
            setBlock(level, pos.above(y), m_trunk);
    }
    PIXEndNamedEvent();
    return true;
}
