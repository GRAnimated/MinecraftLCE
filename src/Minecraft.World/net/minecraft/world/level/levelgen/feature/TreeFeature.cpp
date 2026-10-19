#include "net/minecraft/world/level/levelgen/feature/TreeFeature.h"

#include "NX/Platform.h"
#include "net/minecraft/client/CMinecraftApp.h"
#include "net/minecraft/core/Direction.h"
#include "net/minecraft/core/MutableBlockPos.h"
#include "net/minecraft/world/Random.h"
#include "net/minecraft/world/level/Level.h"
#include "net/minecraft/world/level/block/Blocks.h"
#include "net/minecraft/world/level/block/CocoaBlock.h"
#include "net/minecraft/world/level/block/OldLeafBlock.h"
#include "net/minecraft/world/level/block/OldLogBlock.h"
#include "net/minecraft/world/level/block/VineBlock.h"
#include "net/minecraft/world/level/levelgen/LevelGenerationOptions.h"
#include "net/minecraft/world/level/material/Material.h"
#include <cstdlib>

const BlockState* TreeFeature::TRUNK;  // name guessed
const BlockState* TreeFeature::LEAVES;

void TreeFeature::staticCtor() {
    TRUNK = Blocks::LOG->defaultBlockState()->setValue<PlanksBlock::Variant*>(OldLogBlock::VARIANT,
                                                                              PlanksBlock::Variant::OAK);
    LEAVES = Blocks::LEAVES->defaultBlockState()
                 ->setValue<PlanksBlock::Variant*>(OldLeafBlock::VARIANT, PlanksBlock::Variant::OAK)
                 ->setValue<bool>(LeafBlock::CHECK_DECAY, false);
}

// name guessed
TreeFeature::TreeFeature(bool update) : AbstractTreeFeature(update, 4, TRUNK, LEAVES, false) {}

// name guessed
TreeFeature::TreeFeature(bool update, int minHeight, const BlockState* trunk, const BlockState* leaves,
                         bool vines)
    : AbstractTreeFeature(update, minHeight, trunk, leaves, vines) {}

/** Preserve the original clearance scan and profiling/query order.
 */
// name guessed
bool TreeFeature::prepareSpawn(Level* level, const BlockPos& pos, int height) {
    PIXBeginNamedEvent(0.0f, "TreeFeature::prepareSpawn");
    bool free = false;
    if (pos.getY() <= 0 || pos.getY() + height >= 256) {
        PIXEndNamedEvent();
        return false;
    }
    if (CConsoleMinecraftApp::sInstance.getLevelGenerationOptions()) {
        PIXBeginNamedEvent(0.0f, "TreeFeature checking intersects");
        auto options = CConsoleMinecraftApp::sInstance.getLevelGenerationOptions();
        bool excluded = options->intersects(pos.offset(-2, -1, -2), pos.offset(2, height, 2));
        PIXEndNamedEvent();
        if (excluded) {
            PIXEndNamedEvent();
            return false;
        }
    }
    MutableBlockPos current;
    free = true;
    for (int y = pos.getY(); y <= pos.getY() + height + 1; ++y) {
        int radius = y == pos.getY() ? 0 : 1;
        if (y >= pos.getY() + height - 1)
            radius = 2;
        for (int x = pos.getX() - radius; x <= pos.getX() + radius && free; ++x) {
            for (int z = pos.getZ() - radius; z <= pos.getZ() + radius && free; ++z) {
                if ((unsigned int)y < 256) {
                    current.set(x, y, z);
                    free = isFree(level->getBlockState(current)->getBlock());
                } else {
                    free = false;
                }
            }
        }
    }
    if (free) {
        Block* ground = level->getBlockState(pos.below())->getBlock();
        if ((ground == Blocks::GRASS || ground == Blocks::DIRT || ground == Blocks::FARMLAND)
            && pos.getY() < 255 - height) {
            setDirtAt(level, pos.below());
            PIXEndNamedEvent();
            return true;
        }
    }
    PIXEndNamedEvent();
    return false;
}

// name guessed
void TreeFeature::placeLeaf(Level* level, const MutableBlockPos& pos) {
    Material* material = level->getBlockState(pos)->getMaterial();
    if (material == Material::AIR || material == Material::LEAVES || material == Material::MOSS)
        setBlock(level, pos, m_leaves);
}

// name guessed
void TreeFeature::addHangingVine(Level* level, const BlockPos& pos, const BooleanProperty* property) {
    BlockPos current = pos;
    addVine(level, current, property);
    current = pos.below();
    int remaining = 4;
    while (level->getBlockState(current)->getBlock()->getMaterial() == Material::AIR && remaining > 0) {
        addVine(level, current, property);
        current = current.below();
        --remaining;
    }
}

