#include "net/minecraft/world/level/levelgen/feature/HugeMushroomFeature.h"

#include "net/minecraft/core/BlockPos.h"
#include "net/minecraft/world/Random.h"
#include "net/minecraft/world/level/Level.h"
#include "net/minecraft/world/level/block/Blocks.h"
#include "net/minecraft/world/level/block/HugeMushroomBlock.h"
#include "net/minecraft/world/level/block/state/BlockState.h"
#include "net/minecraft/world/level/material/Material.h"

HugeMushroomFeature::HugeMushroomFeature(Block* type) : Feature(true), m_type(type) {}

HugeMushroomFeature::HugeMushroomFeature() : Feature(false), m_type(nullptr) {}

bool HugeMushroomFeature::place(Level* level, Random& random, const BlockPos& pos) {
    Block* type = m_type;
    if (!type)
        type = random.nextBoolean() ? Blocks::BROWN_MUSHROOM_BLOCK : Blocks::RED_MUSHROOM_BLOCK;

    int height = random.nextInt(3) + 4;
    if (random.nextInt(12) == 0)
        height *= 2;
    if (pos.getY() < 1 || pos.getY() + height >= 255)
        return false;

    bool clear = true;
    for (int y = pos.getY(); y <= pos.getY() + height + 1; ++y) {
        int radius = 3;
        if (y <= pos.getY() + 3)
            radius = 0;
        BlockPos candidate;
        for (int x = pos.getX() - radius; x <= pos.getX() + radius && clear; ++x) {
            for (int z = pos.getZ() - radius; z <= pos.getZ() + radius && clear; ++z) {
                if (y >= 0 && y < 256) {
                    candidate = BlockPos(x, y, z);
                    const BlockState* state = level->getBlockState(candidate);
                    Material* material = state->getMaterial();
                    if (material != Material::AIR && material != Material::LEAVES)
                        clear = false;
                } else {
                    clear = false;
                }
            }
        }
    }
    if (!clear)
        return false;

    Block* ground = level->getBlockState(pos.below())->getBlock();
    if (ground != Blocks::DIRT && ground != Blocks::GRASS && ground != Blocks::MYCELIUM)
        return false;

    int capStart = pos.getY() + height;
    if (type == Blocks::RED_MUSHROOM_BLOCK)
        capStart = pos.getY() + height - 3;
    for (int y = capStart; y <= pos.getY() + height; ++y) {
        int radius = 1;
        if (y < pos.getY() + height)
            radius = 2;
        if (type == Blocks::BROWN_MUSHROOM_BLOCK)
            radius = 3;
        int minX = pos.getX() - radius;
        int maxX = pos.getX() + radius;
        int minZ = pos.getZ() - radius;
        int maxZ = pos.getZ() + radius;
        for (int x = minX; x <= maxX; ++x) {
            for (int z = minZ; z <= maxZ; ++z) {
                int data = 5;
                if (x == minX)
                    --data;
                if (x == maxX)
                    ++data;
                if (z == minZ)
                    data -= 3;
                if (z == maxZ)
                    data += 3;
                HugeMushroomBlock::Variant* variant = HugeMushroomBlock::Variant::byData(data);
                if (type == Blocks::BROWN_MUSHROOM_BLOCK || y < pos.getY() + height) {
                    if ((x == minX || x == maxX) && (z == minZ || z == maxZ))
                        continue;
                    if (x == pos.getX() - (radius - 1) && z == pos.getZ() - radius)
                        variant = HugeMushroomBlock::Variant::NORTH_WEST;
                    if (x == minX && z == pos.getZ() - (radius - 1))
                        variant = HugeMushroomBlock::Variant::NORTH_WEST;
                    if (x == pos.getX() + (radius - 1) && z == minZ)
                        variant = HugeMushroomBlock::Variant::NORTH_EAST;
                    if (x == maxX && z == pos.getZ() - (radius - 1))
                        variant = HugeMushroomBlock::Variant::NORTH_EAST;
                    if (x == pos.getX() - (radius - 1) && z == maxZ)
                        variant = HugeMushroomBlock::Variant::SOUTH_WEST;
                    if (x == minX && z == pos.getZ() + (radius - 1))
                        variant = HugeMushroomBlock::Variant::SOUTH_WEST;
                    if (x == pos.getX() + (radius - 1) && z == maxZ)
                        variant = HugeMushroomBlock::Variant::SOUTH_EAST;
                    if (x == maxX && z == pos.getZ() + (radius - 1))
                        variant = HugeMushroomBlock::Variant::SOUTH_EAST;
                }
                if (variant == HugeMushroomBlock::Variant::CENTER && y < pos.getY() + height)
                    variant = HugeMushroomBlock::Variant::ALL_INSIDE;
                // The shipped Switch check reads the origin Y on both sides.
                if (variant == HugeMushroomBlock::Variant::ALL_INSIDE && pos.getY() < pos.getY() + height - 1)
                    continue;
                BlockPos candidate(x, y, z);
                if (!level->getBlockState(candidate)->isSolid())
                    setBlock(level, candidate,
                             type->defaultBlockState()->setValue(HugeMushroomBlock::VARIANT, variant));
            }
        }
    }

    for (int y = 0; y < height; ++y) {
        if (!level->getBlockState(pos.above(y))->isSolid())
            setBlock(level, pos.above(y),
                     type->defaultBlockState()->setValue(HugeMushroomBlock::VARIANT,
                                                         HugeMushroomBlock::Variant::STEM));
    }
    return true;
}
