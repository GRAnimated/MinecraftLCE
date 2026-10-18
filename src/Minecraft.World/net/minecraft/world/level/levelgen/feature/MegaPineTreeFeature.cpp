#include "net/minecraft/world/level/levelgen/feature/MegaPineTreeFeature.h"

#include "NX/Platform.h"
#include "net/minecraft/core/BlockPos.h"
#include "net/minecraft/util/Mth.h"
#include "net/minecraft/world/Random.h"
#include "net/minecraft/world/level/Level.h"
#include "net/minecraft/world/level/block/Blocks.h"
#include "net/minecraft/world/level/block/DirtBlock.h"
#include "net/minecraft/world/level/block/OldLeafBlock.h"
#include "net/minecraft/world/level/block/OldLogBlock.h"
#include "net/minecraft/world/level/material/Material.h"
#include <cstdlib>

const BlockState* MegaPineTreeFeature::TRUNK;
const BlockState* MegaPineTreeFeature::LEAVES;
const BlockState* MegaPineTreeFeature::PODZOL;

void MegaPineTreeFeature::staticCtor() {
    TRUNK = Blocks::LOG->defaultBlockState()->setValue(OldLogBlock::VARIANT, PlanksBlock::Variant::SPRUCE);
    LEAVES
        = Blocks::LEAVES->defaultBlockState()->setValue(OldLeafBlock::VARIANT, PlanksBlock::Variant::SPRUCE);
    PODZOL = Blocks::DIRT->defaultBlockState()->setValue(DirtBlock::VARIANT, DirtBlock::Variant::PODZOL);
}

MegaPineTreeFeature::MegaPineTreeFeature(bool update, bool useBaseHeight)
    : MegaTreeFeature(update, 13, 15, TRUNK, LEAVES), m_useBaseHeight(useBaseHeight) {}
MegaPineTreeFeature::~MegaPineTreeFeature() = default;

void MegaPineTreeFeature::createCrown(Level* level, int x, int z, int y, int radius, Random& random) {
    int depth = random.nextInt(5) + (m_useBaseHeight ? m_minHeight : 3);
    int previousRadius = 0;
    for (int currentY = y - depth; currentY <= y; ++currentY) {
        int distance = y - currentY;
        int width = radius + Mth::floor(static_cast<float>(distance) / depth * 3.5f);
        placeDoubleTrunkLeaves(
            level, BlockPos(x, currentY, z),
            width + (distance > 0 && width == previousRadius && (currentY & 1) == 0 ? 1 : 0));
        previousRadius = width;
    }
}

bool MegaPineTreeFeature::place(Level* level, Random& random, const BlockPos& pos) {
    int height = calcTreeHeigth(random);
    if (!prepareTree(level, random, pos, height))
        return false;
    createCrown(level, pos.getX(), pos.getZ(), pos.getY() + height, 0, random);
    for (int y = 0; y < height; ++y) {
        const BlockState* state = level->getBlockState(pos.above(y));
        if (state->getMaterial() == Material::AIR || state->getMaterial() == Material::LEAVES)
            setBlock(level, pos.above(y), m_trunk);
        if (y < height - 1) {
            state = level->getBlockState(pos.offset(1, y, 0));
            if (state->getMaterial() == Material::AIR || state->getMaterial() == Material::LEAVES)
                setBlock(level, pos.offset(1, y, 0), m_trunk);
            state = level->getBlockState(pos.offset(1, y, 1));
            if (state->getMaterial() == Material::AIR || state->getMaterial() == Material::LEAVES)
                setBlock(level, pos.offset(1, y, 1), m_trunk);
            state = level->getBlockState(pos.offset(0, y, 1));
            if (state->getMaterial() == Material::AIR || state->getMaterial() == Material::LEAVES)
                setBlock(level, pos.offset(0, y, 1), m_trunk);
        }
    }
    return true;
}

void MegaPineTreeFeature::placePodzolAt(Level* level, const BlockPos& pos) {
    for (int y = 2; y >= -3; --y) {
        BlockPos candidate = pos.above(y);
        const BlockState* state = level->getBlockState(candidate);
        Block* block = state->getBlock();
        if (block == Blocks::GRASS || block == Blocks::DIRT) {
            setBlock(level, candidate, PODZOL);
            return;
        }
        if (state->getMaterial() != Material::AIR && y < 0)
            break;
    }
}

void MegaPineTreeFeature::placePodzolCircle(Level* level, const BlockPos& pos) {
    for (int x = -2; x <= 2; ++x)
        for (int z = -2; z <= 2; ++z)
            if (std::abs(x) != 2 || std::abs(z) != 2)
                placePodzolAt(level, pos.offset(x, 0, z));
}

void MegaPineTreeFeature::postPlaceTree(Level* level, Random& random, const BlockPos& pos) {
    PIXBeginNamedEvent(0, "MegaPineTreeFeature::postPlaceTree");
    placePodzolCircle(level, pos.west().north());
    placePodzolCircle(level, pos.east(2).north());
    placePodzolCircle(level, pos.west().south(2));
    placePodzolCircle(level, pos.east(2).south(2));
    for (int i = 0; i < 5; ++i) {
        int value = random.nextInt(64);
        int x = value % 8;
        int z = value / 8;
        if (x == 0 || x == 7 || z == 0 || z == 7)
            placePodzolCircle(level, pos.offset(x - 3, 0, z - 3));
    }
    PIXEndNamedEvent();
}
