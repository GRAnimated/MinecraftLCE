#include "net/minecraft/core/BlockPos.h"
#include <cstdint>

// The original static initializers derive 26 X/Z bits from the 30,000,000
// world border, leaving 12 Y bits. Positions are packed X:Y:Z, high to low.
long long BlockPos::compressBlockPos() const {
    return (std::uint64_t(getX()) & 0x3ffffffULL) << 38 | (std::uint64_t(getY()) & 0xfffULL) << 26
           | (std::uint64_t(getZ()) & 0x3ffffffULL);
}

BlockPos BlockPos::decompressBlockPos(long long value) {
    const std::uint64_t bits = static_cast<std::uint64_t>(value);
    const int x = static_cast<std::int64_t>(bits) >> 38;
    const int y = static_cast<std::int64_t>(bits << 26) >> 52;
    const int z = static_cast<std::int64_t>(bits << 38) >> 38;
    return BlockPos(x, y, z);
}
