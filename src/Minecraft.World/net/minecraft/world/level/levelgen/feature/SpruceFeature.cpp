#include "net/minecraft/world/level/levelgen/feature/SpruceFeature.h"

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

const BlockState* SpruceFeature::TRUNK;
const BlockState* SpruceFeature::LEAVES;

void SpruceFeature::staticCtor() {
    TRUNK = Blocks::LOG->defaultBlockState()->setValue(OldLogBlock::VARIANT, PlanksBlock::Variant::SPRUCE);
    LEAVES = Blocks::LEAVES->defaultBlockState()
                 ->setValue(OldLeafBlock::VARIANT, PlanksBlock::Variant::SPRUCE)
                 ->setValue(LeafBlock::CHECK_DECAY, false);
}

SpruceFeature::SpruceFeature(bool update) : AbstractTreeFeature(update, 6, TRUNK, LEAVES, false) {}

bool SpruceFeature::place(Level* level, Random& random, const BlockPos& pos) {
    int height = random.nextInt(4) + m_minHeight;
    int bareHeight = random.nextInt(2) + 1;
    int maxRadius = random.nextInt(2) + 2;
    if (pos.getY() <= 0 || pos.getY() + height >= 256)
        return false;
    if (CConsoleMinecraftApp::sInstance.getLevelGenerationOptions()
        && CConsoleMinecraftApp::sInstance.getLevelGenerationOptions()->intersects(
            pos.offset(-maxRadius, -1, -maxRadius), pos.offset(maxRadius, height, maxRadius)))
        return false;
    MutableBlockPos cursor;
    bool free = true;
    for (int y = pos.getY(); y <= pos.getY() + height + 1 && free; ++y) {
        int radius = maxRadius;
        if (y - pos.getY() <= bareHeight - 1)
            radius = 0;
        for (int x = pos.getX() - radius; x <= pos.getX() + radius && free; ++x) {
            for (int z = pos.getZ() - radius; z <= pos.getZ() + radius && free; ++z) {
                if (y >= 0 && y < 256) {
                    Material* material = level->getBlockState(*cursor.set(x, y, z))->getMaterial();
                    free = material == Material::AIR || material == Material::LEAVES;
                } else {
                    free = false;
                }
            }
        }
    }
    if (!free)
        return false;
    Block* ground = level->getBlockState(pos.below())->getBlock();
    if ((ground != Blocks::GRASS && ground != Blocks::DIRT && ground != Blocks::FARMLAND)
        || pos.getY() >= 255 - height)
        return false;
    setDirtAt(level, pos.below());
    int trunkHeight = height - random.nextInt(3);
    if (placeTrunk(level, pos, random, trunkHeight)) {
        int layers = height - bareHeight;
        int radius = random.nextInt(2);
        int limit = 1;
        int reset = 0;
        for (int layer = 0; layer <= layers; ++layer) {
            int y = pos.getY() + height - layer;
            for (int x = pos.getX() - radius; x <= pos.getX() + radius; ++x) {
                int dx = x - pos.getX();
                for (int z = pos.getZ() - radius; z <= pos.getZ() + radius; ++z) {
                    int dz = z - pos.getZ();
                    if (std::abs(dx) == radius && std::abs(dz) == radius && radius > 0)
                        continue;
                    BlockPos leaves(x, y, z);
                    if (!level->getBlockState(leaves)->isSolid())
                        setBlock(level, leaves, m_leaves);
                }
            }
            if (radius >= limit) {
                radius = reset;
                reset = 1;
                if (++limit > maxRadius)
                    limit = maxRadius;
            } else {
                ++radius;
            }
        }
    }
    return true;
}
