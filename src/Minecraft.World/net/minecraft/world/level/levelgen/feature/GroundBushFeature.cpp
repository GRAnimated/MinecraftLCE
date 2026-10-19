#include "net/minecraft/world/level/levelgen/feature/GroundBushFeature.h"

#include "NX/Platform.h"
#include "net/minecraft/core/BlockPos.h"
#include "net/minecraft/world/Random.h"
#include "net/minecraft/world/level/Level.h"
#include "net/minecraft/world/level/block/Blocks.h"
#include "net/minecraft/world/level/material/Material.h"
#include <cstdlib>

// name guessed
GroundBushFeature::GroundBushFeature(const BlockState* trunk, const BlockState* leaves)
    : TreeFeature(false), m_bushLeaves(leaves), m_bushTrunk(trunk) {}

// name guessed
bool GroundBushFeature::place(Level* level, Random& random, const BlockPos& origin) {
    PIXBeginNamedEvent(0.0f, "Placing GroundBushFeature");
    BlockPos pos = origin;
    for (;;) {
        const BlockState* state = level->getBlockState(pos);
        if ((state->getMaterial() != Material::AIR && state->getMaterial() != Material::LEAVES)
            || pos.getY() <= 0)
            break;
        pos = pos.below();
    }
    Block* ground = level->getBlockState(pos)->getBlock();
    if (ground == Blocks::DIRT || ground == Blocks::GRASS) {
        pos = pos.above();
        setBlock(level, pos, m_bushTrunk);
        for (int y = pos.getY(); y <= pos.getY() + 2; ++y) {
            int radius = 2 - (y - pos.getY());
            for (int x = pos.getX() - radius; x <= pos.getX() + radius; ++x) {
                int dx = x - pos.getX();
                for (int z = pos.getZ() - radius; z <= pos.getZ() + radius; ++z) {
                    int dz = z - pos.getZ();
                    if (std::abs(dx) != radius || std::abs(dz) != radius || random.nextInt(2) != 0) {
                        BlockPos candidate(x, y, z);
                        const BlockState* state = level->getBlockState(candidate);
                        Material* material = state->getMaterial();
                        if (material == Material::AIR || material == Material::LEAVES)
                            setBlock(level, candidate, m_bushLeaves);
                    }
                }
            }
        }
    }
    PIXEndNamedEvent();
    return true;
}
