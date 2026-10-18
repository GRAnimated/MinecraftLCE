#include "net/minecraft/world/level/levelgen/feature/EndGatewayFeature.h"

#include "net/minecraft/core/MutableBlockPos.h"
#include "net/minecraft/world/level/block/Blocks.h"
#include "net/minecraft/world/level/block/EndGatewayBlock.h"
#include <cstdlib>

EndGatewayFeature::EndGatewayFeature(int portalNumber) : Feature(false), m_portalNumber(portalNumber) {}

bool EndGatewayFeature::place(Level* level, Random&, const BlockPos& pos) {
    MutableBlockPos current(0, 0, 0);
    for (int x = pos.getX() - 1; x <= pos.getX() + 1; ++x) {
        for (int z = pos.getZ() - 1; z <= pos.getZ() + 1; ++z) {
            for (int y = pos.getY() - 2; y <= pos.getY() + 2; ++y) {
                current.set(x, y, z);
                bool sameX = x == pos.getX();
                bool sameY = y == pos.getY();
                bool sameZ = z == pos.getZ();
                bool cap = std::abs(y - pos.getY()) == 2;
                if (sameX && sameY && sameZ) {
                    const BlockState* state = Blocks::END_GATEWAY->defaultBlockState()->setValue(
                        EndGatewayBlock::FJ_PORTAL_NUMBER, m_portalNumber);
                    setBlock(level, BlockPos(current), state);
                } else if (sameY) {
                    setBlock(level, current, Blocks::AIR->defaultBlockState());
                } else if (sameX && cap && sameZ) {
                    setBlock(level, current, Blocks::BEDROCK->defaultBlockState());
                } else if (cap || (!sameX && !sameZ)) {
                    setBlock(level, current, Blocks::AIR->defaultBlockState());
                } else {
                    setBlock(level, current, Blocks::BEDROCK->defaultBlockState());
                }
            }
        }
    }
    return true;
}
