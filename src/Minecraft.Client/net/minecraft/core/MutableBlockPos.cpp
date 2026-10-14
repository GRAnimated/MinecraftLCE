#include "net/minecraft/core/MutableBlockPos.h"

MutableBlockPos::MutableBlockPos() : BlockPos(0, 0, 0) {}

MutableBlockPos::MutableBlockPos(int x, int y, int z) : BlockPos(x, y, z) {}
