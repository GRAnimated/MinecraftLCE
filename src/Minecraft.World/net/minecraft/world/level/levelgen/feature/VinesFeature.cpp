#include "net/minecraft/world/level/levelgen/feature/VinesFeature.h"

#include "net/minecraft/core/BlockPos.h"
#include "net/minecraft/core/Direction.h"
#include "net/minecraft/world/Random.h"
#include "net/minecraft/world/level/Level.h"
#include "net/minecraft/world/level/block/Blocks.h"
#include "net/minecraft/world/level/block/VineBlock.h"

VinesFeature::VinesFeature() : Feature(false) {}

bool VinesFeature::place(Level* level, Random& random, const BlockPos& origin) {
    BlockPos pos = origin;
    for (; pos.getY() < 128; pos = pos.above()) {
        if (level->isEmptyBlock(pos)) {
            auto directions = Direction::Plane::HORIZONTAL->iterator();
            for (unsigned int i = 0; i < directions.m_length; ++i) {
                const Direction* direction = directions[i];
                if (Blocks::VINE->mayPlace(level, pos, direction)) {
                    const BlockState* state = Blocks::VINE->defaultBlockState()
                                                  ->setValue(VineBlock::SOUTH, direction == Direction::SOUTH)
                                                  ->setValue(VineBlock::WEST, direction == Direction::WEST)
                                                  ->setValue(VineBlock::NORTH, direction == Direction::NORTH)
                                                  ->setValue(VineBlock::EAST, direction == Direction::EAST);
                    level->setBlock(pos, state, 2, false);
                    break;
                }
            }
        } else {
            int x = random.nextInt(4) - random.nextInt(4);
            int z = random.nextInt(4) - random.nextInt(4);
            pos = pos.offset(x, 0, z);
        }
    }
    return true;
}
