#include "BlockPos.h"
#include "Minecraft/util/math/Vec3.h"

BlockPos::BlockPos(int x, int y, int z) {
    mArr = Vec3i(x, y, z);
}

BlockPos::BlockPos(Vec3* vec) {
    mArr = Vec3i(vec->x, vec->y, vec->z);
}

BlockPos* BlockPos::create(int x, int y, int z) {
    return new BlockPos(x, y, z);
}
