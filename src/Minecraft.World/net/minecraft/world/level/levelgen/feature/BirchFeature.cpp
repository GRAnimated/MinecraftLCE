#include "net/minecraft/world/level/levelgen/feature/BirchFeature.h"

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

const BlockState* BirchFeature::TRUNK;
const BlockState* BirchFeature::LEAVES;

void BirchFeature::staticCtor() {
    TRUNK = Blocks::LOG->defaultBlockState()->setValue(OldLogBlock::VARIANT, PlanksBlock::Variant::BIRCH);
    LEAVES = Blocks::LEAVES->defaultBlockState()
                 ->setValue(OldLeafBlock::VARIANT, PlanksBlock::Variant::BIRCH)
                 ->setValue(LeafBlock::CHECK_DECAY, false);
}

BirchFeature::BirchFeature(bool update, bool superBirch)
    : AbstractTreeFeature(update, 5, TRUNK, LEAVES, false), m_superBirch(superBirch) {}

bool BirchFeature::place(Level* level, Random& random, const BlockPos& pos) {
    PIXBeginNamedEvent(0, "BirchFeature::place");
    int height = random.nextInt(3) + m_minHeight;
    if (m_superBirch)
        height += random.nextInt(7);
    if (pos.getY() <= 0 || pos.getY() + height >= 256) {
        PIXEndNamedEvent();
        return false;
    }
    MutableBlockPos cursor(0, 0, 0);
    bool free = true;
    for (int y = pos.getY(); y <= pos.getY() + height + 1; ++y) {
        int radius = y == pos.getY() ? 0 : 1;
        if (y >= pos.getY() + height - 1)
            radius = 2;
        for (int x = pos.getX() - radius; x <= pos.getX() + radius && free; ++x) {
            for (int z = pos.getZ() - radius; z <= pos.getZ() + radius && free; ++z) {
                if (y >= 0 && y < 256) {
                    cursor.set(x, y, z);
                    Block* block = level->getBlockState(cursor)->getBlock();
                    // The original call passes the block as the unused receiver as well.
                    free = reinterpret_cast<AbstractTreeFeature*>(block)->isFree(block);
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
    if ((ground != Blocks::GRASS && ground != Blocks::DIRT && ground != Blocks::FARMLAND)
        || pos.getY() >= 255 - height) {
        PIXEndNamedEvent();
        return false;
    }
    if (CConsoleMinecraftApp::sInstance.getLevelGenerationOptions()
        && CConsoleMinecraftApp::sInstance.getLevelGenerationOptions()->intersects(
            pos.offset(-3, -1, -3), pos.offset(3, height, 3))) {
        PIXEndNamedEvent();
        return false;
    }
    setDirtAt(level, pos.below());
    if (placeTrunk(level, pos, random, height)) {
        MutableBlockPos leaves(0, 0, 0);
        for (int y = pos.getY() + height - 3; y <= pos.getY() + height; ++y) {
            int relative = y - (pos.getY() + height);
            int radius = 1 - relative / 2;
            for (int x = pos.getX() - radius; x <= pos.getX() + radius; ++x) {
                int dx = x - pos.getX();
                for (int z = pos.getZ() - radius; z <= pos.getZ() + radius; ++z) {
                    int dz = z - pos.getZ();
                    if (std::abs(dx) != radius || std::abs(dz) != radius
                        || (random.nextInt(2) != 0 && relative != 0)) {
                        leaves.set(x, y, z);
                        Material* material = level->getBlockState(leaves)->getMaterial();
                        if (material == Material::AIR || material == Material::LEAVES)
                            setBlock(level, leaves, m_leaves);
                    }
                }
            }
        }
        PIXEndNamedEvent();
    }
    return true;
}
