#include "Minecraft.Core/BlockPos.h"
#include "Minecraft.World/phys/Vec3.h"

BlockPos::BlockPos(int x, int y, int z) : mArr(Vec3i(x, y, z)) {}

BlockPos::BlockPos() : mArr(Vec3i(0, 0, 0)) {}

BlockPos::BlockPos(Vec3* vec) : mArr(Vec3i(vec->x, vec->y, vec->z)) {}

BlockPos::BlockPos(Vec3i const& vec) : mArr(Vec3i(vec.getX(), vec.getY(), vec.getZ())) {}

BlockPos* BlockPos::create(int x, int y, int z) {
    return new BlockPos(x, y, z);
}