// name guessed
void TreeFeature::placeCocoa(Level* level, int age, const BlockPos& pos, const Direction* direction) {
    setBlock(level, pos,
             Blocks::COCOA->defaultBlockState()
                 ->setValue<int>(CocoaBlock::AGE, age)
                 ->setValue<const Direction*>(HorizontalDirectionalBlock::FACING, direction));
}

/** Keep the original leaf/vine scan ordering and random draws.
 */
// name guessed
bool TreeFeature::place(Level* level, Random& random, const BlockPos& pos) {
    PIXBeginNamedEvent(0.0f, "TreeFeature::place");
    int height = random.nextInt(3) + m_minHeight;
    if (!prepareSpawn(level, pos, height)) {
        PIXEndNamedEvent();
        return false;
    }
    if (placeTrunk(level, pos, random, height)) {
        PIXBeginNamedEvent(0.0f, "Placing TreeFeature leaves");
        MutableBlockPos current(0, 0, 0);
        for (int y = pos.getY() + height; y >= pos.getY() + height - 3; --y) {
            int topOffset = y - (pos.getY() + height);
            int radius = 1 - topOffset / 2;
            for (int x = pos.getX() - radius; x <= pos.getX() + radius; ++x) {
                int dx = x - pos.getX();
                for (int z = pos.getZ() - radius; z <= pos.getZ() + radius; ++z) {
                    int dz = z - pos.getZ();
                    // Top corners still consume the random draw before being skipped.
                    if (std::abs(dx) != radius || std::abs(dz) != radius
                        || (random.nextInt(2) != 0 && topOffset != 0)) {
                        current.set(x, y, z);
                        placeLeaf(level, current);
                    }
                }
            }
        }
        PIXEndNamedEvent();
        if (m_vines) {
            PIXBeginNamedEvent(0.0f, "TreeFeature adding vines");
            MutableBlockPos vinePos(0, 0, 0);
            for (int y = pos.getY() + height - 3; y <= pos.getY() + height; ++y) {
                int radius = 2 - (y - (pos.getY() + height)) / 2;
                for (int x = pos.getX() - radius; x <= pos.getX() + radius; ++x) {
                    for (int z = pos.getZ() - radius; z <= pos.getZ() + radius; ++z) {
                        vinePos.set(x, y, z);
                        if (level->getBlockState(vinePos)->getBlock()->getMaterial() == Material::LEAVES) {
                            auto west = vinePos.west();
                            auto east = vinePos.east();
                            auto north = vinePos.north();
                            auto south = vinePos.south();
                            if (random.nextInt(4) == 0
                                && level->getBlockState(west)->getMaterial() == Material::AIR)
                                addHangingVine(level, west, VineBlock::EAST);
                            if (random.nextInt(4) == 0
                                && level->getBlockState(east)->getMaterial() == Material::AIR)
                                addHangingVine(level, east, VineBlock::WEST);
                            if (random.nextInt(4) == 0
                                && level->getBlockState(north)->getMaterial() == Material::AIR)
                                addHangingVine(level, north, VineBlock::SOUTH);
                            if (random.nextInt(4) == 0
                                && level->getBlockState(south)->getMaterial() == Material::AIR)
                                addHangingVine(level, south, VineBlock::NORTH);
                        }
                    }
                }
            }
            PIXEndNamedEvent();
            int cocoa = random.nextInt(5);
            if (height > 5 && cocoa == 0) {
                PIXBeginNamedEvent(0.0f, "TreeFeature adding cocoa");
                {
                    auto directions = Direction::Plane::HORIZONTAL->iterator();
                    for (unsigned int i = 0; i < directions.m_length; ++i) {
                        const Direction* direction = directions[i];
                        if (random.nextInt(4) == 0) {
                            const Direction* opposite = direction->getOpposite();
                            int age = random.nextInt(3);
                            placeCocoa(level, age, pos.offset(opposite->getX(), height - 5, opposite->getZ()),
                                       direction);
                        }
                    }
                }
                {
                    auto directions = Direction::Plane::HORIZONTAL->iterator();
                    for (unsigned int i = 0; i < directions.m_length; ++i) {
                        const Direction* direction = directions[i];
                        if (random.nextInt(3) == 0) {
                            const Direction* opposite = direction->getOpposite();
                            int age = random.nextInt(3);
                            placeCocoa(level, age, pos.offset(opposite->getX(), height - 4, opposite->getZ()),
                                       direction);
                        }
                    }
                }
                PIXEndNamedEvent();
            }
        }
    }
    PIXEndNamedEvent();
    return true;
}
