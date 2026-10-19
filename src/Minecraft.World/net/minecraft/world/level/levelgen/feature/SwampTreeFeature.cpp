#include "net/minecraft/world/level/levelgen/feature/SwampTreeFeature.h"

#include "NX/Platform.h"
#include "net/minecraft/client/CMinecraftApp.h"
#include "net/minecraft/core/MutableBlockPos.h"
#include "net/minecraft/world/level/Level.h"
#include "net/minecraft/world/level/block/Blocks.h"
#include "net/minecraft/world/level/block/OldLeafBlock.h"
#include "net/minecraft/world/level/block/OldLogBlock.h"
#include "net/minecraft/world/level/block/VineBlock.h"
#include "net/minecraft/world/level/material/Material.h"
#include <cstdlib>

const BlockState* SwampTreeFeature::TRUNK;  // name guessed
const BlockState* SwampTreeFeature::LEAVES;

void SwampTreeFeature::staticCtor() {
    TRUNK = Blocks::LOG->defaultBlockState()->setValue(OldLogBlock::VARIANT, PlanksBlock::Variant::OAK);
    LEAVES = Blocks::LEAVES->defaultBlockState()
                 ->setValue(OldLeafBlock::VARIANT, PlanksBlock::Variant::OAK)
                 ->setValue(LeafBlock::CHECK_DECAY, false);
}

// name guessed
SwampTreeFeature::SwampTreeFeature() : AbstractTreeFeature(false, 5, TRUNK, LEAVES, false) {}

// name guessed
void SwampTreeFeature::addVine(Level* level, const BlockPos& pos, const BooleanProperty* property) {
    const BlockState* state
        = Blocks::VINE->defaultBlockState()->setValue(const_cast<BooleanProperty*>(property), true);
    BlockPos current = pos;
    setBlock(level, current, state);
    current = current.below();
    int remaining = 4;
    while (level->getBlockState(current)->getBlock()->getMaterial() == Material::AIR && remaining > 0) {
        setBlock(level, current, state);
        current = current.below();
        --remaining;
    }
}

// name guessed
// NON_MATCHING | score: 1410 (lower is better)
bool SwampTreeFeature::place(Level* level, Random& random, const BlockPos& input) {
    PIXBeginNamedEvent(0, "SwampTreeFeature::place");
    BlockPos pos = input;
    int height = random.nextInt(4) + m_minHeight;
    while (level->getBlockState(pos.below())->getMaterial() == Material::WATER)
        pos = pos.below();
    if (pos.getY() <= 0 || pos.getY() + height >= 128) {
        PIXEndNamedEvent();
        return false;
    }
    if (CConsoleMinecraftApp::sInstance.getLevelGenerationOptions()
        && CConsoleMinecraftApp::sInstance.getLevelGenerationOptions()->intersects(
            pos.offset(-3, -1, -3), pos.offset(3, height, 3))) {
        PIXEndNamedEvent();
        return false;
    }
    MutableBlockPos cursor(0, 0, 0);
    int free = true;
    for (int y = pos.getY(); y <= pos.getY() + height + 1; ++y) {
        int radius = y == pos.getY() ? 0 : 1;
        if (y >= pos.getY() + height - 1)
            radius = 3;
        for (int x = pos.getX() - radius; x <= pos.getX() + radius && free; ++x) {
            for (int z = pos.getZ() - radius; z <= pos.getZ() + radius && free; ++z) {
                if (y >= 0 && y < 128) {
                    const BlockState* state = level->getBlockState(*cursor.set(x, y, z));
                    Block* block = state->getBlock();
                    if (state->getMaterial() == Material::AIR || state->getMaterial() == Material::LEAVES)
                        free = true;
                    else if (block == Blocks::WATER || block == Blocks::FLOWING_WATER)
                        free = y <= pos.getY();
                    else
                        free = false;
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
    if ((ground != Blocks::GRASS && ground != Blocks::DIRT) || pos.getY() >= 127 - height) {
        PIXEndNamedEvent();
        return false;
    }
    setDirtAt(level, pos.below());
    MutableBlockPos leaf(0, 0, 0);
    for (int y = pos.getY() + height - 3; y <= pos.getY() + height; ++y) {
        int relative = y - (pos.getY() + height);
        int radius = 2 - relative / 2;
        for (int x = pos.getX() - radius; x <= pos.getX() + radius; ++x) {
            int dx = x - pos.getX();
            for (int z = pos.getZ() - radius; z <= pos.getZ() + radius; ++z) {
                int dz = z - pos.getZ();
                if (std::abs(dx) != radius || std::abs(dz) != radius
                    || (random.nextInt(2) != 0 && relative != 0)) {
                    leaf.set(x, y, z);
                    if (!level->getBlockState(leaf)->isSolid())
                        setBlock(level, leaf, m_leaves);
                }
            }
        }
    }
    for (int y = 0; y < height; ++y) {
        const BlockState* state = level->getBlockState(pos.above(y));
        Block* block = state->getBlock();
        if (state->getMaterial() == Material::AIR || state->getMaterial() == Material::LEAVES
            || block == Blocks::FLOWING_WATER || block == Blocks::WATER)
            setBlock(level, pos.above(y), m_trunk);
    }
    MutableBlockPos vines(0, 0, 0);
    for (int y = pos.getY() + height - 3; y <= pos.getY() + height; ++y) {
        int relative = y - (pos.getY() + height);
        int radius = 2 - relative / 2;
        for (int x = pos.getX() - radius; x <= pos.getX() + radius; ++x) {
            for (int z = pos.getZ() - radius; z <= pos.getZ() + radius; ++z) {
                vines.set(x, y, z);
                if (level->getBlockState(vines)->getMaterial() == Material::LEAVES) {
                    BlockPos west = vines.west();
                    BlockPos east = vines.east();
                    BlockPos north = vines.north();
                    BlockPos south = vines.south();
                    if (random.nextInt(4) == 0 && level->getBlockState(west)->getMaterial() == Material::AIR)
                        addVine(level, west, VineBlock::EAST);
                    if (random.nextInt(4) == 0 && level->getBlockState(east)->getMaterial() == Material::AIR)
                        addVine(level, east, VineBlock::WEST);
                    if (random.nextInt(4) == 0 && level->getBlockState(north)->getMaterial() == Material::AIR)
                        addVine(level, north, VineBlock::SOUTH);
                    if (random.nextInt(4) == 0 && level->getBlockState(south)->getMaterial() == Material::AIR)
                        addVine(level, south, VineBlock::NORTH);
                }
            }
        }
    }
    PIXEndNamedEvent();
    return true;
}
